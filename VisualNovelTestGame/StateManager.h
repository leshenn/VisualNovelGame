#pragma once
#include <memory>
#include <stack>
#include "State.h"

class StateManager {
private:
    std::stack<std::unique_ptr<State>> states;

public:
    void pushState(std::unique_ptr<State> state);
    void popState();
    State* getCurrentState();
};