#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "threepp/threepp.hpp"
#include "LaserControls.hpp"
#include "Astroid.hpp"

TEST_CASE("TestCreateLaser", "[LaserControls]") {
    LaserControls laserControls;
    auto scene = std::make_shared<threepp::Scene>();
    auto sprite = threepp::Sprite::create();
    laserControls.setLaserSpeed(1.0, 1.0);
    laserControls.createLaser(scene, sprite);

    auto lasers = laserControls.getLasers();
    REQUIRE(lasers.size() == 1);
    CHECK(lasers[0].first->position.x == sprite->position.x);
    CHECK(lasers[0].first->position.y == sprite->position.y);
}

TEST_CASE("TestUpdateLasers", "[LaserControls]") {
    auto scene = std::make_shared<threepp::Scene>();
    auto sprite = threepp::Sprite::create();
    LaserControls laserControls;
    laserControls.setLaserSpeed(1.0, 1.0);
    laserControls.createLaser(scene, sprite);

    laserControls.updateLasers(scene, 1.0, 100);
    auto lasers = laserControls.getLasers();
    REQUIRE(lasers.size() == 1);
    CHECK(lasers[0].first->position.x > sprite->position.x);
    CHECK(lasers[0].first->position.y > sprite->position.y);
}