#ifndef QQIBROW_DISRUPTOR_SINGLEPRODUCERSEQUENCER
#define QQIBROW_DISRUPTOR_SINGLEPRODUCERSEQUENCER

#include "./Sequencer.h"
namespace qqibrow {
namespace Disruptor {
class SingleProducerSequencer : public Sequencer {
   public:
    SingleProducerSequencer(int buffsize, WaitStrategy* strategy);
    bool HasAvailableCapacity(int capacity);
    long Next();
    long Next(int n);
    long GetRemainingCapacity();
    // Only used during init.
    void Claim(long sequence);
    void Publish(long sequence);
    void Publish(long lo, long hi);
    bool IsAvailable(long sequence);
    long GetHighestPublishedSequence(long lowBound, long availableSequence);

   private:
    long nextValue_;
    long cachedValue_;

};

}  // namespace disruptor
}  // namespace qqibrow
#endif
