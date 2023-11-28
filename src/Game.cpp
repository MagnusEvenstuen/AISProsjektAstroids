#include "Game.hpp"

std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> Game::startGame(const std::string& backgroundImage, const std::string& shipImage, std::shared_ptr<Scene>& scene, const int& boardSize) {
    auto background = ObjectCreator::createSprite(boardSize * 2, boardSize * 2, backgroundImage).first;
    scene->add(background);

    auto ship = ObjectCreator::createSprite(5, 5, shipImage);
    scene->add(ship.first);

    return ship;
}

void Game::resetGame(std::shared_ptr<Scene>& scene, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& lasers, std::vector<Vector2>& astroidSpeeds, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& astroids, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& enemyShips) {
    scene->clear();
    lasers.clear();
    astroids.clear();
    astroidSpeeds.clear();
    enemyShips.clear();
}
