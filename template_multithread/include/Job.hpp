#pragma once

enum class JobStatus {
    Idle,
    Running,
    Completed,
    Error
};

class Job {
    public:
        virtual ~Job() = default;
        virtual void run() = 0;
        virtual void stop() = 0;
        virtual JobStatus getStatus() const = 0;
};