# Astroids Game

This project is my exam project in the subject AIS1003.
I have programmed a new take on the classic arcade game
Asteroids. The main differences between my version, and the
classic version is that my version have collition detection
between astroids, even though it is a bit wonky, but most of
the time it works all of the time. In addition
I don't have astroids that split up when they get shot, but
I have also added explotions when they get shot.

The setting for the game is the scene from the movie "The 
Empire Strikes Back", where the Millenium Falcon is navigated
through an astroid field to escape chasing Thai Fighters.

The controls for the game are quite simple: 

w/arrow up = forward

d/arrow right = right 

a/arrow left = left

space = shoot.

## Functionalities
Controls

Bots

Movement

Collition physics (between astroids)

Object Creation

Testing System

## Dependencies
This Project is built using Threepp. Which is a port of the
popular JavaScript libarary Three.js. Other than that, I
have just used the standard libarary for C++.

As vcpkg is used, you need to tell CMake about it in order for dependency 
resolution to work:

-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake

## Executing Program
You can run the program by using the green run button at the
top line in CLion or Visual Studio. 

### Sources
ChatGPT

Stack overflow

GitHub(https://github.com/dadul96/ElasticCollisionSimulation)

All of theese are mostly been used for fixing errors, hence 
why they arent creddited in spesific parts of the code. From
the GitHub link I only used the code for HitBoxes.

Kandidatnummer: 10017