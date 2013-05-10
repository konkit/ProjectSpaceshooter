#include "stdafx.h"
#include "LevelDescription.h"



void LevelDescription::clearLevelDescription()
{
	levelStageCollection.clearCollection();
	staticObjectList.clearCollection();
	lightsCollections.clearCollection();
}
