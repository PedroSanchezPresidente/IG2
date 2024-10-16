#include "Heroe.h"
#include "Labyrinth.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {

        newDir = Vector3(0, 0, -1);
    } 
    else if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) {
        newDir = Vector3(0, 0, 1);
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        newDir = Vector3(-1, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        newDir = Vector3(1, 0, 0);
    }

    return true;
}

bool Heroe::keyReleased(const OgreBites::KeyboardEvent& evt) {
    if ((evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) && newDir == Vector3(0, 0, -1)) {
        newDir = dir;
    }
    else if ((evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) && newDir == Vector3(0, 0, 1)) {
        newDir = dir;
    }
    else if ((evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) && newDir == Vector3(-1, 0, 0)) {
        newDir = dir;
    }
    else if ((evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) && newDir == Vector3(1, 0, 0)) {
        newDir = dir;
    }

    return true;
}

void Heroe::frameRendered(const Ogre::FrameEvent& evt) {
    Character::frameRendered(evt);
    if (distance == 0)
        lab->getTile(getPosition())->interact(this);
}

void Heroe::addPoints(int p)
{
    lab->addPoints(p);
}
