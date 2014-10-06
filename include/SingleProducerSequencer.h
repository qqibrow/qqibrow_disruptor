#ifndef QQIBROW_DISRUPTOR_SINGLEPRODUCERSEQUENCER
#define QQIBROW_DISRUPTOR_SINGLEPRODUCERSEQUENCER

#include "./Sequencer.h"
namespace qqibrow {
namespace Disruptor {
class SingleProducerSequencer : public Sequencer {
   public:
    SingleProducerSequencer(int buffsize, WaitStrategy* strategy);
    virtual bool HasAvailableCapacity(int capacity);
    virtual long Next();
    virtual long Next(int n);
    virtual long GetRemainingCapacity();
    // Only used during init.
    virtual void Claim(long sequence);
    virtual void Publish(long sequence);
    virtual void Publish(long lo, long hi);
    virtual bool IsAvailable(long sequence);
    virtual long GetHighestPublishedSequence(long lowBound, long availableSequence);
    virtual ~SingleProducerSequencer() {}

   private:
    long nextValue_;
    long cachedValue_;

};

}  // namespace disruptor
}  // namespace qqibrow
#endif
