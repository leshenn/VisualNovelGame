#include "StateManager.h"

void StateManager::pushState(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void StateManager::popState() {
    if (!states.empty()) states.pop();
}

State* StateManager::getCurrentState() {
    return states.empty() ? nullptr : states.top().get();
}