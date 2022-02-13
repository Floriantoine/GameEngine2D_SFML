#include "system/ParticlesSystem.hpp"
#include "Game.hpp"

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
    if (gravityC) {
        gravityC->_cur_S = masse * force;
    }
}

void ParticlesSystem::update(long elapsedTime)
{
    tools::Chrono::start();

    _elapsedTime += elapsedTime;
    if (_elapsedTime < 16)
        return;
    _elapsedTime = 0;
    auto array = this->componentManager_
                     ->getComponentList<components::ParticleIdentity>();

    if (array.size() != _vertexArray.getVertexCount())
        _vertexArray.resize(array.size());

    for (auto it = array.begin(); it != array.end(); ++it) {
        components::ParticleIdentity *identity =
            static_cast<components::ParticleIdentity *>(it->second);

        if (identity->_isInit == false) {
            reset(it->first);
            identity->_isInit = true;
        } else {
            components::HealthComponent *compLife =
                this->componentManager_
                    ->getComponent<components::HealthComponent>(it->first);
            if (!compLife || compLife->health > 0) {
                components::PosComponent *PosC =
                    this->componentManager_
                        ->getComponent<components::PosComponent>(it->first);
                if (PosC != nullptr) {
                    _vertexArray[it->first].position =
                        sf::Vector2f(PosC->_pos.x, PosC->_pos.y);
                }
            } else if (compLife && compLife->health <= 0) {
                components::LoopLife *loopLife =
                    this->componentManager_->getComponent<components::LoopLife>(
                        it->first);
                if (loopLife) {
                    reset(it->first);
                } else {
                    this->componentManager_->removeAllComponents(it->first);
                }
            }
        }
    }
    Game::Game::getInstance().getWindow()->draw(_vertexArray);

    tools::Chrono::end("particleSystem");
}
} // namespace systems