#include "system/FormSystem.hpp"

namespace systems {

void FormSystem::update(long elapsedTime)
{
    auto array =
        this->componentManager_->getComponentList<components::FormComponent>();
    auto it = array.begin();
    components::FormComponent *FormC =
        static_cast<components::FormComponent *>(it->second);
    _data = *(FormC->_dataLink);

    if (ImGui::SliderInt("Test", &_data, 0, 1920)) {
        for (it; it != array.end(); ++it) {
            FormC = static_cast<components::FormComponent *>(it->second);
            *(FormC->_dataLink) = _data;
        }
    }
}
} // namespace systems