#include <iostream>

#include <fstream>
#include <random>
#include <algorithm>
#include <future>
#include <thread>

#include <queue>

// определяем задачу
template<class T>
struct SortTask {
    T first;
    T last;
    std::atomic<bool> flag{false};

    SortTask(T first, T last) {
        this->first = first;
        this->last = last;
    };
};

template<class T>
class SortingMachine {
public:
    std::mutex mtx;
    std::condition_variable cv; // условная переменная
    std::queue<SortTask<T> *> tasks;
    T first;
    T last;
    std::atomic<bool> stopped{false}; // состояние


    SortingMachine(T first, T last) : first(first), last(last) {
        tasks = std::queue<SortTask<T> *>();
    };

    void push(SortTask<T> *t) {
        //std::cout << "pushing task\n";
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(t);

        std::cout << " notifying!! tasks size = " << std::to_string(tasks.size()) << "\n";

        cv.notify_one(); // оповестить один из ждущих потоков
    }

    void loop() {
        std::unique_lock<std::mutex> lock{mtx};
        std::cout << "thread loop??\n";
        cv.wait(lock, [this, &lock]() {
            std::cout << "thread working, tasks size = " << std::to_string(tasks.size()) << "\n";
            while (!tasks.empty()) {
                std::cout << "task detected\n";
                SortTask<T> *task = tasks.front();
                tasks.pop();
                lock.unlock(); // lock_guard наоборот
                do_sort(task);
                lock.lock();
            }
            bool d = stopped;
            return d;
        });

    }

    std::vector<std::thread> threads{8}; // потоки
    void start() {

        for (auto &thr : threads) {
            std::cout << "starting thread##\n";
            thr = std::thread{[this]() { this->loop(); }};
        }
        stopped = false; // изменяем состояние
        std::cout << "threads started\n";
    }

    void stop() {
        stopped = true;
        cv.notify_all();
        std::cout << "stop called\n";
    }

    void wait() { // ожидание завершения потоков
        std::cout << "waiting with " << std::to_string(this->tasks.size()) << " tasks in queue\n";
        for (auto &thr : threads) {
            std::cout << "waiting with " << std::to_string(this->tasks.size()) << " tasks in queue\n";

            if (thr.joinable()) { thr.join(); }
        }
        std::cout << "threads stopped\n";

    }

    void sort() {
        SortTask<T> *t = new SortTask<T>(this->first, this->last);

        this->push(t);
        while (!(t->flag)){}
        this->stop();
        this->wait();
    }

    void do_sort(SortTask<T> *task) {
        long size = std::distance(task->first, task->last);

        if (size < 2) {
            task->flag = true;
            return;
        }
        T middle = std::next(task->first, size / 2);
        SortTask<T> *t1 = new SortTask<T>(task->first, middle);
        SortTask<T> *t2 = new SortTask<T>(middle, task->last);

        //std::cout << "pushing from sorting task\n";
        //std::cout << std::this_thread::get_id() << std::endl;

        this->push(t1);
        this->push(t2);

        //std::cout << "waiting in sorting task " << std::to_string(this->tasks.size()) << " tasks in queue\n";
        //std::cout << std::this_thread::get_id() << " mtx: " << std::endl;

        //cv.notify_all();
        while (!(t1->flag));
        while (!(t2->flag));
        std::cout << "merge in sorting task\n";
        std::cout << std::this_thread::get_id() << std::endl;


        merge_a(task->first, middle, middle, task->last);
        std::cout << "releasing sorting task\n";
        std::cout << "waiting with "<<std::to_string(this->tasks.size())<<" tasks in queue\n";

        task->flag = true;
        std::cout<<"flag set on task";
    }


    void merge_a(T xf, T xl, T yf, T yl) {
        T f = xf;
        unsigned long const size = yl - xf;
        std::vector<typename T::value_type> buf;
        int i = 0;
        while (i < size) {
            if (xf == xl) {
                buf.insert(buf.begin() + i, yf, yl);
                break;
            }
            if (yf == yl) {
                buf.insert(buf.begin() + i, xf, xl);
                break;
            }
            if (*xf >= *yf) {
                buf.push_back(*xf);
                xf++;
            } else {
                buf.push_back(*yf);
                yf++;
            }
            i++;
        }
        std::copy(buf.begin(), buf.end(), f);

    }

};