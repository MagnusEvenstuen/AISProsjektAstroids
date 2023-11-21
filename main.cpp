#include "Controls.hpp"
#include "Astroid.hpp"
#include "Enemy.hpp"
#include <string>
using namespace threepp;

int main() {

    const float creationTime = 0.5;
    const int astroidsPerEnemy = 20;
    int createdAstroidsCounter = 15;
    double timePassed = creationTime + 1;
    int boardSize = 35;
    std::string text = "Score: 0";
    Object Object3D;
    Astroid astroid(boardSize);

    Canvas canvas("Astroids", {{"aa", 4}});
    GLRenderer renderer(canvas.size());

    const auto camera = OrthographicCamera::create(-boardSize, boardSize, boardSize, -boardSize);
    camera->position.z = 50;

    std::shared_ptr<Scene> scene = Scene::create();

    Enemy enemy(scene, boardSize);
    auto background = Object3D.createSprite("../textures/background.jpg", boardSize * 2, boardSize * 2).first;
    scene->add(background);

    auto ship = Object3D.createSprite("../textures/Millenium Falcon.png", 5, 5);
    scene->add(ship.first);

    Controls control(ship, scene, boardSize);
    canvas.addKeyListener(&control);


    TextRenderer textRenderer;
    auto &textHandle = textRenderer.createHandle(text);
    textHandle.verticalAlignment = threepp::TextHandle::VerticalAlignment::BOTTOM;
    textHandle.setPosition(0, canvas.size().height);
    textHandle.scale = 2;

    canvas.onWindowResize([&](WindowSize size) {
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height);
    });

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();
        timePassed += dt;

        if (timePassed > creationTime){
            astroid.createAstroids(scene);
            timePassed -= creationTime;
            createdAstroidsCounter += 1;
            if (createdAstroidsCounter >= astroidsPerEnemy){
                enemy.createEnemy();
                createdAstroidsCounter = 0;
            }
        }

        astroid.updateAstroids(scene, dt);

        auto lasers = control.getLasars();
        auto enemyLasers = enemy.getLasars();

        astroid.checkColison(lasers, ship.first, scene, enemy.getEnemyShips(), enemyLasers);
        enemy.moveEnemy(lasers, ship.first, astroid.getAstroids(), astroid.getAstroidSpeeds(), control.getLaserSpeeds());

        control.setDeltaTime(dt);
        enemy.setDt(dt);
        control.setSpeed();

        renderer.render(*scene, *camera);

        text = "Score: " + std::to_string(astroid.getScore());
        textHandle.setText(text);

        renderer.resetState();
        textRenderer.render();
    });
}