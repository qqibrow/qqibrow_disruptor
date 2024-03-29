#ifndef QQIBROW_DISRUPTOR_WAITSTRETEGY
#define QQIBROW_DISRUPTOR_WAITSTRETEGY
#include "Sequence.h"

namespace qqibrow {
namespace Disruptor {
class SequenceBarrier;
class WaitStrategy {
    public:
    virtual long WaitFor(long sequence, const Sequence& cursor,
                 const Sequence& dependentSequence,
                 const SequenceBarrier* barrier) = 0;
    virtual void SignalAllWhenBlocking() = 0;
};

}  // namespace Disruptor
}  // namespace qqibrow
#endif
