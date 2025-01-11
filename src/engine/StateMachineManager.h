//
// Created by filip on 2024-12-16.
//

#pragma once
#include "IState.h"

namespace Lemmings::Engine {

    template <typename T>
    class StateMachineManager {
    private:
        std::unique_ptr<IState<T>> currentState_;
        T* parent_;

    public:
        StateMachineManager(std::unique_ptr<IState<T>> startingState, T* parent);
        void changeState(std::unique_ptr<IState<T>> state);
        void update(float delta);
    };

    template <typename T>
    StateMachineManager<T>::StateMachineManager(std::unique_ptr<IState<T>> startingState, T* parent) : parent_(parent)
    {
        this->changeState(std::move(startingState));
    }

    template <typename T>
    void StateMachineManager<T>::changeState(std::unique_ptr<IState<T>> state)
    {
        if (this->currentState_ != nullptr)
            this->currentState_->exit();

        this->currentState_ = std::move(state);
        this->currentState_->setParent(this->parent_);
        this->currentState_->enter();
    }

    template <typename T>
    void StateMachineManager<T>::update(float delta)
    {
        std::unique_ptr<IState<T>> newState = this->currentState_->update(delta);
        if (newState != nullptr) this->changeState(std::move(newState));
    }
} // namespace Lemmings::Engine