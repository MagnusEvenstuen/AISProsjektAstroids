#ifndef PLACEHOLDER_CONTROLS_HPP
#define PLACEHOLDER_CONTROLS_HPP

#include "objectCreator.hpp"
#include "lazarControls.hpp"
#include <astroid.hpp>
#include <vector>

using namespace threepp;
namespace {
    class Controls : public KeyListener {

    public:
        Controls(Object3D &obj, const std::shared_ptr<Scene> scene) : obj_(obj), scene_(scene) {
        }

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
            if (evt.key == Key::SPACE) {
                lazarControls.createLazar(scene_, obj_);
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
                obj_.position.x += (speedMultiplier_ * speedX_ * dt_) / 2;
                obj_.position.y += (speedMultiplier_ * speedY_ * dt_) / 2;
                lazarControls.setLazarSpeed(speedX_, speedY_);
            } else if (speedY_ == 0 && speedX_ != 0 || speedY_ != 0 && speedX_ == 0) {
                obj_.position.y += speedMultiplier_ * speedY_ * dt_;
                obj_.position.x += speedMultiplier_ * speedX_ * dt_;
                lazarControls.setLazarSpeed(speedX_, speedY_);
            }
            if (!speed_.empty() && speedY_ != 0 || !speed_.empty() && speedX_ != 0) {
                speed_.erase(speed_.begin());
                speed_.push_back(std::make_pair(speedX_, speedY_));
            }
            if (!speed_.empty() && speedY_ == 0 && speedX_ == 0) {
                lazarControls.setLazarSpeed(speed_[0].first, speed_[0].second);
            }

            lazarControls.updateLazars(scene_, dt_);
        }

    private:
        int speedMultiplier_ = 10;
        float dt_{0};
        int speedY_ = 0;
        int speedX_ = 0;
        std::vector<std::pair<int, int>> speed_;
        Object3D &obj_;
        std::shared_ptr<Scene> scene_;
        std::vector<std::shared_ptr<Object>> lazars_;
        LazarControls lazarControls;
    };
}
#endif //PLACEHOLDER_CONTROLS_HPP