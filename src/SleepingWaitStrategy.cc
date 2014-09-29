#include "SleepingWaitStrategy.h"

using namespace qqibrow::Disruptor;

long SleepingWaitStrategy::WaitFor(long sequence, const Sequence& cursor,
                                   const Sequence& dependentSequence,
                                   const SequenceBarrier& barrier) {}

void SleepingWaitStrategy::SignalAllWhenBlocking() {

}
