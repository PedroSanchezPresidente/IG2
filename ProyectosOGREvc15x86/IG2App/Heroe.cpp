#include "Heroe.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    
    if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {
        cout << mNode->getOrientation();

        mNode->setOrientation(1, 0, Radian(180).valueRadians(), 0);

        move(Ogre::Vector3(0.0, 0.0, -10.0));
    }
    else if (evt.keysym.sym == SDLK_DOWN ||evt.keysym.sym == SDLK_s) {
        mNode->setOrientation(1, 0, 0, 0);
        move(Ogre::Vector3(0.0, 0.0, 10.0));
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        mNode->setOrientation(1, 0,-1, 0); 
        move(Ogre::Vector3(-10.0, 0.0, 0.0));
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        mNode->setOrientation(1, 0, 1, 0); 
        move(Ogre::Vector3(10.0, 0.0, 0.0));
    }

    return true;
}