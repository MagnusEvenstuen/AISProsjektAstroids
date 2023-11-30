#include "Controls.hpp"
#include "Astroid.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "CollitionDetection.hpp"
#include <iostream>
#include <string>

using namespace threepp;

int main() {

    const float creationTime = 0.7;
    const int astroidsPerEnemy = 20;
    int score = 0;
    int createdAstroidsCounter = 0;
    double timePassed = creationTime + 1;
    const int boardSize = 35;
    const float laserHitBox = 1;
    const float shipHitBox = 5;
    std::string text = "Score: 0";
    ObjectCreator Object3D;
    Astroid astroid(boardSize);

    Canvas canvas("Astroids", {{"aa",4}});
    GLRenderer renderer(canvas.size());

    const auto camera = OrthographicCamera::create(-boardSize, boardSize, boardSize, -boardSize);
    camera -> position.z = 50;

    std::shared_ptr<Scene> scene = Scene::create();

    Enemy enemy(scene, boardSize);

    auto ship = Game::startGame("../textures/Background.jpg", "../textures/Millenium Falcon.png", scene, boardSize);

    Controls control(ship, scene, boardSize);
    canvas.addKeyListener( & control);

    ExplotionCreator explotionCreator(scene);

    TextRenderer textRenderer;
    auto & textHandle = textRenderer.createHandle(text);
    textHandle.verticalAlignment = threepp::TextHandle::VerticalAlignment::BOTTOM;
    textHandle.setPosition(0, canvas.size().height);
    textHandle.scale = 2;

    canvas.onWindowResize([ & ](WindowSize size) {
        camera -> updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height);
    });
    int c = 0;
    Clock clock;
    clock.start();
    canvas.animate([ & ] {
        c++;
        auto dt = clock.getDelta();
        timePassed += dt;

        if (timePassed > creationTime) {
            astroid.createAstroids(scene);
            timePassed -= creationTime;
            createdAstroidsCounter += 1;
            if (createdAstroidsCounter >= astroidsPerEnemy) {
                enemy.createEnemy();
                createdAstroidsCounter = 0;
            }
        }

        astroid.updateAstroids(scene, dt);

        auto lasers = control.getLasers();
        auto enemyLasers = enemy.getLasers();

        enemy.moveEnemy(ship.first, astroid.getAstroids(), astroid.getAstroidSpeeds());
        CollitionDetection::collitionChangeDirection(astroid.getAstroids(), astroid.getAstroidSpeeds(), astroid.getAstroidRotationSpeeds(), astroid.getAstroidSize());
        CollitionDetection::collitionDestroy(astroid.getAstroids(), enemy.getEnemyShips(), astroid.getAstroidSize(), shipHitBox, scene, explotionCreator);
        CollitionDetection::collitionDestroy(enemyLasers, astroid.getAstroids(), astroid.getAstroidSize(), laserHitBox, scene, explotionCreator, &astroid.getAstroidSpeeds(), & astroid.getAstroidRotationSpeeds());
        score += CollitionDetection::collitionDestroy(lasers, astroid.getAstroids(), astroid.getAstroidSize(), laserHitBox, scene, explotionCreator, & astroid.getAstroidSpeeds(), & astroid.getAstroidRotationSpeeds());
        score += CollitionDetection::collitionDestroy(lasers, enemy.getEnemyShips(), laserHitBox, shipHitBox, scene, explotionCreator);
        score = CollitionDetection::collitionDestroy(enemyLasers, ship, laserHitBox, shipHitBox, score);
        if (ship.first != nullptr) {
            score = CollitionDetection::collitionDestroy(astroid.getAstroids(), ship, astroid.getAstroidSize(), shipHitBox, score);
        }

        if (ship.first == nullptr) {
            Game::resetGame(scene, lasers, enemyLasers, astroid.getAstroidSpeeds(), astroid.getAstroids(), enemy.getEnemyShips());
            ship = Game::startGame("../textures/Background.jpg", "../textures/Millenium Falcon.png", scene, boardSize);
        }

        explotionCreator.moveExplotion(dt);
        control.setDeltaTime(dt);
        enemy.setDt(dt);
        control.setSpeed();
        renderer.render( * scene, * camera);

        text = "Score: " + std::to_string(score);
        textHandle.setText(text);
        renderer.resetState();
        textRenderer.render();
    });
    std::cout << c / clock.elapsedTime << std::endl;
}