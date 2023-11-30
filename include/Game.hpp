#ifndef ASTROIDS_GAME_HPP
#define ASTROIDS_GAME_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Game{
public:
    static std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>
    startGame(const std::string& backgroundImage, const std::string& shipImage, std::shared_ptr<Scene>& scene,
              const int& boardSize);

    static void resetGame(std::shared_ptr<Scene>& scene, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& lasers,
                          std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& enemyLasers, std::vector<Vector2>& astroidSpeeds, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& astroids,
                          std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& enemyShips);
};

#endif//ASTROIDS_GAME_HPP
