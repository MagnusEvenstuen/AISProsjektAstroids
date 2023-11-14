#ifndef PLACEHOLDER_CONTROLS_HPP
#define PLACEHOLDER_CONTROLS_HPP
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
        Controls(Object3D &obj, const std::shared_ptr<Scene>& scene) : obj_(obj), scene_(scene) {
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
                laserControls_.createLasar(scene_, obj_);
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

        std::vector<std::shared_ptr<Object>>& getLasars(){
            return laserControls_.getLasars();
        }

        void setDeltaTime(const float dt) {
            dt_ = dt;
        }

        void setSpeed(std::shared_ptr<SpriteMaterial>& image) {
            image->rotation += rotaition_ * dt_ * 200;
            obj_.rotation.z += rotaition_ * dt_ * 200;
            Vector2 direction(cos(obj_.rotation.z()), sin(obj_.rotation.z()));
            obj_.position.x += speed_ * dt_ * speedMultiplier_ * direction[0];
            obj_.position.y += speed_ * dt_ * speedMultiplier_ * direction[1];
            if (obj_.position.x > 30 || obj_.position.x < -30){
                obj_.position.x *= -1;
            } else if (obj_.position.y > 30 || obj_.position.y < -30){
                obj_.position.y *= -1;
            }
            laserControls_.setLasarSpeed(direction[0], direction[1]);
            laserControls_.updateLasars(scene_, dt_);
        }

    private:
        const float speedMultiplier_ = 15;
        float dt_{0};
        float speed_ = 0;
        float rotaition_ = 0;
        Object3D &obj_;
        std::shared_ptr<Scene> scene_;
        LaserControls laserControls_;
    };
}
#endif //PLACEHOLDER_CONTROLS_HPP