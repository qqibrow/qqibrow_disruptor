#include "Sequence.h"

using namespace boost;
using namespace qqibrow::Disruptor;

const long Sequence::INITIAL_VALUE = -1;

Sequence::Sequence() : Sequence(INITIAL_VALUE){

}

Sequence::Sequence(long value) {
    this->value_.store(value, memory_order_relaxed);
}

long Sequence::Get() const {
    return value_.load(memory_order_relaxed);
}

void Sequence::Set(const long& value) {
    this->value_.store(value, memory_order_relaxed);
}

bool Sequence::CompareAndSet(long& expect, const long& newValue) {
    return value_.compare_exchange_weak(expect, newValue, memory_order_seq_cst);
}

long Sequence::IncrementAndGet() {
    return AddAndGet(1);
}

long Sequence::AddAndGet(const long& increment) {
    long currentValue, newValue;
    do {
        currentValue = Get();
        newValue = currentValue + increment;
    } while(!CompareAndSet(currentValue, newValue));
    return newValue;
}

