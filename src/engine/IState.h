//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>

namespace Lemmings::Engine {

template <typename T>
class IState {

protected:
    T* parent_ = nullptr;

public:
    void setParent(T* parent) { this->parent_ = parent; }
    virtual ~IState() = default;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual std::unique_ptr<IState<T>> update(float delta) = 0;
};

} // Lemmings
