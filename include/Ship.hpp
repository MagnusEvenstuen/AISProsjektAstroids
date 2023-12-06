#ifndef ASTROIDS_SHIP_HPP
#define ASTROIDS_SHIP_HPP

#include "BaseShip.hpp"
#include "ObjectCreator.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;
class Ship: public KeyListener, public BaseShip {

public:
    Ship(std::shared_ptr<Scene>& scene, const int boardSize);

    void onKeyPressed(const KeyEvent evt) override;

    void onKeyReleased(const KeyEvent evt) override;

    void move (const float dt);

private: bool leftPressed_ = false;
    bool rightPressed_ = false;
    std::shared_ptr<Scene> scene_;
};
#endif//ASTROIDS_SHIP_HPP