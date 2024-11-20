#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering... 
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_s) {
        if (_state != GAME) {
            _state = GAME;
            changeScene();
        }
    }
    else if (evt.keysym.sym == SDLK_p) {
        if (_state != MAIN_MENU) {
            _state = MAIN_MENU;
            changeScene();
        }
    }
    
  return true;
}

void IG2App::shutdown(){
    if (map != nullptr) {
        delete map;
        map = nullptr;
    }
    if (cinematic != nullptr) {
        delete cinematic;
        cinematic = nullptr;
    }
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  

  mRoot->destroySceneManager(mSM);  
					
  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;

  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, -10, 30);
    mCamNode->lookAt(Ogre::Vector3(0, -5, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);


    // ---------------------------------------------
    //  Creating laberynth

    map = new Labyrinth("../stage1.txt", mSM, mTrayMgr);
    map->setup();

    addInputListener(map->getHeroe());
    for (Enemigo* e : map->getEnemigos()) {
        addInputListener(e);
    }

    //----------------------------------------------
    //  Creating cinematic
    cinematic = new Cinematic(mSM);
    addInputListener(cinematic);

    changeScene();
}

void IG2App::changeScene() {
    switch (_state) {
    case GAME:
        map->setVisible(true);
        map->resetCamera(mCamNode);
        cinematic->setVisible(false);
        break;
    case MAIN_MENU:
        map->restart();
        map->setVisible(false);
        cinematic->setVisible(true);
        cinematic->resetCamera(mCamNode);
        break;
    default:
        break;
    }
}




