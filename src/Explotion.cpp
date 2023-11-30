#include "Explotion.hpp"
#include "ObjectCreator.hpp"
#include "ObjectUpdater.hpp"
#include <random>

void ExplotionCreator::createExpolotion(const float & xPos, const float & yPos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < 50; i++) {
        auto explotionParticle = ObjectCreator::createSprite(1, 1);
        explotionParticle.second -> color = explotionColor;
        explotionParticles_.push_back(explotionParticle);
        yellow_.push_back(1);
        scene_ -> add(explotionParticles_.back().first);
        explotionParticles_.back().first -> position.y = yPos;
        explotionParticles_.back().first -> position.x = xPos;

        std::uniform_real_distribution < float > speedDistribution(-4, 4);
        explotionParticleSpeeds_.emplace_back(speedDistribution(gen), speedDistribution(gen));
    }
}

void ExplotionCreator::moveExplotion(const float & dt) {
    for (int i = 0; i < explotionParticles_.size(); i++) {
        yellow_[i] -= 1.0f * dt;
        ObjectUpdater::moveObject(explotionParticles_[i].first, explotionParticleSpeeds_[i], dt);
        explotionParticles_[i].first -> scale.x -= 1 * dt;
        explotionParticles_[i].first -> scale.y -= 1 * dt;
        explotionColor = Color(1, yellow_[i], 0);
        explotionParticles_[i].second -> color = explotionColor;
        if (explotionParticles_[i].first -> scale.x < 0 || explotionParticles_[i].first -> scale.y < 0) {
            scene_ -> remove( * explotionParticles_[i].first);
            explotionParticles_.erase(explotionParticles_.begin() + i);
            explotionParticleSpeeds_.erase(explotionParticleSpeeds_.begin() + i);
            yellow_.erase(yellow_.begin() + i);
        }
    }
}