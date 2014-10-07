#include "SequenceBarrier.h"
#include "Sequencer.h"
#include "Util.h"

using namespace qqibrow::Disruptor;
using namespace std;

SequenceBarrier::SequenceBarrier(Sequencer* sequencer, const WaitStrategy* strategy,
                SequenceCollector& dependentSequences) {

}
long SequenceBarrier::WaitFor(long sequence) {return 0;}
long SequenceBarrier::GetCursor() const {return 0;}
