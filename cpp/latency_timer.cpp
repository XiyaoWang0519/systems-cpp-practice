#include <chrono>
#include <iostream>
#include <ratio>

class Timer{
    private:
        using Clock = std::chrono::steady_clock;
        Clock::time_point start_time;
        Clock::time_point end_time;

    public:
        void start() {
            start_time = Clock::now();
        }
    
        void stop() {
            end_time = Clock::now();
        }
    
        double elapsed_ms() const {
            std::chrono::duration<double, std::milli> duration = end_time - start_time;
            return duration.count();
        }
};

int main(){
    const int n = 100000000;
    std::vector<int> data(n, 1);

    Timer timer;
    timer.start();

    long long sum = 0;
    for (int x : data){
        sum += x;
    }

    timer.stop();

    std::cout << "sum = " << sum << "\n";
    std::cout << "elapsed time = " << timer.elapsed_ms() << " ms\n";
    
    return 0;
}