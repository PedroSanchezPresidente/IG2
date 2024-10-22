#include "Enemigo.h"

void Enemigo::frameRendered(const Ogre::FrameEvent& evt)
{
	helix->update();
	body->update();
	wheels->update();
}
