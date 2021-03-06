#include "system/ParticlesSystem.hpp"
#include "Game.hpp"

namespace systems {

void ParticlesSystem::reset(fa::id_t index)
{
    components::RigideBody *gravityC =
        this->_componentManager->getComponent<components::RigideBody>(index);
    components::HealthComponent *compLife =
        this->_componentManager->getComponent<components::HealthComponent>(
            index);
    components::MasseComponent *MasseComp =
        this->_componentManager->getComponent<components::MasseComponent>(
            index);
    components::ForceComponent *ForceComp =
        this->_componentManager->getComponent<components::ForceComponent>(
            index);
    components::PosComponent *PosComp =
        this->_componentManager->getComponent<components::PosComponent>(index);
    components::Size *SizeComp =
        this->_componentManager->getComponent<components::Size>(index);
    components::SpawnPos *SpawnPosC =
        this->_componentManager->getComponent<components::SpawnPos>(index);
    components::SolidBlock *solidBlockC =
        this->_componentManager->getComponent<components::SolidBlock>(index);
    if (MasseComp != nullptr)
        generateProprietyRange(&MasseComp->masse, MasseComp->_initMasse, 1, 1);
    if (compLife != nullptr)
        generateProprietyRange(&compLife->health, compLife->_initHealth,
            compLife->_rangeMin, compLife->_rangeMax);
    if (ForceComp != nullptr)
        generateVectorProprietyRange(&ForceComp->force, ForceComp->_initForce,
            ForceComp->_rangeMin, ForceComp->_rangeMax);
    if (PosComp != nullptr && SpawnPosC != nullptr) {
        generateVectorProprietyRange(&PosComp->_pos, SpawnPosC->_initPos,
            SpawnPosC->_rangeMin, SpawnPosC->_rangeMax);
    }
    if (SizeComp != nullptr) {
        generateVectorProprietyRange(&SizeComp->_size, SizeComp->_initSize,
            SizeComp->_rangeMin, SizeComp->_rangeMax);
    }
    if (solidBlockC != nullptr) {
        solidBlockC->_haveCollision = false;
    }

    float masse = (MasseComp != nullptr ? MasseComp->masse : 0);
    sf::Vector2f force =
        (ForceComp != nullptr ? ForceComp->force : sf::Vector2f(0, 0));
    if (gravityC != nullptr) {
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
    auto array = this->_componentManager
                     ->getComponentList<components::ParticleIdentity>();

    if ((_vertexArray.getPrimitiveType() == sf::PrimitiveType::Points &&
            array.size() != _vertexArray.getVertexCount()) ||
        (_vertexArray.getPrimitiveType() == sf::PrimitiveType::Quads &&
            array.size() != _vertexArray.getVertexCount() / 4)) {
        if (array.size() == 0) {
            _vertexArray.clear();
        } else {
            components::ParticleIdentity *identity =
                this->_componentManager
                    ->getComponent<components::ParticleIdentity>(
                        array.begin()->first);
            if (identity != nullptr) {
                if (identity->_type == sf::PrimitiveType::Points) {
                    _vertexArray.resize(array.size());
                    _vertexArray.setPrimitiveType(sf::PrimitiveType::Points);
                } else if (identity->_type == sf::PrimitiveType::Quads) {
                    _vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);
                    _vertexArray.resize(array.size() * 4);
                }
            }
        }
    }

    int i = 0;
    for (auto &it: array) {
        components::ParticleIdentity *identity =
            static_cast<components::ParticleIdentity *>(it.second);

        if (identity->_isInit == false) {
            reset(it.first);
            identity->_isInit = true;
        } else {
            components::HealthComponent *compLife =
                this->_componentManager
                    ->getComponent<components::HealthComponent>(it.first);
            if (!compLife || compLife->health > 0) {
                components::PosComponent *PosC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(it.first);
                if (PosC != nullptr) {
                    components::Color *colorC =
                        this->_componentManager
                            ->getComponent<components::Color>(it.first);
                    if (identity->_type != sf::PrimitiveType::Quads) {
                        _vertexArray[i].position =
                            sf::Vector2f(PosC->_pos.x, PosC->_pos.y);
                        if (colorC != nullptr) {
                            _vertexArray[i].color = colorC->_color;
                        }
                    } else if (identity->_type == sf::PrimitiveType::Quads) {
                        components::Size *sizeC =
                            this->_componentManager
                                ->getComponent<components::Size>(it.first);
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
                    this->_componentManager->getComponent<components::LoopLife>(
                        it.first);
                if (loopLife) {
                    reset(it.first);
                } else {
                    Game::Game::getInstance().getEntityFactory().destroyEntity(
                        it.first);
                }
            }
            i++;
        }
    }
    Game::Game::getInstance().getWindow()->draw(_vertexArray);

    tools::Chrono::end("particleSystem");
}
} // namespace systems