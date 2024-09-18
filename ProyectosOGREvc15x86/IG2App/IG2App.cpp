#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering... 
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if(evt.keysym.sym == SDLK_k){
        cout << "Position of Sinbad: " << mSinbadNode->getPosition() << endl;
        cout << "Position of the camera: " << mCamNode->getPosition() << endl;

    }
    else if (evt.keysym.sym == SDLK_a) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        mSnowmanNode->translate(Ogre::Vector3(0.0, 200.0, 0.0));
    }
    else if (evt.keysym.sym == SDLK_s) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        mSnowmanHeadNode->translate(Ogre::Vector3(0.0, 200.0, 0.0));
    }
    else if (evt.keysym.sym == SDLK_d) {
        //mSnowmanNode->rotate(Ogre::Quaternion(0.0, 0.0, 180.0, 0.0));
        mSnowmanBodyNode->translate(Ogre::Vector3(0.0, 200.0, 0.0));
    }
    
  return true;
}

void IG2App::shutdown(){
    
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

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5)); 
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0, 0, -1));
    

    
    ////------------------------------------------------------------------------
    //// Creating Sinbad

    //Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //mSinbadNode->attachObject(ent);

    //// Show bounding box
    //mSinbadNode->showBoundingBox(true);
    //
    //// Set position of Sinbad
    //mSinbadNode->setPosition(0, 20, 0);
    //
    //// Set scale of Sinbad
    //mSinbadNode->setScale(20, 20, 20);
    //
    ////mSinbadNode->yaw(Ogre::Degree(-45));
    ////mSinbadNode->setVisible(false); 
    //
    //// Creating bath

    /*Ogre::Entity* ent2 = mSM->createEntity("RomanBathLower.mesh");
    mBathNode = mSM->getRootSceneNode()->createChildSceneNode("nBath");
    mBathNode->attachObject(ent2);
    Ogre::Entity* ent3 = mSM->createEntity("RomanBathUpper.mesh");
    mBathNode->attachObject(ent3);*/

    //Snowman
    //Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
    mSnowmanNode = mSM->getRootSceneNode()->createChildSceneNode("nSnowman");
    // CABEZA
    Ogre::Entity* headEnt = mSM->createEntity("sphere.mesh");
    mSnowmanHeadNode = mSnowmanNode->createChildSceneNode("nSnowmanHead");
    mSnowmanHeadNode->attachObject(headEnt);
    mSnowmanHeadNode->showBoundingBox(true);
    // CUERPO
    Ogre::Entity* bodyEnt = mSM->createEntity("sphere.mesh");
    mSnowmanBodyNode = mSnowmanNode->createChildSceneNode("nSnowmanBody");
    mSnowmanBodyNode->attachObject(bodyEnt);

    mSnowmanHeadNode->scale(Ogre::Vector3(0.75, 0.75, 0.75));
    mSnowmanHeadNode->translate(Ogre::Vector3(0.0, 160, 0.0));


    // PARTES CABEZA
   
    // =====================================
    // BOCA
    Ogre::Entity* mouthEnt = mSM->createEntity("sphere.mesh");
    mSnowmanMouthNode = mSnowmanHeadNode->createChildSceneNode("nSnowmanMouth");
    mSnowmanMouthNode->attachObject(mouthEnt);

    mSnowmanMouthNode->scale(Ogre::Vector3(0.2, 0.10, 0.15));
    mSnowmanMouthNode->translate(Ogre::Vector3(0, -30, 100 ));
    // =====================================


    // =====================================
    // NARIZ
    Ogre::Entity* noseEnt = mSM->createEntity("sphere.mesh");
    mSnowmanNoseNode = mSnowmanHeadNode->createChildSceneNode("nSnowmanNose");
    mSnowmanNoseNode->attachObject(noseEnt);

    mSnowmanNoseNode->scale(Ogre::Vector3(0.1, 0.1, 0.1));
    mSnowmanNoseNode->translate(Ogre::Vector3(0, 0, 100));
    // =====================================

    // =====================================
    // OJO DERECHO
    Ogre::Entity* reEnt = mSM->createEntity("sphere.mesh");
    mSnowmanRENode = mSnowmanHeadNode->createChildSceneNode("nSnowmanRE");
    mSnowmanRENode->attachObject(reEnt);

    mSnowmanRENode->scale(Ogre::Vector3(0.1, 0.1, 0.1));
    mSnowmanRENode->translate(Ogre::Vector3(30, 20, 100));
    // =====================================

    // =====================================
    // OJO IZQUIERDO
    Ogre::Entity* leEnt = mSM->createEntity("sphere.mesh"); 
    mSnowmanLENode = mSnowmanHeadNode->createChildSceneNode("nSnowmanLE");
    mSnowmanLENode->attachObject(leEnt);

    mSnowmanLENode->scale(Ogre::Vector3(0.1, 0.1, 0.1));
    mSnowmanLENode->translate(Ogre::Vector3(-30, 20, 100));
    // =====================================


    // PARTES CUERPO
    
    // =====================================
    // OMBLIGO
    Ogre::Entity* bbEnt = mSM->createEntity("sphere.mesh");
    mSnowmanBBNode = mSnowmanBodyNode->createChildSceneNode("nSnowmanBB");
    mSnowmanBBNode->attachObject(bbEnt);

    mSnowmanBBNode->scale(Ogre::Vector3(0.1, 0.1, 0.1));
    mSnowmanBBNode->translate(Ogre::Vector3(0, 0, 100));


}


