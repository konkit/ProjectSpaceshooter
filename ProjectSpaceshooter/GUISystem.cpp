#pragma once
#include "GUISystem.h"
//
//Ogre::TextAreaOverlayElement* GUISystem::createText( std::string elementID, int posX, int posY )
//{
//	// Create a text area
//	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
//		overlayManager->createOverlayElement("TextArea", elementID));
//	textArea->setMetricsMode(Ogre::GMM_PIXELS);
//	textArea->setPosition(posX, posY);
//	textArea->setDimensions(100, 20);
//	textArea->setCharHeight(16);
//	textArea->setFontName("MyFont");
//	textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
//	textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));
//
//	// Add the text area to the panel
//	panel->addChild(textArea);
//
//	return textArea;
//}
//
//void GUISystem::loadFont( std::string fontFilename )
//{
//	Ogre::ResourceGroupManager &resGroupMgr = Ogre::ResourceGroupManager::getSingleton();
//	// tell it to look at this location
//	resGroupMgr.addResourceLocation(FONT_FOLDER, "FileSystem");
//	// get the font manager
//	Ogre::FontManager &fontMgr = Ogre::FontManager::getSingleton();
//	// create a font resource
//	Ogre::ResourcePtr font = fontMgr.create("MyFont", "General");
//	// set as truetype
//	font->setParameter("type", "truetype");
//	// set the .ttf file name
//	font->setParameter("source", fontFilename);
//	// set the size
//	font->setParameter("size", "26");
//	// set the dpi
//	font->setParameter("resolution", "96");
//	// load the ttf
//	font->load();
//}
//
//GUISystem::~GUISystem()
//{
//	//This function unloads previously loaded texture
//	Ogre::TextureManager::getSingleton().unload("radar_background.png");
//
//	ogre2dManager->end();
//	delete ogre2dManager;
//}
//
//void GUISystem::display( GameData& mGameData, TimeData _time )
//{
//	//Draw radar background
//	ogre2dManager->spriteBltFull("radar3.png", 0.6, 1.0, 1.0, 0.5);
//
//	//Draw objects on radar
//	//Draw player dot
//	ogre2dManager->spriteBltFull("Player.png", 0.8-DOT_WIDTH , 0.75+DOT_HEIGHT, 0.8+DOT_WIDTH, 0.75-DOT_HEIGHT);
//
//	const float DOT_DISTANCE_SCALE = 2500.0f;
//
//	//Draw static
//	GameObject* it;
//	GameCollectionIterator<StaticObject> myStaticsIterator = mGameData.getStatics().getIterator();
//	while (myStaticsIterator.hasNext())
//	{
//		it = myStaticsIterator.getNext();
//
//
//
//		Ogre::Vector3 toStatic =
//			( it->getPosition() - mGameData.getPlayer()->getPosition() );
//
//		if( toStatic.squaredLength() > 2000.0 * 2000.0)	{
//			continue;
//		}
//
//		toStatic.x = -toStatic.x;
//
//		toStatic = mGameData.getPlayer()->getOrientation() * toStatic;
//
//		float offsetX = toStatic.x / ( DOT_DISTANCE_SCALE * 4);
//		float offsetZ = toStatic.z / ( DOT_DISTANCE_SCALE * 4);
//
//		if( it == &mGameData.getCore() )	{
//			ogre2dManager->spriteBltFull("Core.png", 
//				0.8  + offsetX - CORE_DOT , 
//				0.75 + offsetZ + CORE_DOT,
//				0.8  + offsetX + CORE_DOT, 
//				0.75 + offsetZ - CORE_DOT);
//		} else {
//			ogre2dManager->spriteBltFull("Static.png", 
//				0.8  + offsetX - DOT_WIDTH , 
//				0.75 + offsetZ + DOT_HEIGHT,
//				0.8  + offsetX + DOT_WIDTH, 
//				0.75 + offsetZ - DOT_HEIGHT );
//		}
//
//
//
//
//	}
//
//	//Draw enemies
//	GameCollectionIterator<EnemyObject> myEnemyIterator = mGameData.getEnemies().getIterator();
//	while (myEnemyIterator.hasNext())
//	{
//		it = myEnemyIterator.getNext();
//
//		Ogre::Vector3 toStatic =
//			( it->getPosition() - mGameData.getPlayer()->getPosition() );
//
//		if( toStatic.squaredLength() > 2000.0 * 2000.0)	{
//			continue;
//		}
//
//		toStatic.x = -toStatic.x;
//
//		toStatic = mGameData.getPlayer()->getOrientation() * toStatic;
//
//		float offsetX = toStatic.x / ( DOT_DISTANCE_SCALE * 4);
//		float offsetZ = toStatic.z / ( DOT_DISTANCE_SCALE * 4);
//
//		ogre2dManager->spriteBltFull("Enemy.png", 
//			0.8  + offsetX - DOT_WIDTH , 
//			0.75 + offsetZ + DOT_HEIGHT,
//			0.8  + offsetX + DOT_WIDTH, 
//			0.75 + offsetZ - DOT_HEIGHT );
//	}
//
//
//
//	//Text stuff
//	//display player velocity as text (actualize text contents)
//	std::stringstream playerVelocityString;
//	playerVelocityString<<"Velocity : "
//		<<mGameData.getPlayer()->getPhysicsComponent().getCurrentVelocityMagnitude()
//		<<", target velocity : "<<mGameData.getPlayer()->getPhysicsComponent().getTargetVelocityValue();
//	playerVelocityText->setCaption( playerVelocityString.str() );
//
//	//display FPS as text 
//	std::stringstream fpsString;
//	fpsString<<"FPS : "<<_time.currentFPSValue;
//	fpsNumber->setCaption( fpsString.str() );
//
//	// Show the overlay
//	overlay->show();
//}
//
//void GUISystem::init( Ogre::SceneManager* mSceneMgr )
//{
//	//2D graphics
//	ogre2dManager = new Ogre2dManager;
//	ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);
//
//	//This function loads image (in example from folder media/materials/textures/ )
//	Ogre::TextureManager::getSingleton().load("radar3.png",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//	Ogre::TextureManager::getSingleton().load("Core.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//	Ogre::TextureManager::getSingleton().load("Enemy.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
//	Ogre::TextureManager::getSingleton().load("Static.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//	Ogre::TextureManager::getSingleton().load("Player.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
//	//End 2D graphics
//
//	//Text Stuff
//	loadFont("arial.ttf");
//
//	// get the resource manager
//	overlayManager = & Ogre::OverlayManager::getSingleton();
//
//	// Create a panel
//	panel = static_cast<Ogre::OverlayContainer*>(
//		overlayManager->createOverlayElement("Panel", "PanelName"));
//	panel->setMetricsMode(Ogre::GMM_PIXELS);
//	panel->setPosition(10, 20);
//	panel->setDimensions(200, 100);
//	panel->setMaterialName( "grayBackground" );
//
//	// Create an overlay, and add the panel
//	overlay = overlayManager->create("OverlayName");
//	overlay->add2D(panel);
//
//	//create text areas
//	playerVelocityText = createText( "playerVelocity1", 0, 25 );
//	fpsNumber = createText( "fps1", 0, 5);
//	//END text stuff
//}
