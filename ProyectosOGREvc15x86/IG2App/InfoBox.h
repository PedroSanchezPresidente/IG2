#pragma once
#include <OgreTrays.h>

class InfoBox {
private:
	OgreBites::TrayManager* mng;
	OgreBites::Label* label;
	Ogre::DisplayString labelText = "Stage 1";
	OgreBites::TextBox* box;
	Ogre::DisplayString textBoxText = "Game Info here!";

	OgreBites::TrayLocation BoxLocation = OgreBites::TrayLocation::TL_BOTTOMRIGHT;

public:
	InfoBox(OgreBites::TrayManager* Mng) : mng(Mng){
		label = mng->createLabel(BoxLocation, "Label", labelText, 200);
		box = mng->createTextBox(BoxLocation, "TextBox", textBoxText, 200, 100);
		box->setText("Lives: 1\nPoints: 280");
	}

	void changeLevel(String s) {
		labelText = "Stage: " + s;
	}

	void changeTextBoxText(String s) {
		box->setText(s);
	}
};