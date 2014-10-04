#ifndef QQIBROW_DISRUPTOR_SLEEPINGWAITSTRATEGY
#define QQIBROW_DISRUPTOR_SLEEPINGWAITSTRATEGY
#include "WaitStrategy.h"
#include <boost/scoped_ptr.hpp>

namespace qqibrow {
namespace Disruptor {
class SleepingWaitStrategy : public WaitStrategy {
   public:
    SleepingWaitStrategy();
    virtual long WaitFor(long sequence, const Sequence& cursor,
                         const Sequence& dependentSequence,
                         const SequenceBarrier& barrier);
    virtual void SignalAllWhenBlocking();
   private:
    class ConcurrencyImpl;
    boost::scoped_ptr<ConcurrencyImpl> concurrencyUtil_;
};

}  // namespace Disruptor
}  // namespace qqibrow
#endif
