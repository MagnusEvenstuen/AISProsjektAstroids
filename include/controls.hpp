#ifndef ASTROIDS_CONTROLS_HPP
#define ASTROIDS_CONTROLS_HPP

#include "threepp/threepp.hpp"
#include "LaserControls.hpp"

using namespace threepp;
class Controls: public KeyListener {

public: Controls(std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& obj, std::shared_ptr<Scene>& scene,
             const int & boardSize): obj_(obj), scene_(scene), boardSize_(boardSize) {}
    void onKeyPressed(const KeyEvent evt) override;

    void onKeyReleased(const KeyEvent evt) override;

    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getLasers();

    void setDeltaTime(const float dt);

    void setSpeed();

private: const float speedMultiplier_ = 15;
    float dt_ {0};
    float speed_ = 0;
    int boardSize_ = 0;
    bool leftPressed_ = false;
    bool rightPressed_ = false;
    std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& obj_;
    std::shared_ptr<Scene> scene_;
    LaserControls laserControls_;
};
#endif //ASTROIDS_CONTROLS_HPP