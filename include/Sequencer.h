#ifndef QQIBROW_DISRUPTOR_SEQUENCER
#define QQIBROW_DISRUPTOR_SEQUENCER
#include <boost/shared_ptr.hpp>
#include <vector>
#include "WaitStrategy.h"
#include "./Sequence.h"

namespace qqibrow {
namespace Disruptor {

typedef boost::shared_ptr<Sequence> SequencePtr;
class Sequencer {
   public:
    Sequencer(int bufferSize, WaitStrategy* strategy);
    long GetCursor() const;
    int GetBufferSize() const;
    void AddGatingSequence(Sequence* sequence);
    void RemoveGatingSequence(Sequence* sequence);
    long GetMinimumSequence() const;
    // TODO(qqibrow) Refactor this to use a Builder Pattern.
    SequenceBarrier* NewBarrier(Sequence sequenceToTrack);

   protected:
    const int bufferSize_;
    const boost::shared_ptr<WaitStrategy> waitStrategy_;
    const Sequence cursor_;
    std::vector<SequencePtr> gatingSequences_;
};
}  // namespace Disruptor
}  // namespace qqibrow
#endif
