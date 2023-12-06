#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CollitionDetection.hpp"
#include "GameLoop.hpp"
#include "Laser.hpp"
#include "Ship.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

TEST_CASE("Astroid updates true") {
    std::shared_ptr<Scene> scene = Scene::create();

    Astroid astroid(35, scene);

    std::shared_ptr<Sprite> astroidObject = astroid.getSprite();
    astroidObject->position.x = 100;
    astroidObject->position.y = 100;

    float dt = 0.016;
    bool result = astroid.update(dt);

    REQUIRE(result == true);
}

TEST_CASE("Astroid updates false") {
    std::shared_ptr<Scene> scene = Scene::create();

    Astroid astroid(35, scene);

    Vector3 position = astroid.getPosition();
    position.x = 10;
    position.y = 20;

    float dt = 0.016;
    bool result = astroid.update(dt);

    REQUIRE(result == false);
}

TEST_CASE("Astroid Collition"){
    std::shared_ptr<Scene> scene = Scene::create();

    std::vector<std::shared_ptr<Astroid>> astroids;

    astroids.push_back(std::make_shared<Astroid>(35, scene));
    astroids.push_back(std::make_shared<Astroid>(35, scene));
    astroids.push_back(std::make_shared<Astroid>(35, scene));

    std::shared_ptr<Sprite> astroidObject = astroids[0]->getSprite();
    astroidObject->position.x = 10;
    astroidObject->position.y = 15;


    std::shared_ptr<Sprite> astroidV0Object = astroids[1]->getSprite();
    astroidV0Object->position.x = 10;
    astroidV0Object->position.y = 15;

    Vector2 astroidV0Speed = astroids[0]->getObjectSpeed();
    Vector2 astroidV1Speed = astroids[1]->getObjectSpeed();
    Vector2 astroidV2Speed = astroids[2]->getObjectSpeed();

    std::shared_ptr<Sprite> astroidV1Object = astroids[2]->getSprite();
    astroidV1Object->position.x = -15;
    astroidV1Object->position.y = -10;

    for (auto& astroid : astroids) {
        astroid->checkAstroidCollition(astroids);
    }
    REQUIRE(astroidV0Speed != astroids[0] -> getObjectSpeed());     //Could check if it got correct speed
    REQUIRE(astroidV1Speed != astroids[1] -> getObjectSpeed());     //But I think a different speed is good enough
    REQUIRE(astroidV2Speed == astroids[2] -> getObjectSpeed());
}

TEST_CASE("Astroid Spawner"){
    std::shared_ptr<Scene> scene = Scene::create();
    Ship ship(scene, 35);
    int numberOfAstroids = 20;

    GameLoop gameLoop(35, ship, scene);
    gameLoop.createAstroids(numberOfAstroids);

    std::vector<std::shared_ptr<Astroid>> astroids = gameLoop.getAstroids();

    REQUIRE(numberOfAstroids == astroids.size());
}

TEST_CASE("Enemy Spawner"){
    std::shared_ptr<Scene> scene = Scene::create();
    Ship ship(scene, 35);
    int numberOfEnemies = 8;

    GameLoop gameLoop(35, ship, scene);
    gameLoop.createEnemies(numberOfEnemies);

    std::vector<Enemy> enemies = gameLoop.getEnemies();

    REQUIRE(numberOfEnemies == enemies.size());
}

TEST_CASE("Game Reset"){
    std::shared_ptr<Scene> scene = Scene::create();
    Ship ship(scene, 35);

    GameLoop gameLoop(35, ship, scene);
    gameLoop.createEnemies(8);
    gameLoop.createAstroids(13);

    gameLoop.reset();

    std::vector<Enemy> enemies = gameLoop.getEnemies();
    std::vector<std::shared_ptr<Astroid>> astroids = gameLoop.getAstroids();
    const int score = gameLoop.getScore();

    REQUIRE(astroids.empty());
    REQUIRE(enemies.empty());
    REQUIRE(scene->children.size() == 1);   //1 because ship isn't removed
    REQUIRE(score == 0);
}