#pragma once
#include <vector>
#include "IG2Object.h"

using namespace std;

class Labyrinth {
private:
	std::vector<std::vector<IG2Object*>> map;
    SceneNode* node;
    int tileHeight = 100, tileWidth = 100;

public:
    Labyrinth() {};

    Labyrinth(string routeName, SceneManager* mSM) {
        ifstream file(routeName);
        if (!file)
            cout << "no se pudo abrir el archivo\n";

        int h, w;
        node = mSM->getRootSceneNode()->createChildSceneNode("map");

        file >> h >> w;
        map.resize(h);

        for (int i = 0; i < h; i++) {
            map[i].resize(w);
            for (int j = 0; j < w; j++) {
                char c;
                file >> c;

                SceneNode* n = node->createChildSceneNode();

                if (c == 'x') {
                    map[i][j] = new IG2Object(Vector3(j * tileWidth, 0, i * tileHeight), n, mSM, "cube.mesh");
                    map[i][j]->setScale(Vector3(1, 1, 1));
                }
                else if (c == 'o') {
                    map[i][j] = new IG2Object(Vector3(j* tileWidth, 0, i* tileHeight), n, mSM, "sphere.mesh");
                    map[i][j]->setScale(Vector3(0.1,0.1,0.1));
                }
            }
        }
    }

    ~Labyrinth() {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; map[i].size(); j++) {
                delete map[i][j];
            }
            map[i].clear();
        }

        map.clear();
    }
};