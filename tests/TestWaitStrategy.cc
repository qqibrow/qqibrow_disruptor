#include "gtest/gtest.h"
#include "SleepingWaitStrategy.h"
#include "SequenceBarrier.h"
#include <thread>
#include <mutex>
#include <boost/scoped_ptr.hpp>

using namespace qqibrow::Disruptor;

class TestWaitStrategy : public ::testing::Test {
    protected:
        TestWaitStrategy() {

        }
        virtual ~TestWaitStrategy() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
};

TEST_F(TestWaitStrategy, ShouldWaitFordependentSequence) {
    boost::scoped_ptr<WaitStrategy> waitStrategy(new SleepingWaitStrategy());
    Sequence depdent(0);
    int steps = 100;
    Sequence cursor(steps);
    boost::scoped_ptr<SequenceBarrier> barrier(new SequenceBarrier());
    long result;
    std::thread runningWaitStrategy([&]() {
            result = waitStrategy->WaitFor(steps, cursor, depdent, barrier.get());
            });
    depdent.AddAndGet(steps);
    runningWaitStrategy.join();
    EXPECT_EQ(result, steps);

}
