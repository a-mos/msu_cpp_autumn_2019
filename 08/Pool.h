#include <thread>
#include <future>
#include <vector>
#include <queue>


class ThreadPool {
    std::condition_variable cond;
    std::vector <std::thread> threads;
    std::queue <std::function<void()>> jobs;
    std::mutex m;
    bool stop;

public:

    explicit ThreadPool(size_t poolSize) {
        stop = false;
        for (size_t i = 0; i < poolSize; ++i) {
            threads.push_back(std::thread(&ThreadPool::wait_and_work, this));
        }
    }
    
    void wait_and_work() {
        while (true) {
            std::function<void()> job;
            {
                std::unique_lock <std::mutex> lock(m);
                while (!stop && jobs.empty()) {
                    cond.wait(lock);
                }
                if (stop) {
                    break;
                }
                job = jobs.front();
                jobs.pop();
            }
            job();
        }
        return;
    }
    
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
            (std::bind(func, args...));
        auto result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(m);
            jobs.emplace([task]() { (*task)(); });
        }
        cond.notify_one();
        return result;
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(m);
            stop = true;
        }
        cond.notify_all();
        for (auto &t: threads) {
            t.join();
        }
    }
};