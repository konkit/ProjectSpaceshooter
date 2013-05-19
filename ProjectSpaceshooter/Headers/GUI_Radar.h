#pragma once

#define DOT_WIDTH 0.0075
#define DOT_HEIGHT 0.01

class Radar	{
public:
	void init(Ogre2dManager* _ogre2dManager)	{
		ogre2dManager = _ogre2dManager;

		//This function loads 2d images (in example from folder media/materials/textures/ )
			Ogre::TextureManager::getSingleton().load("radar_background.png",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			Ogre::TextureManager::getSingleton().load("blue_dot.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			Ogre::TextureManager::getSingleton().load("red_dot.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
			Ogre::TextureManager::getSingleton().load("green_dot.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			Ogre::TextureManager::getSingleton().load("violet_dot.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
		//End 2D graphics
	}

	void display(GameData& mGameData, TimeData _time)	{
		//Draw radar background
		ogre2dManager->spriteBltFull("radar_background.png", 0.6, 1.0, 1.0, 0.5);

		//Draw objects on radar
			//Draw player dot
			ogre2dManager->spriteBltFull("violet_dot.png", 0.8-DOT_WIDTH , 0.75+DOT_HEIGHT, 0.8+DOT_WIDTH, 0.75-DOT_HEIGHT);
			
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
					ogre2dManager->spriteBltFull("blue_dot.png", 
					0.8  + offsetX - DOT_WIDTH , 
					0.75 + offsetZ + DOT_HEIGHT,
					0.8  + offsetX + DOT_WIDTH, 
					0.75 + offsetZ - DOT_HEIGHT );
				} else {
					ogre2dManager->spriteBltFull("green_dot.png", 
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
				
				ogre2dManager->spriteBltFull("red_dot.png", 
					0.8  + offsetX - DOT_WIDTH , 
					0.75 + offsetZ + DOT_HEIGHT,
					0.8  + offsetX + DOT_WIDTH, 
					0.75 + offsetZ - DOT_HEIGHT );
			}
	}

	~Radar()	{
		//Unload loaded 2d images
		Ogre::TextureManager::getSingleton().unload("radar_background.png");
		Ogre::TextureManager::getSingleton().unload("blue_dot.png");
		Ogre::TextureManager::getSingleton().unload("red_dot.png");
		Ogre::TextureManager::getSingleton().unload("green_dot.png");
		Ogre::TextureManager::getSingleton().unload("violet_dot.png");
	}


private:
	Ogre2dManager* ogre2dManager;


};
