#include <chrono>
namespace stackapi {

struct Backoff {
    int secs;
    std::chrono::system_clock::time_point timeReceived;
};

}
