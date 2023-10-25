#ifndef PLACEHOLDER_LAZARCONTROLS_HPP
#define PLACEHOLDER_LAZARCONTROLS_HPP
using namespace threepp;
namespace {
    class LazarControls {
    public:


        void setLazarSpeed(const int speedX, const int speedY) {
            lazarSpeedX_ = speedX;
            lazarSpeedY_ = speedY;
        }

        void createLazar(const std::shared_ptr<Scene> scene, const Object3D &obj) {
            auto lazar = std::make_shared<Object>();
            lazars_.push_back(lazar);
            creationTime_.push_back(0);
            lazar->setColor(Color::red);
            scene->add(*lazar);
            lazar->position.y = obj.position.y;
            lazar->position.x = obj.position.x;

            lazarSpeeds_.push_back(std::make_pair(lazarSpeedX_, lazarSpeedY_));
        }

        void updateLazars(const std::shared_ptr<Scene> scene, const double dt) {
            for (size_t i = 0; i < lazars_.size(); ++i) {   //Modifisert ChatGPT kode
                auto lazar = lazars_[i];
                lazar->position.x += lazarSpeeds_[i].first * dt * speedMultiplier_;
                lazar->position.y += lazarSpeeds_[i].second * dt * speedMultiplier_;
                creationTime_[i] += dt;    //Slutt modifisert ChatGPT kode
                if (creationTime_[i] >= 2) {
                    scene->remove(*lazar);
                    lazars_.erase(lazars_.begin() + i);
                    creationTime_.erase(creationTime_.begin() + i);
                    lazarSpeeds_.erase(lazarSpeeds_.begin() + i);
                    i--;
                }
            }
        }

    private:
        int lazarSpeedX_ = 0;
        int lazarSpeedY_ = 0;
        int speedMultiplier_ = 40;
        std::vector<double> creationTime_;
        std::vector<std::shared_ptr<Object>> lazars_;
        std::vector<std::pair<int, int>> lazarSpeeds_;
    };
}
#endif //PLACEHOLDER_LAZARCONTROLS_HPP
