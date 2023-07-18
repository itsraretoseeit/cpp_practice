#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include "StateMachine.hpp"
#include "Job.hpp"
#include "ExampleJob.hpp"
#include "ExternalEventProvider.hpp"

int main(int argc, char* argv[]) {
    StateMachine stateMachine;
    ExternalEventProvider externalEventProvider;

    /* vector for holding UniquePtrs for the Jobs to be executed*/
    std::vector<std::unique_ptr<Job>> jobs;
    /* vector of threads which executes the Jobs */
    std::vector<std::thread> threads;

    /* create a number of Jobs to be done */
    for (int i = 0; i<5; i++) {
        jobs.push_back(std::make_unique<ExampleJob>(i));
    }

    /* run the created jobs, emplace_back creates 'in place' the thread object */
    for (auto& job : jobs) {
        threads.emplace_back([&job]() {
            job->run();
        });
    }

    /* add also the external event provider to the thread vector*/
    threads.emplace_back([&stateMachine, &externalEventProvider]() {
        externalEventProvider.registerForEvent(stateMachine);
    });

    /* scoped lock and blocking wait for the condition to be satisfied */
    {
        std::unique_lock<std::mutex> lock(stateMachine.getMutex());
        stateMachine.getConditionVariable().wait(lock, [&]() {
            return !stateMachine.isRunning();
        });
    }
    
    /* stop the jobs */
    for(auto& job : jobs) {
        job -> stop();
    }

    /* join the threads*/
    for(auto& thread : threads) {
        thread.join();
    }

    /* clean up */
    jobs.clear();
    threads.clear();

    return 0;
}