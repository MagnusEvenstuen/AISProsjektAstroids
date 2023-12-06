#ifndef ASTROIDS_COLLITIONDETECTION_HPP
#define ASTROIDS_COLLITIONDETECTION_HPP

#include "ExplotionCreator.hpp"
#include "threepp/threepp.hpp"
#include "BaseObject.hpp"
#include "Astroid.hpp"
#include "Enemy.hpp"
#include "Laser.hpp"
#include "Ship.hpp"

using namespace threepp;

class CollitionDetection {
public:



    static bool collitionDestroy(std::shared_ptr<Astroid>& astroid, std::vector<Laser>& lasers);

    static bool collitionDestroy(std::shared_ptr<Astroid>& astroid, Enemy& enemy);

    static bool collitionDestroy(std::vector<Laser>& lasers, Enemy& enemy);;

    static bool collitionReset(std::shared_ptr<Astroid>& astroid, Ship& ship);

    static bool collitionReset(std::vector<Laser>& lasers, Ship& ship);;
};

#endif //ASTROIDS_COLLITIONDETECTION_HPP