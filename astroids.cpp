#include "BaseShip.hpp"
#include "GameLoop.hpp"
#include <iostream>
#include <string>

using namespace threepp;

int main() {

    const float creationTime = 0.7;
    const int astroidsPerEnemy = 10;
    int createdAstroidsCounter = 0;
    double timePassed = creationTime + 1;
    const int boardSize = 35;

    Canvas canvas("Astroids", {{"aa",4}});
    canvas.setSize({850, 850});
    GLRenderer renderer(canvas.size());

    const auto camera = OrthographicCamera::create(-boardSize, boardSize, boardSize, -boardSize);
    camera -> position.z = 50;

    std::shared_ptr<Scene> scene = Scene::create();

    auto background = ObjectCreator::createSprite(boardSize * 2, boardSize * 2, "../textures/Background.jpg");

    scene->add(background.first);

    Ship ship(scene, boardSize);

    canvas.addKeyListener(&ship);

    TextRenderer textRenderer;      //Lager teksten
    auto & textHandle = textRenderer.createHandle("Score: 0");
    textHandle.verticalAlignment = threepp::TextHandle::VerticalAlignment::BOTTOM;
    textHandle.setPosition(0, canvas.size().height);
    textHandle.scale = 2;

    canvas.onWindowResize([&](WindowSize size) {    //Endrer vindusstørrelse
        camera -> updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height);
    });

    GameLoop gameLoop(boardSize, ship, scene);

    int c = 0;
    Clock clock;
    clock.start();
    canvas.animate([&] {
        c++;
        auto dt = clock.getDelta();
        timePassed += dt;

        gameLoop.setShip(ship);

        if (timePassed > creationTime) {
            gameLoop.createAstroids(2);
            timePassed -= creationTime;
            createdAstroidsCounter += 1;
            if (createdAstroidsCounter >= astroidsPerEnemy) {
                gameLoop.createEnemies(2);
                createdAstroidsCounter = 0;
            }
        }

        ship.move(dt);

        bool reset = gameLoop.astroidUpdater(dt);

        std::vector<Laser> lasers = ship.getLaser();

        bool collidedeWithLaser = gameLoop.enemyUpdater(dt);
        if (!reset){
            reset = collidedeWithLaser;
        }

        gameLoop.explotionParticleUpdater(dt);

        if (reset){
            gameLoop.reset();
        }

        renderer.render(*scene, *camera);

        textHandle.setText("Score: " + std::to_string(gameLoop.getScore()));
        renderer.resetState();
        textRenderer.render();
    });
    std::cout << c / clock.elapsedTime << std::endl;
}