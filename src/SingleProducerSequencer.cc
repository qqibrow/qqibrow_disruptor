#include "SingleProducerSequencer.h"

using namespace qqibrow::Disruptor;

SingleProducerSequencer::SingleProducerSequencer(int buffsize, WaitStrategy* strategy):
    Sequencer(buffsize, strategy) {}

bool SingleProducerSequencer::HasAvailableCapacity(int capacity) {
    return false;
}

long SingleProducerSequencer::Next() {
    return -1;

}

long SingleProducerSequencer::Next(int n) {
    return -1;

}

long SingleProducerSequencer::GetRemainingCapacity() {
    return 0;

}

void SingleProducerSequencer::Claim(long sequence) {

}

void SingleProducerSequencer::Publish(long sequence) {

}

void SingleProducerSequencer::Publish(long lo, long hi) {

}

bool SingleProducerSequencer::IsAvailable(long sequence) {
    return false;

}

long SingleProducerSequencer::GetHighestPublishedSequence(long lowBound, long availableSequence) {
    return -1;

}
