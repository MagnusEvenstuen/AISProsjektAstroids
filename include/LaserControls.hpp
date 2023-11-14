#ifndef PLACEHOLDER_LASERCONTROLS_HPP
#define PLACEHOLDER_LASERCONTROLS_HPP

class LaserControls {
public:


    void setLasarSpeed(const float speedX, const float speedY) {
        laserSpeedX_ = speedX;
        laserSpeedY_ = speedY;
    }

    void createLasar(const std::shared_ptr<Scene>& scene, const Object3D &obj) {
        auto lasar = std::make_shared<Object>();
        lasers_.push_back(lasar);
        lasar->setColor(Color::red);
        scene->add(*lasar);
        lasar->position.y = obj.position.y;
        lasar->position.x = obj.position.x;

        laserSpeeds_.emplace_back(laserSpeedX_, laserSpeedY_);
    }

    void updateLasars(const std::shared_ptr<Scene>& scene, const float dt) {
        for (long long i = 0; i < lasers_.size(); i++) {   //Modifisert ChatGPT kode
            auto lasar = lasers_[i];
            lasar->position.x += laserSpeeds_[i].first * dt * speedMultiplier_;
            lasar->position.y += laserSpeeds_[i].second * dt * speedMultiplier_;    //Slutt modifisert ChatGPT kode
            if (lasar->position.x > 30 || lasar->position.x < -30 || lasar->position.y > 30 || lasar->position.y < -30) {
                lasers_.erase(lasers_.begin() + i);
                laserSpeeds_.erase(laserSpeeds_.begin() + i);
                scene->remove(*lasar);
                i--;
            }
        }
    }

    std::vector<std::shared_ptr<Object>>& getLasars(){
        return lasers_;
    }

private:
    float laserSpeedX_ = 0;
    float laserSpeedY_ = 0;
    const float speedMultiplier_ = 40;
    std::vector<std::shared_ptr<Object>> lasers_;
    std::vector<std::pair<float, float>> laserSpeeds_;
};
#endif //PLACEHOLDER_LASERCONTROLS_HPP
