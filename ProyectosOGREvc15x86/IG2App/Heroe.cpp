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

void Heroe::frameRendered(const Ogre::FrameEvent& evt) {
    if (distance > 0) {
        if (newDir == dir * -1) {
            Quaternion q = getOrientation().getRotationTo(newDir);
            mNode->rotate(q);
            dir = newDir;
            distance = tileWidth - distance;
        }
        move(dir * speed);
        distance -= speed;
        lab->getTile(getPosition())->interact(this);
    }
    else {
        if (newDir != dir && lab->getTile(getPosition() + (newDir * tileWidth))->isTraspasable()) {
            Quaternion q = getOrientation().getRotationTo(newDir);
            dir = newDir;
            mNode->rotate(q);
        }
        if (dir != Vector3::ZERO && lab->getTile(getPosition() + (dir * tileWidth))->isTraspasable()) {
            distance = tileWidth;
        }
        else
            dir = Vector3::ZERO;
    }
}

void Heroe::addPoints(int p)
{
    lab->addPoints(p);
}
