#pragma once

#define DOT_WIDTH 0.0075
#define DOT_HEIGHT 0.01
#define RADAR_DOT  0.02

class Radar	{
public:
	void init(Ogre2dManager* _ogre2dManager)	{
		ogre2dManager = _ogre2dManager;

		//This function loads 2d images (in example from folder media/materials/textures/ )
			Ogre::TextureManager::getSingleton().load("radar3.png",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			Ogre::TextureManager::getSingleton().load("Core.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			Ogre::TextureManager::getSingleton().load("Enemy.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
			Ogre::TextureManager::getSingleton().load("Static.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			Ogre::TextureManager::getSingleton().load("Player.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
		//End 2D graphics
	}

	void display(GameData& mGameData, TimeData _time)	{
		//Draw radar background
			ogre2dManager->spriteBltFull("radar3.png", 0.6, 1.0, 1.0, 0.5);

		//Draw objects on radar
			//Draw player dot
			ogre2dManager->spriteBltFull("Player.png", 0.8-DOT_WIDTH , 0.75+DOT_HEIGHT, 0.8+DOT_WIDTH, 0.75-DOT_HEIGHT);
			
			const float DOT_DISTANCE_SCALE = 2500.0f;

			//Draw static
			GameObject* it;
			GameCollectionIterator<StaticObject> myStaticsIterator = mGameData.getStatics().getIterator();
			while (myStaticsIterator.hasNext())
			{
				it = myStaticsIterator.getNext();

				Ogre::Vector3 toStatic =
					 ( it->getPosition() - mGameData.getPlayer()->getPosition() );

				if( toStatic.squaredLength() > 2000.0 * 2000.0)	{
					continue;
				}

				toStatic.x = -toStatic.x;

				toStatic = mGameData.getPlayer()->getOrientation() * toStatic;

				float offsetX = toStatic.x / ( DOT_DISTANCE_SCALE * 4);
				float offsetZ = toStatic.z / ( DOT_DISTANCE_SCALE * 4);

				if( it == &mGameData.getCore() )	{
					ogre2dManager->spriteBltFull("Core.png", 
					0.8  + offsetX - RADAR_DOT, 
					0.75 + offsetZ + RADAR_DOT,
					0.8  + offsetX + RADAR_DOT, 
					0.75 + offsetZ - RADAR_DOT);
				} else {
					ogre2dManager->spriteBltFull("Static.png", 
					0.8  + offsetX - DOT_WIDTH , 
					0.75 + offsetZ + DOT_HEIGHT,
					0.8  + offsetX + DOT_WIDTH, 
					0.75 + offsetZ - DOT_HEIGHT );
				}
			}

			//Draw enemies
			GameCollectionIterator<EnemyObject> myEnemyIterator = mGameData.getEnemies().getIterator();
			while (myEnemyIterator.hasNext())
			{
				it = myEnemyIterator.getNext();

				Ogre::Vector3 toStatic =
					 ( it->getPosition() - mGameData.getPlayer()->getPosition() );

				if( toStatic.squaredLength() > 2000.0 * 2000.0)	{
					continue;
				}

				toStatic.x = -toStatic.x;

				toStatic = mGameData.getPlayer()->getOrientation() * toStatic;

				float offsetX = toStatic.x / ( DOT_DISTANCE_SCALE * 4);
				float offsetZ = toStatic.z / ( DOT_DISTANCE_SCALE * 4);
				
				ogre2dManager->spriteBltFull("Enemy.png", 
					0.8  + offsetX - DOT_WIDTH , 
					0.75 + offsetZ + DOT_HEIGHT,
					0.8  + offsetX + DOT_WIDTH, 
					0.75 + offsetZ - DOT_HEIGHT );
			}
	}

	~Radar()	{
		//Unload loaded 2d images
		Ogre::TextureManager::getSingleton().unload("radar3.png");
		Ogre::TextureManager::getSingleton().unload("Core.png");
		Ogre::TextureManager::getSingleton().unload("Enemy.png"); 
		Ogre::TextureManager::getSingleton().unload("Static.png");
		Ogre::TextureManager::getSingleton().unload("Player.png"); 		
	}


private:
	Ogre2dManager* ogre2dManager;


};
