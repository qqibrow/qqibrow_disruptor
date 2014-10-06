#ifndef QQIBROW_DISRUPTOR_SEQUENCEBARRIER
#define QQIBROW_DISRUPTOR_SEQUENCEBARRIER
#include "Sequencer.h"

namespace qqibrow {
namespace Disruptor {
class SequenceBarrier {
   public:
    SequenceBarrier(Sequencer* sequencer,
                                     const WaitStrategy* strategy,
                                     SequenceCollector& dependentSequences);
    ~SequenceBarrier() {}
    long WaitFor(long sequence);
    long GetCursor() const;
};
}  // namespace Disruptor
}  // namespace qqibrow
#endif
