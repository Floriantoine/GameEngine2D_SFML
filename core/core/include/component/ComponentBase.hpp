#pragma once

#include "../../src/types.hpp"
#include "Imgui.hpp"

namespace fa {

class Entity;

class ComponentBase {
    friend class ComponentManager;

  protected:
    Entity *entity_{nullptr};

    static id_t getNextTypeId()
    {
        static id_t id = 0;
        return id++;
    }

  public:
    Entity *getEntity() const
    {
        return this->entity_;
    }
    virtual void dislayImGuiPanel()
    {
        ImGui::Text("Empty");
    }
};

} // namespace fa
