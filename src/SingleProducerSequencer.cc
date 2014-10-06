#include "SingleProducerSequencer.h"
#include "Util.h"

using namespace qqibrow::Disruptor;
using namespace std;

SingleProducerSequencer::SingleProducerSequencer(int buffsize,
                                                 WaitStrategy* strategy)
    : Sequencer(buffsize, strategy), nextValue_(-1), cachedValue_(-1) {}

bool SingleProducerSequencer::HasAvailableCapacity(int capacity) {
    long mostBehind = Util::GetMinSequence(gatingSequences_, nextValue_);
    return nextValue_ - mostBehind + capacity <= bufferSize_;
}

long SingleProducerSequencer::Next() { return Next(1); }

long SingleProducerSequencer::Next(int n) {
    assert(n > 0 && "n must > 0.");
    long mostBehind;
    while (nextValue_ + n - bufferSize_ >
    (mostBehind = Util::GetMinSequence(gatingSequences_, nextValue_))) {
        ;
    }
    return nextValue_ = nextValue_ + n;
}

long SingleProducerSequencer::GetRemainingCapacity() {
    long mostBehind = Util::GetMinSequence(gatingSequences_, nextValue_);
    return bufferSize_ - (nextValue_ - mostBehind);
}

void SingleProducerSequencer::Claim(long sequence) {
    this->nextValue_ = sequence;
}

void SingleProducerSequencer::Publish(long sequence) {
    cursor_.Set(sequence);
    waitStrategy_->SignalAllWhenBlocking();
}

    void SingleProducerSequencer::Publish(long lo, long hi) { Publish(hi); }

    bool SingleProducerSequencer::IsAvailable(long sequence) {
        return cursor_.Get() >= sequence;
    }

    long SingleProducerSequencer::GetHighestPublishedSequence(
        long lowBound, long availableSequence) {
        return availableSequence;
    }
