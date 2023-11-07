#ifndef PLACEHOLDER_LAZARCONTROLS_HPP
#define PLACEHOLDER_LAZARCONTROLS_HPP

class LasarControls {
public:


    void setLasarSpeed(const float speedX, const float speedY) {
        lasarSpeedX_ = speedX;
        lasarSpeedY_ = speedY;
    }

    void createLasar(const std::shared_ptr<Scene>& scene, const Object3D &obj) {
        auto lasar = std::make_shared<Object>();
        lasars_.push_back(lasar);
        lasar->setColor(Color::red);
        scene->add(*lasar);
        lasar->position.y = obj.position.y;
        lasar->position.x = obj.position.x;

        lasarSpeeds_.emplace_back(lasarSpeedX_, lasarSpeedY_);
    }

    void updateLasars(const std::shared_ptr<Scene>& scene, const float dt) {
        for (size_t i = 0; i < lasars_.size(); i++) {   //Modifisert ChatGPT kode
            auto lasar = lasars_[i];
            lasar->position.x += lasarSpeeds_[i].first * dt * speedMultiplier_;
            lasar->position.y += lasarSpeeds_[i].second * dt * speedMultiplier_;    //Slutt modifisert ChatGPT kode
            if (lasar->position.x > 30 || lasar->position.x < -30 || lasar->position.y > 30 || lasar->position.y < -30) {
                lasars_.erase(lasars_.begin() + i);
                lasarSpeeds_.erase(lasarSpeeds_.begin() + i);
                scene->remove(*lasar);
                i--;
            }
        }
    }

    std::vector<std::shared_ptr<Object>>& getLasars(){
        return lasars_;
    }

private:
    float lasarSpeedX_ = 0;
    float lasarSpeedY_ = 0;
    const float speedMultiplier_ = 40;
    std::vector<std::shared_ptr<Object>> lasars_;
    std::vector<std::pair<float, float>> lasarSpeeds_;
};
#endif //PLACEHOLDER_LAZARCONTROLS_HPP
