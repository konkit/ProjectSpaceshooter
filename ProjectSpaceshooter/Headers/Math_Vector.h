#pragma once


namespace GameUtils
{

	class Vector3
	{
		void set(float nx, float ny, float nz)	{
			x = nx;
			y = ny;
			z = nz;
		}

		Ogre::Vector3 toOgreVector()
		{
			Ogre::Vector3 result(x, y, z);
			return result;
		}

		float x, y, z;
	private:

	};
}