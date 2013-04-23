#include "CppUnitTest.h"
#include <OgreVector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	using Ogre::Vector3;
	using Ogre::Quaternion;
	TEST_CLASS(Colider_tests)
	{
	public:

		//TEST_METHOD(FaildMethod)
		//{
		//	Assert::AreEqual(1,0);
		//}

		TEST_METHOD(BasicColider_Collision)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,21,29);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			colider_struct coll;
			coll.offset = Vector3(0,0,0);
			coll.radius = 27;
			colider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsTrue(result, L"No collision occurring");
		}

		TEST_METHOD(BasicColider_NoCollision)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,21,-1);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			colider_struct coll;
			coll.offset = Vector3(0,0,0);
			coll.radius = 27;
			colider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsFalse(result, L"Collision occurring");
		}

		
		TEST_METHOD(BasicColider_Collision_Offset)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,0,29);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			colider_struct coll;
			coll.offset = Vector3(0,21,0);
			coll.radius = 27;
			colider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsTrue(result, L"No collision occurring");
		}

		TEST_METHOD(BasicColider_NoCollision_Offset)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,0,29);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			colider_struct coll;
			coll.offset = Vector3(0,70,0);
			coll.radius = 27;
			colider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsFalse(result, L"Collision occurring");
		}

		//Colider class have only one colider inside
		//Collision should occurred
		TEST_METHOD(TwoColiders_BasicColision)
		{
			colider_struct tmp;
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 27;
			Collider col1;
			col1.addColider(tmp);
			col1.setInaccurateColider(tmp);
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 15;
			Collider col2;
			col2.addColider(tmp);
			col2.setInaccurateColider(tmp);
			
			position_struct pos1;
			position_struct pos2;
			pos1.position = Vector3(43,21,29);
			pos2.position = Vector3(6,8,24);
			pos1.orientation = pos2.orientation = Quaternion();
			
			bool result = col1.isCollidingWith(pos1,col2,pos2);
			Assert::IsTrue(result);
		}

		//There is a collision in inaccurate coliders, but there are no collision in colider sit 
		TEST_METHOD(TwoColiders_NoColision_IAC)
		{
			position_struct pos1;
			position_struct pos2;
			pos1.position = Vector3(-30,-10, 0);
			pos2.position = Vector3(-91,0,0);
			pos1.orientation = pos2.orientation = Quaternion();
			
			Collider col1;
			Collider col2;
			colider_struct tmp;
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 30; // TODO: Why it's don't work for 25?
			col1.setInaccurateColider(tmp);
			tmp.radius = 35;
			col2.setInaccurateColider(tmp);
		//--------------------------------------
			tmp.radius = 12;
			tmp.offset = pos1.position - Vector3(-13,10,0); //Transform from global coordinates to local coordinates
			col1.addColider(tmp);
			tmp.radius = 7;
			tmp.offset = pos1.position - Vector3(-24,29,0); 
			col1.addColider(tmp);
		//------------ 2 Colider  -------------
			tmp.radius = 13;
			tmp.offset = pos2.position - Vector3(-82,19,0); 
			col2.addColider(tmp);
			tmp.radius = 14;
			tmp.offset = pos2.position - Vector3(-94,-24,0); 
			col2.addColider(tmp);

			bool result = Collider::isCollisionOccuring(col1.getInaccurateColider(), pos1, col2.getInaccurateColider(), pos2); 
			Assert::IsTrue(result, L"There is no collision on inaccurate coliders");

			result = col1.isCollidingWith(pos1,col2,pos2);
			Assert::IsFalse(result, L"There is collision on coliders list");
		}

		//There is a collision in inaccurate coliders, but there are no collision in colider sit 
		TEST_METHOD(TwoColiders_Collision)
		{
			position_struct pos1;
			position_struct pos2;
			pos1.position = Vector3(-30,-10, 0);
			pos2.position = Vector3(-91,0,0);
			pos1.orientation = pos2.orientation = Quaternion();

			Collider col1;
			Collider col2;
			colider_struct tmp;
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 30;
			col1.setInaccurateColider(tmp);
			tmp.radius = 35;
			col2.setInaccurateColider(tmp);
			//--------------------------------------
			tmp.radius = 12;
			tmp.offset = Vector3(-50,10,0) - pos1.position; //Transform from global coordinates to local coordinates
			col1.addColider(tmp);
			tmp.radius = 7;
			tmp.offset = Vector3(-24,29,0) - pos1.position; 
			col1.addColider(tmp);
			//------------ 2 Colider  -------------
			tmp.radius = 13;
			tmp.offset = Vector3(-82,19,0) - pos2.position; 
			col2.addColider(tmp);
			tmp.radius = 14;
			tmp.offset = Vector3(-63,3,0) - pos2.position; 
			col2.addColider(tmp);

			bool result = Collider::isCollisionOccuring(col1.getInaccurateColider(), pos1, col2.getInaccurateColider(), pos2); 
			Assert::IsTrue(result, L"There is no collision on inaccurate coliders");

			result = col1.isCollidingWith(pos1,col2,pos2);
			Assert::IsTrue(result, L"There is no collision on coliders list");
		}

	};
}