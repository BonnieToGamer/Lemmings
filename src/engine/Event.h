//
// Created by filip on 2024-12-25.
//

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <mutex>

namespace Lemmings::Engine {

    template <typename... Args>
    class Event {
    private:
        std::vector<std::function<void(Args...)>> receivers_;
        mutable std::mutex mutex_; // For thread safety

    public:
        Event();

        void invoke(Args... args) const;
        void operator +=(std::function<void(Args...)> func);
        void operator -=(std::function<void(Args...)> func);
    };

    template <typename... Args>
    Event<Args...>::Event() : receivers_()
    {
    }

    template <typename... Args>
    void Event<Args...>::invoke(Args... args) const
    {
        for (const auto& receiver : receivers_)
            receiver(args...);
    }

    template <typename... Args>
    void Event<Args...>::operator+=(std::function<void(Args...)> func)
    {
        receivers_.push_back(func);
    }

    template <typename... Args>
    void Event<Args...>::operator-=(std::function<void(Args...)> func)
    {
        std::lock_guard<std::mutex> lock(mutex_); // Lock for thread safety
        receivers_.erase(std::remove_if(receivers_.begin(), receivers_.end(),
        [&func](const std::function<void(Args...)>& f) {
            return f.template target<void(Args...)>() == func.template target<void(Args...)>();
        }), receivers_.end());
    }
} // namespace Lemmings::Engine