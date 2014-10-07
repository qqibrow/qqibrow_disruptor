#ifndef QQIBROW_DISRUPTOR_SEQUENCER
#define QQIBROW_DISRUPTOR_SEQUENCER
#include <boost/shared_ptr.hpp>
#include <vector>
#include "WaitStrategy.h"
#include "./Sequence.h"

namespace qqibrow {
namespace Disruptor {

typedef boost::shared_ptr<Sequence> SequencePtr;
    typedef std::vector<SequencePtr> SequenceCollector;
class Sequencer {
   public:
    Sequencer(int bufferSize, WaitStrategy* strategy);
    virtual ~Sequencer() {}
    long GetCursor() const;
    int GetBufferSize() const;
    void AddGatingSequence(Sequence* sequence);
    void RemoveGatingSequence(Sequence* sequence);
    long GetMinimumSequence() const;
    // TODO(qqibrow) Refactor this to use a Builder Pattern.
    SequenceBarrier* NewBarrier(Sequence sequenceToTrack);

    virtual bool HasAvailableCapacity(int capacity) = 0;
    virtual long Next() = 0;
    virtual long Next(int n) = 0;
    virtual long GetRemainingCapacity() = 0;
    // Only used during init.
    virtual void Claim(long sequence) = 0;
    virtual void Publish(long sequence) = 0;
    virtual void Publish(long lo, long hi) = 0;
    virtual bool IsAvailable(long sequence) = 0;
    virtual long GetHighestPublishedSequence(long lowBound, long availableSequence) = 0;

   protected:
    const int bufferSize_;
    const boost::shared_ptr<WaitStrategy> waitStrategy_;
    Sequence cursor_;
    SequenceCollector gatingSequences_;
};
}  // namespace Disruptor
}  // namespace qqibrow
#endif
