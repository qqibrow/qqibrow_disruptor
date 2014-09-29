#include "gtest/gtest.h"
#include "Sequencer.h"

using namespace qqibrow::Disruptor;

class TestSequencer : public ::testing::Test {
    protected:
        TestSequencer() {
            sequencer = new SingleProducerSequencer();
        };
        virtual ~TestSequencer() {
            delete sequencer;
        }
        virtual void SetUp() {}
        virtual void TearDown() {}
        Sequencer* sequencer;

};
