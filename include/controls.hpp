#ifndef PLACEHOLDER_CONTROLS_HPP
#define PLACEHOLDER_CONTROLS_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "objectCreator.hpp"
#include <vector>

using namespace threepp;
namespace {
    class Controls : public KeyListener {

    public:
        Controls(Object3D &obj) : obj_(obj) {}

        void onKeyPressed(const KeyEvent evt) {
            if (evt.key == Key::W) {
                speedY_ += 1;
            }
            if (evt.key == Key::S) {
                speedY_ -= 1;
            }
            if (evt.key == Key::A) {
                speedX_ -= 1;
            }
            if (evt.key == Key::D) {
                speedX_ += 1;
            }
        }

        void onKeyReleased(const KeyEvent evt) override {
            if (evt.key == Key::W) {
                speedY_ -= 1;
            }
            if (evt.key == Key::S) {
                speedY_ += 1;
            }
            if (evt.key == Key::A) {
                speedX_ += 1;
            }
            if (evt.key == Key::D) {
                speedX_ -= 1;
            }
        }

        void setDeltaTime(const float dt) {
            dt_ = dt;
        }

        void setSpeed() {
            if (speedY_ != 0 && speedX_ != 0) {
                obj_.position.x += (5 * speedX_ * dt_) / 2;
                obj_.position.y += (5 * speedY_ * dt_) / 2;
            } else {
                obj_.position.y += 5 * speedY_ * dt_;
                obj_.position.x += 5 * speedX_ * dt_;
            }
        }

    private:
        float dt_{0};
        int speedY_ = 0;
        int speedX_ = 0;
        Object3D &obj_;
    };
}
#endif //PLACEHOLDER_CONTROLS_HPP
