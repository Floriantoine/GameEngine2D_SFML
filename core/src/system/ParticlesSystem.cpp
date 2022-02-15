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
    components::Size *SizeComp =
        this->componentManager_->getComponent<components::Size>(index);
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
    if (SizeComp) {
        generateVectorProprietyRange(&SizeComp->_size, SizeComp->_initSize,
            SizeComp->_rangeMin, SizeComp->_rangeMax);
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

    if (array.size() != _vertexArray.getVertexCount()) {
        if (array.size() == 0) {
            _vertexArray.clear();
        } else {
            components::ParticleIdentity *identity =
                this->componentManager_
                    ->getComponent<components::ParticleIdentity>(
                        array.begin()->first);
            if (!identity || identity->_type == sf::PrimitiveType::Points) {
                _vertexArray.resize(array.size());
                _vertexArray.setPrimitiveType(sf::PrimitiveType::Points);
            } else if (identity->_type == sf::PrimitiveType::Quads) {
                _vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);
                _vertexArray.resize(array.size() * 4);
            }
        }
    }

    int i = 0;
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
                    components::Color *colorC =
                        this->componentManager_
                            ->getComponent<components::Color>(it->first);
                    if (identity->_type != sf::PrimitiveType::Quads) {
                        _vertexArray[i].position =
                            sf::Vector2f(PosC->_pos.x, PosC->_pos.y);
                        if (colorC != nullptr) {
                            _vertexArray[i].color = colorC->_color;
                        }
                    } else if (identity->_type == sf::PrimitiveType::Quads) {
                        components::Size *sizeC =
                            this->componentManager_
                                ->getComponent<components::Size>(it->first);
                        sf::Vector2f size =
                            (sizeC ? sizeC->_size : sf::Vector2f(1, 1));
                        int index = i * 4;
                        _vertexArray[index].position =
                            sf::Vector2f(PosC->_pos.x, PosC->_pos.y);
                        _vertexArray[index + 1].position =
                            sf::Vector2f(PosC->_pos.x + size.x, PosC->_pos.y);
                        _vertexArray[index + 2].position = sf::Vector2f(
                            PosC->_pos.x + size.x, PosC->_pos.y + size.y);
                        _vertexArray[index + 3].position =
                            sf::Vector2f(PosC->_pos.x, PosC->_pos.y + size.y);
                        if (colorC != nullptr) {
                            _vertexArray[index].color = colorC->_color;
                            _vertexArray[index + 1].color = colorC->_color;
                            _vertexArray[index + 2].color = colorC->_color;
                            _vertexArray[index + 3].color = colorC->_color;
                        }
                    }
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
            i++;
        }
    }
    Game::Game::getInstance().getWindow()->draw(_vertexArray);

    tools::Chrono::end("particleSystem");
}
} // namespace systems