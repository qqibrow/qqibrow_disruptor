#include <boost/atomic.hpp>

namespace qqibrow {
namespace Disruptor {
class Sequence {
   public:
    Sequence();
    explicit Sequence(long value);
    long Get() const;
    void Set(const long& value);
    bool CompareAndSet(long& expect, const long& newValue);
    long IncrementAndGet();
    long AddAndGet(const long& increment);

   private:
    boost::atomic<long> value_;
    static const long INITIAL_VALUE;
};
}  // namespace Disruptor
}

