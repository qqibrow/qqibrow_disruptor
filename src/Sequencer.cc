#include "Sequencer.h"
#include "SequenceBarrier.h"
#include <assert.h>
using namespace qqibrow::Disruptor;
using namespace boost;
using namespace std;

Sequencer::Sequencer(int bufferSize, WaitStrategy* strategy)
    : bufferSize_(bufferSize), waitStrategy_(strategy) {
    assert(bufferSize > 1 && ((bufferSize & (bufferSize - 1)) == 0) &&
           "buffSize is wrong.");
}

long Sequencer::GetCursor() const { return cursor_.Get(); }

int Sequencer::GetBufferSize() const { return bufferSize_; }

void Sequencer::AddGatingSequence(Sequence* sequence) {
    gatingSequences_.push_back(SequencePtr(sequence));
}
void Sequencer::RemoveGatingSequence(Sequence* sequence) {
    remove_if(
        gatingSequences_.begin(), gatingSequences_.end(),
        [&sequence](const SequencePtr& ptr) { return ptr.get() == sequence; });
}
long Sequencer::GetMinimumSequence() const { return 0; }
SequenceBarrier* Sequencer::NewBarrier(Sequence sequenceToTrack) {
    return new SequenceBarrier(this, waitStrategy_.get(), gatingSequences_);
}

