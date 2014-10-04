#include "gtest/gtest.h"
#include "Sequencer.h"
#include "SingleProducerSequencer.h"
#include "SleepingWaitStrategy.h"

using namespace qqibrow::Disruptor;

class TestSequencer : public ::testing::Test {
    protected:
        TestSequencer() {
            const int buffsize = 100;
            sequencer = new SingleProducerSequencer(buffsize, new SleepingWaitStrategy());
        };
        virtual ~TestSequencer() {
            delete sequencer;
        }
        virtual void SetUp() {}
        virtual void TearDown() {}
        Sequencer* sequencer;

};
