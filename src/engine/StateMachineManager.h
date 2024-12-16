//
// Created by filip on 2024-12-16.
//

#pragma once
#include "IState.h"

namespace Lemmings::Engine {

    template <typename T>
    class StateMachineManager {
    private:
        std::shared_ptr<IState<T>> currentState_;
        std::shared_ptr<T> parent_;

    public:
        StateMachineManager(std::shared_ptr<IState<T>> startingState, std::shared_ptr<T> parent);
        void changeState(std::shared_ptr<IState<T>> state);
        void update(float delta);
    };

    // Implementation of the template methods
    template <typename T>
    StateMachineManager<T>::StateMachineManager(std::shared_ptr<IState<T>> startingState, std::shared_ptr<T> parent) : parent_(parent)
    {
        this->changeState(startingState);
    }

    template <typename T>
    void StateMachineManager<T>::changeState(std::shared_ptr<IState<T>> state)
    {
        if (this->currentState_ != nullptr)
            this->currentState_->exit();

        this->currentState_ = state;
        this->currentState_->setParent(this->parent_);
        this->currentState_->enter();
    }

    template <typename T>
    void StateMachineManager<T>::update(float delta)
    {
        std::shared_ptr<IState<T>> newState = this->currentState_->update(delta);
        if (newState != nullptr) this->changeState(newState);
    }

} // namespace Lemmings::Engine