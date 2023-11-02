#ifndef PLACEHOLDER_CONTROLS_HPP
#define PLACEHOLDER_CONTROLS_HPP

#include "objectCreator.hpp"
#include "lazarControls.hpp"
#include <vector>
#include <iostream>

using namespace threepp;
namespace {
    class Controls : public KeyListener {

    public:
        Controls(Object3D &obj, const std::shared_ptr<Scene>& scene) : obj_(obj), scene_(scene) {
        }

        void onKeyPressed(const KeyEvent evt) override {
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
            if (evt.key == Key::SPACE) {
                lazarControls_.createLasar(scene_, obj_);
            }
        }

        std::vector<std::shared_ptr<Object>>& getLasars(){
            return lazarControls_.getLasars();
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
                obj_.position.x += (speedMultiplier_ * speedX_ * dt_) / 2;
                obj_.position.y += (speedMultiplier_ * speedY_ * dt_) / 2;
                lazarControls_.setLasarSpeed(speedX_, speedY_);
            } else if (speedY_ == 0 && speedX_ != 0 || speedY_ != 0 && speedX_ == 0) {
                obj_.position.y += speedMultiplier_ * speedY_ * dt_;
                obj_.position.x += speedMultiplier_ * speedX_ * dt_;
                lazarControls_.setLasarSpeed(speedX_, speedY_);
            }
            if (obj_.position.x > 30 || obj_.position.x < -30){
                obj_.position.x *= -1;
            }
            if (obj_.position.y > 30 || obj_.position.y < -30){
                obj_.position.y *= -1;
            }
            if (!speed_.empty() && speedY_ != 0 || !speed_.empty() && speedX_ != 0) {
                speed_.erase(speed_.begin());
                speed_.emplace_back(speedX_, speedY_);
            }
            if (!speed_.empty() && speedY_ == 0 && speedX_ == 0) {
                lazarControls_.setLasarSpeed(speed_[0].first, speed_[0].second);
            }

            lazarControls_.updateLasars(scene_, dt_);
        }

    private:
        const float speedMultiplier_ = 10;
        float dt_{0};
        float speedY_ = 0;
        float speedX_ = 0;
        std::vector<std::pair<float, float>> speed_;
        Object3D &obj_;
        std::shared_ptr<Scene> scene_;
        std::vector<std::shared_ptr<Object>> lazars_;
        LasarControls lazarControls_;
    };
}
#endif //PLACEHOLDER_CONTROLS_HPP