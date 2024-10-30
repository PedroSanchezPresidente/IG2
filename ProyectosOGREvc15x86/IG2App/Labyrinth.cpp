#include "Labyrinth.h"

Labyrinth::Labyrinth(string routeName, SceneManager* mSM, OgreBites::TrayManager* tM, SceneNode* camNode) {
    ifstream file(routeName);
    if (!file)
        cout << "no se pudo abrir el archivo\n";

    node = mSM->getRootSceneNode()->createChildSceneNode("map");
    file >> r >> c;
    file >> floorMat >> pearlMat >> wallMat >> bodyMat1 >> bodyMat2 >> helMat >> typeLight;
    map.resize(r);

    g = new Grafo(r * c);
    int eP;

    for (int i = 0; i < r; i++) {
        map[i].resize(c);
        for (int j = 0; j < c; j++) {
            char ch;
            file >> ch;

            SceneNode* n = node->createChildSceneNode();

            int x, z;
            x = j * tileWidth + tileWidth / 2;
            z = i * tileHeight + tileHeight / 2;

            if (ch == 'x') {
                map[i][j] = new Muro(Vector3(x, 0, z), n, mSM, wallMat ,false);
            }
            else if (ch == 'o') {
                map[i][j] = new Perla(Vector3(x, 0, z), n, mSM, pearlMat, 10, true, true, Vector3(0.1, 0.1, 0.1));
            }
            else if (ch == 'h') {
                map[i][j] = new Tile();
                n = node->createChildSceneNode();
                heroe = new Heroe(Vector3(x, 0, z), n, mSM, "Sinbad.mesh", this, tileWidth);
                eP = i + j * c;
            }
            else if (ch == 'v') {
                map[i][j] = new Perla(Vector3(x, 0, z), n, mSM,  pearlMat, 10, true, true, Vector3(0.1, 0.1, 0.1));
                n = node->createChildSceneNode();
                Enemigo* e = new Enemigo(Vector3(x, -ENEMY_Y_OFFSET, z), n, mSM, enemigos.size(), bodyMat1, bodyMat2, helMat, this, tileWidth);
                e->setScale(ENEMY_SCALE);
                enemigos.push_back(e);
                enemiesLights.push_back(new FollowingLight(e->getSceneNode(), mSM, Light::LightTypes::LT_POINT, "enemyLight" + to_string(enemiesLights.size() - 1), Ogre::ColourValue::Red, Vector3(0, -10, 0)));
            }

            if (ch != 'x') {
                if (j != 0 && map[i][j-1]->isTraspasable())
                    g->ponArista(j - 1 + i * c, j + i * c);
                if (i != 0 && map[i-1][j]->isTraspasable())
                    g->ponArista(j + (i - 1) * c, j + i * c);
            }
        }
    }
    center = Vector3((map.size() * tileHeight) / 2 - tileHeight / 2, 0, (map[0].size() * tileWidth) / 2 - tileWidth / 2);

    createFloor(mSM);

    setCameraPosition(camNode);

    if (heroe != nullptr) {
        heroe->showBoundingBox(true);
        heroeLight = new FollowingLight(heroe->getSceneNode(), mSM, typeLight, "heroeLight");
    }

    ib = new InfoBox(tM);

    cam = new CaminoMasCorto(*g, eP);
}


Vector3 Labyrinth::getDistance(Vector3 s) {
    Vector3 dir = Vector3(0,0,0);
    int distance = 10000000;

    int sPX = s.x / tileWidth;
    int sPY = s.z / tileHeight;
    int sP = sPX + sPY * c;
    int x = heroe->getPosition().x / tileWidth;
    int y = (heroe->getPosition().z / tileHeight);
    int eP = x + y * c;
    if (cam->getS() != eP) {
        delete cam;
        cam = new CaminoMasCorto(*g, eP);
    }

    if (sPY > 0 && map[sPY - 1][sPX]->isTraspasable() && cam->distancia(sP - c) < distance) {
        distance = cam->distancia(sP - c);
        dir = { 0,0,-1 };
    }
    if (sPY != r - 1 && map[sPY + 1][sPX]->isTraspasable() && cam->distancia(sP + c) < distance) {
        distance = cam->distancia(sP + c);
        dir = { 0,0,1 };
    }
    if (sPX != 0 && map[sPY][sPX - 1]->isTraspasable() && cam->distancia(sP - 1) < distance) {
        distance = cam->distancia(sP - 1);
        dir = { -1,0,0 };
    }
    if (sPX != c - 1 && map[sPY][sPX + 1]->isTraspasable() && cam->distancia(sP + 1) < distance) {
        distance = cam->distancia(sP+1);
        dir = { 1,0,0 };
    }

    return dir;
}

void Labyrinth::gameOver() {
    for (std::vector<Tile*> r : map)
        for (Tile* t : r)
            t->restart();

    heroe->restart();
    for (Enemigo* e : enemigos)
        e->restart();
    ib->gameOver();
};