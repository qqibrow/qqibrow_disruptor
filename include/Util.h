#ifndef QQIBROW_DISRUPTOR_UTIL
#define QQIBROW_DISRUPTOR_UTIL
#include "Sequence.h"
#include <algorithm>
#include <vector>

namespace qqibrow {
namespace Disruptor {
struct CompareSequencePtr {
    bool operator()(const SequencePtr& p1, const SequencePtr& p2) {
        return p1->Get() < p2->Get();
    }
};
class Util {
   public:
    static long GetMinSequence(const std::vector<SequencePtr>& gatingSequences,
                               long sequence) {
        if (gatingSequences.empty()) {
            return sequence;
        } else {
            const SequencePtr& ptr =
                *std::min_element(gatingSequences.begin(),
                                  gatingSequences.end(), CompareSequencePtr());
            return (std::min)(sequence, ptr->Get());
        }
    }
};
}
}
#endif
