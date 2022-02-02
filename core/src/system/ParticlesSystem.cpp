#include "system/ParticlesSystem.hpp"

namespace systems {

void ParticlesSystem::reset(int index)
{
    components::Gravity *gravityC =
        this->componentManager_->getComponent<components::Gravity>(index);
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
    components::SpawnPos *SpawnPosC =
        this->componentManager_->getComponent<components::SpawnPos>(index);
    if (MasseComp)
        generateProprietyRange(&MasseComp->masse, MasseComp->_initMasse, 1, 1);
    if (compLife)
        generateProprietyRange(&compLife->health, compLife->_initHealth,
            compLife->_rangeMin, compLife->_rangeMax);
    if (ForceComp)
        generateVectorProprietyRange(&ForceComp->force, ForceComp->_initForce,
            ForceComp->_rangeMin, ForceComp->_rangeMax);
    if (PosComp && SpawnPosC) {
        generateVectorProprietyRange(&PosComp->_pos, SpawnPosC->_initPos,
            SpawnPosC->_rangeMin, SpawnPosC->_rangeMax);
    }

    float masse = (MasseComp ? MasseComp->masse : 0);
    sf::Vector2f force = (ForceComp ? ForceComp->force : sf::Vector2f(0, 0));
    if (gravityC && PosComp) {
        gravityC->_cur_S[0] = masse * force;
        gravityC->_cur_S[1] = sf::Vector2f(PosComp->_pos.x, PosComp->_pos.y);
    }
}

void ParticlesSystem::update(long elapsedTime)
{
    auto array = this->componentManager_
                     ->getComponentList<components::ParticleIdentity>();

    for (auto it = array.begin(); it != array.end(); ++it) {
        components::PosComponent *PosC =
            this->componentManager_->getComponent<components::PosComponent>(
                it->first);
        if (PosC == nullptr)
            break;

        components::HealthComponent *compLife =
            this->componentManager_->getComponent<components::HealthComponent>(
                it->first);
        if (!compLife || compLife->health > 0) {
            (*_vertexArray)[it->first].position =
                sf::Vector2f(PosC->_pos.x, PosC->_pos.y);
        } else if (compLife && compLife->health <= 0) {
            reset(it->first);
        }
    }
}
} // namespace systems