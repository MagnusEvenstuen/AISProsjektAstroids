#ifndef ASTROIDS_CONTROLS_HPP
#define ASTROIDS_CONTROLS_HPP
#define _USE_MATH_DEFINES

#include "ObjectCreator.hpp"
#include "LaserControls.hpp"
#include <vector>
#include <cmath>
#include <iostream>

using namespace threepp;
namespace {
    class Controls : public KeyListener {

    public:
        Controls(std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& obj, std::shared_ptr<Scene>& scene, const int& boardSize)
            :obj_(obj), scene_(scene), boardSize_(boardSize) {
        }
        void onKeyPressed(const KeyEvent evt) override{
            if (evt.key == Key::W) {
                speed_ += 1;
            }
            if (evt.key == Key::A) {
                rotaition_ += M_PI/180;
            }
            if (evt.key == Key::D) {
                rotaition_ -= M_PI/180;
            }
            if (evt.key == Key::SPACE) {
                laserControls_.createLaser(scene_, obj_.first);
            }
        }
        void onKeyReleased(const KeyEvent evt) override {
            if (evt.key == Key::W) {
                speed_ -= 1;
            }
            if (evt.key == Key::A) {
                rotaition_ -= M_PI/180;
            }
            if (evt.key == Key::D) {
                rotaition_ += M_PI/180;
            }
        }

        std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getLasers(){
            return laserControls_.getLasers();
        }

        void setDeltaTime(const float dt) {
            dt_ = dt;
        }

        void setSpeed() {
            obj_.second->rotation += rotaition_ * dt_ * 200;
            obj_.first->rotation.z += rotaition_ * dt_ * 200;
            Vector2 direction(cos(obj_.first->rotation.z()), sin(obj_.first->rotation.z()));

            ObjectUpdater::moveObject(obj_.first, direction, dt_, speedMultiplier_ * speed_);
            ObjectUpdater::loopObject(obj_.first, boardSize_);

            laserControls_.setLaserSpeed(direction[0], direction[1]);
            laserControls_.updateLasers(scene_, dt_, boardSize_);
        }

    private:
        const float speedMultiplier_ = 15;
        float dt_{0};
        float speed_ = 0;
        float rotaition_ = 0;
        int boardSize_ = 0;
        std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> &obj_;
        std::shared_ptr<Scene> scene_;
        LaserControls laserControls_;
    };
}
#endif //ASTROIDS_CONTROLS_HPP