#include "controls.hpp"

using namespace threepp;

int main() {

    Canvas canvas("threepp demo", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 30;

    OrbitControls controls{*camera, canvas};

    auto scene = Scene::create();

    Object ship;
    ship.setColor(Color::blue);
    scene->add(ship);

    Controls control(ship);
    canvas.addKeyListener(&control);

    TextRenderer textRenderer;
    auto &textHandle = textRenderer.createHandle("Hello World");
    textHandle.verticalAlignment = threepp::TextHandle::VerticalAlignment::BOTTOM;
    textHandle.setPosition(0, canvas.size().height);
    textHandle.scale = 2;

    std::array<float, 3> posBuf{};

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height);
    });

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();
        control.setDeltaTime(dt);
        control.setSpeed();

        renderer.render(*scene, *camera);

        renderer.resetState();// needed when using TextRenderer
        textRenderer.render();
    });
}