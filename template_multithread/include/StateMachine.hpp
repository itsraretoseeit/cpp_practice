#pragma once

#include <mutex>
#include <condition_variable>

class StateMachine {
public:
    StateMachine() : running_(true) {};

    void stop() {
        std::lock_guard<std::mutex> lock(mutex_);
        running_ = false;
        cv_.notify_all();
    }

    void triggerStatusChange() {
        stop();
    }

    bool isRunning() const {
        return running_;
    }

    std::mutex& getMutex() {
        return mutex_;
    }

    std::condition_variable& getConditionVariable() {
        return cv_;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    bool running_;
};