#ifndef PLACEHOLDER_CONTROLS_HPP
#define PLACEHOLDER_CONTROLS_HPP
#define _USE_MATH_DEFINES

#include "objectCreator.hpp"
#include "lazarControls.hpp"
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
                lazarControls_.createLasar(scene_, obj_);
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
            return lazarControls_.getLasars();
        }

        void setDeltaTime(const float dt) {
            dt_ = dt;
        }

        void setSpeed() {
            obj_.rotation.z += rotaition_ * dt_ * 200;
            Vector3 direction(cos(obj_.rotation.z()), sin(obj_.rotation.z()), 0);
            obj_.position.x += speed_ * dt_ * speedMultiplier_ * direction[0];
            obj_.position.y += speed_ * dt_ * speedMultiplier_ * direction[1];
            if (obj_.position.x > 30 || obj_.position.x < -30){
                obj_.position.x *= -1;
            } else if (obj_.position.y > 30 || obj_.position.y < -30){
                obj_.position.y *= -1;
            }
            lazarControls_.setLasarSpeed(direction[0], direction[1]);
            lazarControls_.updateLasars(scene_, dt_);
        }

    private:
        const float speedMultiplier_ = 10;
        float dt_{0};
        float speed_ = 0;
        float rotaition_ = 0;
        Object3D &obj_;
        std::shared_ptr<Scene> scene_;
        std::vector<std::shared_ptr<Object>> lazars_;
        LasarControls lazarControls_;
    };
}
#endif //PLACEHOLDER_CONTROLS_HPP