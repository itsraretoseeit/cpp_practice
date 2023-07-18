#pragma once

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include "Job.hpp"

class ExampleJob : public Job {
    public:
        ExampleJob(const unsigned int id) : id_(id) {
            std::cout << "#" << id << " New example job created." << std::endl;
        }
        void run() override {
            setStatus(JobStatus::Running);

            while(!stop_flag_) {
                std::cout << "\n#" << id_ << " - doing job..." << std::endl;
                std::this_thread::sleep_for(std::chrono::duration(std::chrono::seconds(5)));
            }
            setStatus(JobStatus::Completed);
        };

        void stop() override {
            stop_flag_ = true;
        };

        JobStatus getStatus() const override {
            return status_;
        };
    
    private:
        const unsigned int id_;
        std::atomic<bool> stop_flag_ = false;
        JobStatus status_ = JobStatus::Idle;
        std::mutex mutex_;

        void setStatus(JobStatus new_status) {
            std::lock_guard<std::mutex> lock(mutex_);
            status_ = new_status;
        }
};