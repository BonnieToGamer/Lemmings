//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>

namespace Lemmings::Engine {

template <typename T>
class IState {

protected:
    T* parent_;

public:
    void setParent(T* parent) { this->parent_ = parent; }
    virtual ~IState() = default;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual std::shared_ptr<IState<T>> update(float delta) = 0;
};

} // Lemmings
