#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include "StateMachine.hpp"

class ExternalEventProvider {

    public:
        void registerForEvent(StateMachine& stateMachine) {
            std::this_thread::sleep_for(std::chrono::seconds(8));
            std::cout << "Triggering status change." << std::endl;
            stateMachine.triggerStatusChange();
        };

};