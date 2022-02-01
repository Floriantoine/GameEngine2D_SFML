#include "system/ResetSystem.hpp"

namespace systems {
void ResetSystem::reset(int index)
{
    components::Gravity *gravityC =
        this->componentManager_->getComponent<components::Gravity>(index);
    if (gravityC == nullptr)
        return;
    components::HealthComponent *compLife =
        this->componentManager_->getComponent<components::HealthComponent>(
            index);
    components::MasseComponent *MasseComp =
        this->componentManager_->getComponent<components::MasseComponent>(
            index);
    components::ForceComponent *ForceComp =
        this->componentManager_->getComponent<components::ForceComponent>(
            index);
    components::PosComponent *PosComp =
        this->componentManager_->getComponent<components::PosComponent>(index);
    if (MasseComp)
        generateProprietyRange(&MasseComp->masse, MasseComp->_initMasse, 1, 1);
    if (compLife)
        generateProprietyRange(&compLife->health, compLife->_initHealth,
            compLife->_rangeMin, compLife->_rangeMax);
    if (ForceComp)
        generateVectorProprietyRange(&ForceComp->force, ForceComp->_initForce,
            ForceComp->_rangeMin, ForceComp->_rangeMax);
    if (PosComp) {
        generateVectorProprietyRange(&PosComp->pos, PosComp->_initPos,
            PosComp->_rangeMin, PosComp->_rangeMax);
    }

    float masse = (MasseComp ? MasseComp->masse : 0);
    sf::Vector2f force = (ForceComp ? ForceComp->force : sf::Vector2f(0, 0));
    gravityC->_cur_S[0] = masse * force;
    gravityC->_cur_S[1] = sf::Vector2f(PosComp->pos.x, PosComp->pos.y);
}

void ResetSystem::update(long elapsedTime)
{
    auto array = this->componentManager_
                     ->getComponentList<components::HealthComponent>();
    for (auto it = array.begin(); it != array.end(); ++it) {
        components::HealthComponent *Comp =
            static_cast<components::HealthComponent *>(it->second);
        if (Comp == nullptr)
            break;
        if (Comp && Comp->health <= 0) {
            reset(it->first);
        }
    }
}

} // namespace systems