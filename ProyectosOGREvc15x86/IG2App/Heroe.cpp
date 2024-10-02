#include "Heroe.h"

void Heroe::keypressed(const OgreBites::KeyboardEvent& evt) {
    
    if (evt.keysym.sym == SDLK_UP) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(0.0, 0.0, -10.0));
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(0.0, 0.0, 10.0));
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(-10.0, 0.0, 0.0));
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        move(Ogre::Vector3(10.0, 0.0, 0.0));
    }
}