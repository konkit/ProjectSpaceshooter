#include "CppUnitTest.h"
#include <OgreVector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	using Ogre::Vector3;
	using Ogre::Quaternion;
	TEST_CLASS(Collider_tests)
	{
	public:

		//TEST_METHOD(FaildMethod)
		//{
		//	Assert::AreEqual(1,0);
		//}

		TEST_METHOD(BasicCollider_Collision)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,21,29);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			Collider_struct coll;
			coll.offset = Vector3(0,0,0);
			coll.radius = 27;
			Collider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsTrue(result, L"No collision occurring");
		}

		TEST_METHOD(BasicCollider_NoCollision)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,21,-1);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			Collider_struct coll;
			coll.offset = Vector3(0,0,0);
			coll.radius = 27;
			Collider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsFalse(result, L"Collision occurring");
		}

		
		TEST_METHOD(BasicCollider_Collision_Offset)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,0,29);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			Collider_struct coll;
			coll.offset = Vector3(0,21,0);
			coll.radius = 27;
			Collider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsTrue(result, L"No collision occurring");
		}

		TEST_METHOD(BasicCollider_NoCollision_Offset)
		{
			position_struct tmp;
			position_struct tmp2;
			tmp.position = Vector3(43,0,29);
			tmp2.position = Vector3(6,8,24);
			tmp.orientation = tmp2.orientation = Quaternion();
			Collider_struct coll;
			coll.offset = Vector3(0,70,0);
			coll.radius = 27;
			Collider_struct coll2;
			coll2.offset = Vector3(0,0,0);
			coll2.radius = 15;
			bool result = Collider::isCollisionOccuring(coll, tmp, coll2, tmp2);
			Assert::IsFalse(result, L"Collision occurring");
		}

		//Collider class have only one Collider inside
		//Collision should occurred
		TEST_METHOD(TwoColliders_BasicColision)
		{
			Collider_struct tmp;
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 27;
			Collider col1;
			col1.addCollider(tmp);
			col1.setInaccurateCollider(tmp);
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 15;
			Collider col2;
			col2.addCollider(tmp);
			col2.setInaccurateCollider(tmp);
			
			position_struct pos1;
			position_struct pos2;
			pos1.position = Vector3(43,21,29);
			pos2.position = Vector3(6,8,24);
			pos1.orientation = pos2.orientation = Quaternion();
			
			bool result = col1.isCollidingWith(pos1,col2,pos2);
			Assert::IsTrue(result);
		}

		//There is a collision in inaccurate Colliders, but there are no collision in Collider sit 
		TEST_METHOD(TwoColliders_NoColision_IAC)
		{
			position_struct pos1;
			position_struct pos2;
			pos1.position = Vector3(-30,-10, 0);
			pos2.position = Vector3(-91,0,0);
			pos1.orientation = pos2.orientation = Quaternion();
			
			Collider col1;
			Collider col2;
			Collider_struct tmp;
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 30; // TODO: Why it's don't work for 25?
			col1.setInaccurateCollider(tmp);
			tmp.radius = 35;
			col2.setInaccurateCollider(tmp);
		//--------------------------------------
			tmp.radius = 12;
			tmp.offset = pos1.position - Vector3(-13,10,0); //Transform from global coordinates to local coordinates
			col1.addCollider(tmp);
			tmp.radius = 7;
			tmp.offset = pos1.position - Vector3(-24,29,0); 
			col1.addCollider(tmp);
		//------------ 2 Collider  -------------
			tmp.radius = 13;
			tmp.offset = pos2.position - Vector3(-82,19,0); 
			col2.addCollider(tmp);
			tmp.radius = 14;
			tmp.offset = pos2.position - Vector3(-94,-24,0); 
			col2.addCollider(tmp);

			bool result = Collider::isCollisionOccuring(col1.getInaccurateCollider(), pos1, col2.getInaccurateCollider(), pos2); 
			Assert::IsTrue(result, L"There is no collision on inaccurate Colliders");

			result = col1.isCollidingWith(pos1,col2,pos2);
			Assert::IsFalse(result, L"There is collision on Colliders list");
		}

		//There is a collision in inaccurate Colliders, but there are no collision in Collider sit 
		TEST_METHOD(TwoColliders_Collision)
		{
			position_struct pos1;
			position_struct pos2;
			pos1.position = Vector3(-30,-10, 0);
			pos2.position = Vector3(-91,0,0);
			pos1.orientation = pos2.orientation = Quaternion();

			Collider col1;
			Collider col2;
			Collider_struct tmp;
			tmp.offset = Vector3(0,0,0);
			tmp.radius = 30;
			col1.setInaccurateCollider(tmp);
			tmp.radius = 35;
			col2.setInaccurateCollider(tmp);
			//--------------------------------------
			tmp.radius = 12;
			tmp.offset = Vector3(-50,10,0) - pos1.position; //Transform from global coordinates to local coordinates
			col1.addCollider(tmp);
			tmp.radius = 7;
			tmp.offset = Vector3(-24,29,0) - pos1.position; 
			col1.addCollider(tmp);
			//------------ 2 Collider  -------------
			tmp.radius = 13;
			tmp.offset = Vector3(-82,19,0) - pos2.position; 
			col2.addCollider(tmp);
			tmp.radius = 14;
			tmp.offset = Vector3(-63,3,0) - pos2.position; 
			col2.addCollider(tmp);

			bool result = Collider::isCollisionOccuring(col1.getInaccurateCollider(), pos1, col2.getInaccurateCollider(), pos2); 
			Assert::IsTrue(result, L"There is no collision on inaccurate Colliders");

			result = col1.isCollidingWith(pos1,col2,pos2);
			Assert::IsTrue(result, L"There is no collision on Colliders list");
		}

	};
}