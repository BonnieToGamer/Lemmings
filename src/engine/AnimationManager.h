//
// Created by filip on 2025-01-06.
//

#pragma once
#include <unordered_map>

#include "SpriteSheetAnimation.h"

namespace Lemmings::Engine {

template <typename T>
class AnimationManager {
private:
    std::unordered_map<T, std::unique_ptr<SpriteSheetAnimation>> animations_;
    SpriteSheetAnimation* currentSpriteSheetAnimation_;

public:
    AnimationManager();

    void addAnimation(T key, std::unique_ptr<SpriteSheetAnimation> animation);
    void changeAnimation(T key);
    SpriteSheetAnimation* getCurrentAnimation() const;
};

template <typename T>
AnimationManager<T>::AnimationManager(): currentSpriteSheetAnimation_(nullptr)
{
}

template <typename T>
void AnimationManager<T>::addAnimation(T key, std::unique_ptr<SpriteSheetAnimation> animation)
{
    this->animations_.insert(std::make_pair(key, std::move(animation)));
}

template <typename T>
void AnimationManager<T>::changeAnimation(T key)
{
    this->currentSpriteSheetAnimation_ = this->animations_[key].get();
}

template <typename T>
SpriteSheetAnimation* AnimationManager<T>::getCurrentAnimation() const
{
    return this->currentSpriteSheetAnimation_;
}
} // Lemmings
