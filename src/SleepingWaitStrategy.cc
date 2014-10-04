#include "SleepingWaitStrategy.h"
#include <mutex>
#include <condition_variable>

using namespace qqibrow::Disruptor;
using namespace std;

class SleepingWaitStrategy::ConcurrencyImpl {
   public:
    mutex mtx;
    condition_variable cv;
};

SleepingWaitStrategy::SleepingWaitStrategy()
    : concurrencyUtil_(new ConcurrencyImpl()) {}

long SleepingWaitStrategy::WaitFor(long sequence, const Sequence& cursor,
                                   const Sequence& dependentSequence,
                                   const SequenceBarrier& barrier) {
    long availableSequence;
    if ((availableSequence = cursor.Get()) < sequence) {
        unique_lock<mutex> lk(concurrencyUtil_->mtx);
        while ((availableSequence = cursor.Get()) < sequence) {
            // barrier.CheckAlert();
            concurrencyUtil_->cv.wait(lk);
        }
    }
    while ((availableSequence = dependentSequence.Get()) < sequence) {
        // barrier.CheckAlert();
    }
    return availableSequence;
}

void SleepingWaitStrategy::SignalAllWhenBlocking() {
    unique_lock<mutex> lk(concurrencyUtil_->mtx);
    concurrencyUtil_->cv.notify_all();
}
