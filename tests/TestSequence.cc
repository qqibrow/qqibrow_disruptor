#include "gtest/gtest.h"
#include "Sequence.h"

using qqibrow::Disruptor::Sequence;
class TestSequence : public ::testing::Test {
    protected:
        TestSequence() {};
        virtual ~TestSequence() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
        Sequence s;
};

TEST_F(TestSequence, ShouldStartWithMinusOne) {
    EXPECT_EQ(s.Get(), -1);
}

