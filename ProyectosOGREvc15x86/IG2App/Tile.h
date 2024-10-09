#pragma once
#include "Heroe.h"
class Tile {
public:
	bool isTraspasable() { return traspasable_; }
	virtual void interact(Heroe* h) = 0;
protected:
	bool traspasable_; 
};

