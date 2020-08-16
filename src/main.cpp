#include "RootTimer.h"
#include <thread>

int main() {
    RootTimer timer(1000000000);
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    timer.stop();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
