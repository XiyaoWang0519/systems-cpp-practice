#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

class Timer {
public:
    void start() {
        start_time = std::chrono::steady_clock::now();
    }

    void stop() {
        end_time = std::chrono::steady_clock::now();
    }

    double elapsed_ms() const {
        std::chrono::duration<double, std::milli> duration = end_time - start_time;
        return duration.count();
    }

private:
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point end_time;
};

long long single_thread_sum(const std::vector<int>& data) {
    long long sum = 0;

    for (int x : data) {
        sum += x;
    }

    return sum;
}

long long partial_sum_range(const std::vector<int>& data,
                            std::size_t begin,
                            std::size_t end) {
    long long sum = 0;

    for (std::size_t i = begin; i < end; ++i) {
        sum += data[i];
    }

    return sum;
}

long long multi_thread_sum(const std::vector<int>& data, int num_threads) {
    std::vector<std::thread> threads;
    std::vector<long long> partial_sums(num_threads, 0);

    std::size_t n = data.size();
    std::size_t chunk_size = n / num_threads;

    for (int t = 0; t < num_threads; ++t) {
        std::size_t begin = t * chunk_size;
        std::size_t end;

        if (t == num_threads - 1) {
            end = n;
        } else {
            end = begin + chunk_size;
        }

        threads.emplace_back([&data, &partial_sums, t, begin, end]() {
            partial_sums[t] = partial_sum_range(data, begin, end);
        });
    }

    for (std::thread& th : threads) {
        th.join();
    }

    long long total = 0;
    for (long long partial : partial_sums) {
        total += partial;
    }

    return total;
}

int main() {
    const std::size_t n = 100000000;
    const int num_threads = 4;

    std::vector<int> data(n, 1);

    Timer timer;

    timer.start();
    long long single_sum = single_thread_sum(data);
    timer.stop();
    double single_time_ms = timer.elapsed_ms();

    timer.start();
    long long multi_sum = multi_thread_sum(data, num_threads);
    timer.stop();
    double multi_time_ms = timer.elapsed_ms();

    std::cout << "data size = " << n << "\n";
    std::cout << "num_threads = " << num_threads << "\n\n";

    std::cout << "single-thread sum = " << single_sum << "\n";
    std::cout << "multi-thread sum  = " << multi_sum << "\n\n";

    std::cout << "single-thread time = " << single_time_ms << " ms\n";
    std::cout << "multi-thread time  = " << multi_time_ms << " ms\n\n";

    if (single_sum == multi_sum) {
        std::cout << "result: correct\n";
    } else {
        std::cout << "result: wrong\n";
    }

    return 0;
}