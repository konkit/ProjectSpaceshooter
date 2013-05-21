#pragma once

/** enum class representing current state of entity AI */
enum class AI_STATE
{
	GET_TO_CORE,
	SHOOT_AT_CORE,
	TURN_AWAY,
	TURN_AROUND,
};

/** enum class representing type of entity AI */
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

	/** sets AI state to specified */
	void setState( AI_STATE newState ){		mState = newState;	}

	/** sets AI type to specified */
	void setType( AI_TYPE newType ) {		mType = newType;	}

	/** returns AI state 
	* @return AI_STATE
	*/
	AI_STATE getState() {	return mState;	}

	/** returns AI type
	* @return AI_STATE
	*/
	AI_TYPE getType() {	return mType;	}

	/** sets new current target position */
	void setCurrentTargetPos(Ogre::Vector3 newPos)	{	cntTargetPos = newPos;	}

	/** returns current target position 
	* @return Ogre::Vector3
	*/
	Ogre::Vector3 getCurrentTargetPos(Ogre::Vector3 newPos)	{	return cntTargetPos;	}
private:
	/** state of AI (FSM one - shooting, evading etc) */
	AI_STATE mState;
	/** type of AI (more active one, more passive etc.) */
	AI_TYPE mType;
	/** position of current target */
	Ogre::Vector3 cntTargetPos;
};