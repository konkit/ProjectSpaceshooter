#pragma once

enum class AI_STATE
{
	GET_TO_CORE,
	SHOOT_AT_CORE,
	TURN_AWAY,
	TURN_AROUND,
};

enum class AI_TYPE
{
	fighter,
	defender
};


/** AI Component stores all data about Artificial Inteligence of
  * gameobject. Such things like type of AI or States of Finite State automata
  * are present there.
  *
  * @author konkit
  */
class AIComponent {
public:
	AIComponent() : mState(AI_STATE::GET_TO_CORE)
	{}

	void setState( AI_STATE newState ){
		mState = newState;
	}

	void setType( AI_TYPE newType ) {
		mType = newType;
	}


	AI_STATE getState() {
		return mState;
	}

	AI_TYPE getType() {
		return mType;
	}


	Ogre::Vector3 cntTarget;

private:
	AI_STATE mState;
	AI_TYPE mType;
};