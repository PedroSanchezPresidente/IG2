#include "Heroe.h"
#include "Labyrinth.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {
        mNode->setOrientation(1, 0, Radian(180).valueRadians(), 0);

        newDir = Vector3(0, 0, -1);
    } 
    else if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) {
        mNode->setOrientation(1, 0, 0, 0);
        newDir = Vector3(0, 0, 1);
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        mNode->setOrientation(1, 0, -1, 0);
        newDir = Vector3(-1, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        mNode->setOrientation(1, 0, 1, 0);
        newDir = Vector3(1, 0, 0);
    }

    return true;
}

void Heroe::frameRendered(const Ogre::FrameEvent& evt) {
    if (distance > 0) {
        move(dir * speed);
        distance -= speed;
    }
    else {
        if (newDir != dir && lab->getTile(actualPos.x + newDir.z, actualPos.y + newDir.x)->isTraspasable()) {
            //Quaternion q = this.getOrientation()
            dir = newDir;
        }
        if (dir != Vector3::ZERO && lab->getTile(actualPos.x + dir.z, actualPos.y + dir.x)->isTraspasable()) {
            distance = tileWidth;
            actualPos.x += dir.z;
            actualPos.y += dir.x;
        }
        else
            dir = Vector3::ZERO;
    }
}