#include "Heroe.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    
    if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));

        move(Ogre::Vector3(0.0, 0.0, -10.0));
    }
    else if (evt.keysym.sym == SDLK_DOWN ||evt.keysym.sym == SDLK_s) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(0.0, 0.0, 10.0));
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(-10.0, 0.0, 0.0));
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(10.0, 0.0, 0.0));
    }

    return true;
}