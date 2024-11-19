#include "Character.h"
#include "Labyrinth.h"

void Character::frameRendered(const Ogre::FrameEvent& evt) {
    if (_active) {
        if (distance > 0) {
            if (newDir == dir * -1) {
                Quaternion q = getOrientation().getRotationTo(newDir);
                mNode->rotate(q);
                dir = newDir;
                distance = tileWidth - distance;
            }
            move(dir * speed);
            distance -= speed;
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
}