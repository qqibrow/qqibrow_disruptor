#include <thread>
#include <boost/atomic.hpp>
#include "gtest/gtest.h"
#include "Sequencer.h"
#include "SingleProducerSequencer.h"
#include "SleepingWaitStrategy.h"

using namespace qqibrow::Disruptor;

class TestSequencer : public ::testing::Test {
   public:
    const static int BUFFER_SIZE;

   protected:
    TestSequencer() {
        const int buffsize = BUFFER_SIZE;
        sequencer =
            new SingleProducerSequencer(buffsize, new SleepingWaitStrategy());
    };
    virtual ~TestSequencer() { delete sequencer; }
    virtual void SetUp() {}
    virtual void TearDown() {}
    Sequencer* sequencer;
};

const int TestSequencer::BUFFER_SIZE = 16;

TEST_F(TestSequencer, ShouldStartWithInitialValue) {
    EXPECT_EQ(0, sequencer->Next());
}

TEST_F(TestSequencer, ShouldBatchClaim) { EXPECT_EQ(3, sequencer->Next(4)); }

TEST_F(TestSequencer, ShouldHasAvailableCapacity) {
    sequencer->AddGatingSequence(new Sequence());
    EXPECT_TRUE(sequencer->HasAvailableCapacity(1));
    EXPECT_TRUE(sequencer->HasAvailableCapacity(TestSequencer::BUFFER_SIZE));
    EXPECT_FALSE(
        sequencer->HasAvailableCapacity(TestSequencer::BUFFER_SIZE + 1));
    sequencer->Publish(sequencer->Next());
    EXPECT_TRUE(
        sequencer->HasAvailableCapacity(TestSequencer::BUFFER_SIZE - 1));
    EXPECT_FALSE(sequencer->HasAvailableCapacity(TestSequencer::BUFFER_SIZE));
}

TEST_F(TestSequencer, ShouldNoAvailableCapacity) {
    sequencer->AddGatingSequence(new Sequence());
    long highest = sequencer->Next(TestSequencer::BUFFER_SIZE);
    sequencer->Publish(highest - (TestSequencer::BUFFER_SIZE - 1), highest);
    EXPECT_FALSE(sequencer->HasAvailableCapacity(1));
    EXPECT_TRUE(sequencer->HasAvailableCapacity(0));
}

TEST_F(TestSequencer, ShouldBlockingWhenBufferIsFull) {
    Sequence* gating = new Sequence();
    sequencer->AddGatingSequence(gating);
    long highest = sequencer->Next(TestSequencer::BUFFER_SIZE);
    sequencer->Publish(highest - (TestSequencer::BUFFER_SIZE - 1), highest);
    boost::atomic<bool> wait1, wait2;
    wait1.store(false, boost::memory_order_relaxed);
    wait2.store(false, boost::memory_order_relaxed);
    std::thread th([&]() {
            wait1.store(true, boost::memory_order_release);
            long next = sequencer->Next();
            sequencer->Publish(next);
            wait2.store(true, boost::memory_order_release);
            });
    while (!wait1.load(boost::memory_order_acquire))
        ;
    EXPECT_EQ(-1 + TestSequencer::BUFFER_SIZE, sequencer->GetCursor());
    gating->Set(-1 + 1);
    while (!wait2.load(boost::memory_order_acquire))
        ;
    EXPECT_EQ(TestSequencer::BUFFER_SIZE, sequencer->GetCursor());

    th.join();

}

