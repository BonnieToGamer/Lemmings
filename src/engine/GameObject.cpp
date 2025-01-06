#include "GameObject.h"

namespace Lemmings::Engine
{
    void GameObject::init()
    {
        for (const auto& child : this->children_)
            child->init();
    }

    void GameObject::update(float delta)
    {
        for (const auto& child : this->children_)
            child->update(delta);
    }

    void GameObject::draw(sf::RenderTarget& renderTarget)
    {
        for (const auto& child : this->children_)
            child->draw(renderTarget);
    }

    void GameObject::addChild(std::unique_ptr<GameObject> child)
    {
        this->children_.push_back(std::move(child));
    }

    void GameObject::removeChild(std::unique_ptr<GameObject> child)
    {
        this->children_.erase(std::find(this->children_.begin(), this->children_.end(), child));
    }
}
