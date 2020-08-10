#include <iostream>

#include "win_prop.h"
#include "Scene.h"

int main(int argc, char **argv) {
    
    // create a new scene
    Scene scene(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);


    // create some walls
	scene.createWall(2, 2, 1, 1);
	scene.createWall(2, 5, 2, 3);
	scene.createWall(4, 7, 5, 1);
	scene.createWall(11, 7, 2, 1);
	scene.createWall(8, 3, 2, 2);


    scene.run();

    return 0;
}