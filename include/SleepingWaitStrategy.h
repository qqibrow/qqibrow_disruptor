#ifndef QQIBROW_DISRUPTOR_SLEEPINGWAITSTRATEGY
#define QQIBROW_DISRUPTOR_SLEEPINGWAITSTRATEGY
#include "WaitStrategy.h"

namespace qqibrow {
namespace Disruptor {
class SleepingWaitStrategy : public WaitStrategy {
    long WaitFor(long sequence, const Sequence& cursor,
                 const Sequence& dependentSequence, SequenceBarrier& barrier);
    void SignalAllWhenBlocking();
};

}  // namespace Disruptor
}  // namespace qqibrow
#endif
