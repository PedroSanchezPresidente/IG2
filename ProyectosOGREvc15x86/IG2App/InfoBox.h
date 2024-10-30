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

	int points = 0;
	int lives = 3;
	void updateTextBoxText() {
		String s1 = "Lives: " + to_string(lives);
		String s2 = "Points: " + to_string(points);
		box->setText(s1 + "\n" + s2);
	}
public:
	InfoBox(OgreBites::TrayManager* Mng) : mng(Mng){
		label = mng->createLabel(BoxLocation, "Label", labelText, 300);
		box = mng->createTextBox(BoxLocation, "TextBox", textBoxText, 300, 100);
		box->setText("Lives: " + to_string(lives) + "\nPoints: " + to_string(points));
	}

	void changeLevel(String s) {
		labelText = "Stage: " + s;
	}
	void addPoints(int p) {
		points += p;
		updateTextBoxText();
	}

	void gameOver() {
		points = 0;
		lives -= 1;
		updateTextBoxText();
	}
};