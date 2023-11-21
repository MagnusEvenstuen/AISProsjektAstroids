#ifndef PLACEHOLDER_LASERCONTROLS_HPP
#define PLACEHOLDER_LASERCONTROLS_HPP

class LaserControls {
public:


    void setLasarSpeed(const float speedX, const float speedY) {
        laserSpeedX_ = speedX;
        laserSpeedY_ = speedY;
    }

    void createLasar(std::shared_ptr<Scene>& scene, const std::shared_ptr<Sprite>& obj) {
        auto laser = std::make_shared<Object>();
        lasers_.push_back(laser);
        laser->setColor(Color::red);
        scene->add(lasers_.back());
        laser->position.y = obj->position.y;
        laser->position.x = obj->position.x;

        laserSpeeds_.emplace_back(laserSpeedX_, laserSpeedY_);
    }

    void updateLasars(std::shared_ptr<Scene>& scene, const float dt, const int& boardSize) {
        for (long long i = 0; i < lasers_.size(); i++) {   //Modifisert ChatGPT kode
            auto laser = lasers_[i];
            laser->position.x += laserSpeeds_[i].first * dt * speedMultiplier_;
            laser->position.y += laserSpeeds_[i].second * dt * speedMultiplier_;    //Slutt modifisert ChatGPT kode
            if (laser->position.x > boardSize + 2 || laser->position.x < -boardSize - 2 || laser->position.y > boardSize + 2 || laser->position.y < -boardSize - 2) {
                lasers_.erase(lasers_.begin() + i);
                laserSpeeds_.erase(laserSpeeds_.begin() + i);
                scene->remove(*laser);
                i--;
            }
        }
    }

    std::vector<std::shared_ptr<Object>>& getLasers(){
        return lasers_;
    }

    std::vector<std::pair<float, float>>& getLaserSpeeds(){
        return laserSpeeds_;
    }

private:
    float laserSpeedX_ = 0;
    float laserSpeedY_ = 0;
    const float speedMultiplier_ = 40;
    std::vector<std::shared_ptr<Object>> lasers_;
    std::vector<std::pair<float, float>> laserSpeeds_;
};
#endif //PLACEHOLDER_LASERCONTROLS_HPP
