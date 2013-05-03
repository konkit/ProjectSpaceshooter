#include "stdafx.h"
#include "PrefabPlant.h"
#include "EnemyPrefabPlant.h"
#include "BulletPrefabPlant.h"

#include "Exceptions.h"
#include "StaticPrefabPlant.h"
#include "EffectPrefabPlant.h"
#include "WeaponPrefab_Plant.h"


unsigned int ValueToUINT(const wstring &value )
{ 
	wchar_t *pEnd;
	unsigned int id = static_cast<unsigned int> (wcstol(value.c_str(), &pEnd, 10));
	return id;
}

double ValueToDouble(const wstring &value )
{ 
	wchar_t *pEnd;
	return wcstod(value.c_str(), &pEnd);
}

PrefabPlant::PrefabPlant(void)
	: prefabReady(false)
{
}


PrefabPlant::~PrefabPlant(void)
{
}

void PrefabPlant::nextElement( const wstring & name )
{
	if (name != getPrefabRootNode())
	{
		elements.push(name);
	}
}


void PrefabPlant::nextElement( const wstring & name, const wstring & prefix )
{
	nextElement(name);
}

void PrefabPlant::closeElement( const wstring & name )
{
	setAttribute(L"close", L"");
	
	if(elements.empty() || elements.top() != name)
		throw My_Exception("Close XML Element: XML document don't meet standard");
	else
		elements.pop();


	if (elements.empty())
	{
		prefabReady = true;
	} 
}

void PrefabPlant::closeElement( const wstring & prefix, const wstring & name )
{
	closeElement(name);
}

PrefabPlant * PrefabPlant::CreatePrefabPlantFor( PREFAB_TYPE prefabType )
{
	switch (prefabType)
	{
	case PREFAB_TYPE::EnemyPrefab:
		return new EnemyPrefabPlant;
	case PREFAB_TYPE::BulletPrefab:
		return new BulletPrefabPlant;
	case PREFAB_TYPE::StaticPrefab:
		return new StaticPrefabPlant;
	case PREFAB_TYPE::EffectPrefab:
		return new EffectPrefabPlant;
	case PREFAB_TYPE::LevelDescription:
		break;
	case PREFAB_TYPE::WeaponPrefab:
		return new WeaponPrefabPlant;
	default:
		break;
	}
	return NULL;
}

void PrefabPlant::DeletePrefabPlant( PrefabPlant * _prefabPlant )
{
	delete _prefabPlant;
}

bool PrefabPlant::IsPrefabReady()
{
	return prefabReady;
}




void PrefabWithCollider_Plant::_setCollider( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::closeNode)
	{
		if (prefabWithCollider == NULL)
		{
			throw My_Exception("PrefabWithCollider setCollider: Can't add Collider into nonexistent prefab");
		}
		prefabWithCollider->addCollider(Collider_str);
		clearCollider();
	} else
	{
		throw My_Exception("PrefabWithCollider _setCollider: Missing attribute type");
	}
}


void PrefabWithCollider_Plant::_setInaccurateCollider( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::closeNode)
	{
		if (prefabWithCollider == NULL)
		{
			throw My_Exception("PrefabWithCollider setCollider: Can't add Collider into nonexistent prefab");
		}
		prefabWithCollider->setInaccurateCollider(Collider_str);
		clearCollider();
	} else
	{
		throw My_Exception("PrefabWithCollider _setCollider: Missing attribute type");
	}
}


void PrefabWithCollider_Plant::_setColliderOffset( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::x_pos)
	{
		Collider_str.offset.x= ValueToDouble(value);
	} else if (attribute == PrefabPlant::y_pos)
	{
		Collider_str.offset.y = ValueToDouble(value);
	} else if (attribute == PrefabPlant::z_pos)
	{
		Collider_str.offset.z = ValueToDouble(value);
	} else if (attribute == PrefabPlant::closeNode)
	{
		return;
	}	else
	{
		wstring tmp(L"PrefabWithCollider_Plant _setColliderOffset: Missing attribute type: ");
		tmp += attribute; 
		throw My_Exception(tmp);
	}
}

void PrefabWithCollider_Plant::_setColliderRadius( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		Collider_str.radius = ValueToUINT(value);

	} else if (attribute == PrefabPlant::closeNode)
	{
		return;
	} else
	{
		wstring tmp(L"EnemyPrefabPlant _setColliderRadius: Missing attribute type: ");
		tmp += attribute; 
		throw My_Exception(tmp);
	}
}

void PrefabWithCollider_Plant::clearCollider()
{
	Collider_str.offset.x = Collider_str.offset.y = Collider_str.offset.z = 0;
	Collider_str.radius = 0;
}


PrefabWithCollider_Plant::PrefabWithCollider_Plant()
	:prefabWithCollider(NULL)
{
}


PrefabWithCollider_Plant::~PrefabWithCollider_Plant()
{

}

void PrefabWithCollider_Plant::_setMaxHealth( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned int val;
		val = ValueToUINT(value);
		prefabWithCollider->setMaxHealth(val);
	};
}

void PrefabWithCollider_Plant::_setExplosionID( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::id)
	{
		unsigned int val;
		val = ValueToUINT(value);
		prefabWithCollider->setExplosionEffectID(val);
	};
}

bool PrefabWithCollider_Plant::setAttribute( const wstring & attribute, const wstring & value )
{
	if (elements.size() < 2)
	{
		return false; // Because next line can't execute if there is less then one element on stack
					  // If there are less then 2 element on stack it can be Prefab property
	}

	wstring stack_top = elements.top(); 
	//There is required to know value which is below top of stack
	elements.pop();
	const wstring & stack_prev = elements.top();
	elements.push(stack_top);

	if (stack_top == PrefabWithCollider_Plant::health)
	{
		_setMaxHealth(attribute, value);
	} else if (stack_top == PrefabWithCollider_Plant::Colliders)
	{
		return true;
	}
	else if (stack_top == PrefabWithCollider_Plant::Collider)
	{
		_setCollider(attribute, value);
	}
	else if (stack_top == PrefabWithCollider_Plant::inaccurate_Collider)
	{
		_setInaccurateCollider(attribute, value);
	}
	else if (stack_top == PrefabWithCollider_Plant::offset)
	{
		if (stack_prev == Collider || stack_prev == inaccurate_Collider) // TODO
		{
			_setColliderOffset(attribute, value);
		}
	}
	else if (stack_top == PrefabWithCollider_Plant::radius)
	{
		_setColliderRadius(attribute, value);
	} else if (stack_top == PrefabWithCollider_Plant::explosion_id)
	{
		_setExplosionID(attribute, value);
	} else
	{
		return false;
	}
	return true;
	
}

bool PrefabWithCollider_Plant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return PrefabWithCollider_Plant::setAttribute(attribute, value);
}

void PrefabPlant::_doNothing( const wstring & attribute, const wstring & value )
{
	return;
}

bool PrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	wstring name = elements.top();
	if (name == getPrefabNodeName())
	{
		_setPrefabID(attribute, value);
	} else if (name == getPrefabName())
	{
		_setPrefabName(attribute, value);
	} else
	{
		return false;
	}
	return true;
}

bool PrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute,value);
}

void PrefabPlant::setPrefab( Prefab * pref )
{
	_prefab = pref;
}


void PrefabPlant::_setPrefabID( const wstring & attribute, const wstring & value )
{
	if (attribute == id)
	{
		unsigned int id;
		id = ValueToUINT(value);
		_prefab->setPrefabID(id);
	};

}

void PrefabPlant::_setPrefabName( const wstring & attribute, const wstring & value )
{
	if (attribute == name)
	{
		_prefab->setName(string(value.begin(), value.end()));
	}
}

void PrefabWithMesh_Plant::_setMeshName( const wstring & attribute, const wstring & value )
{
	if (attribute == name)
	{
		if (_prefabWithMesh == NULL)
		{
			throw("PrefabWithMesh setMesh: try to use uninitialized prefab");
		}
		_prefabWithMesh->setMeshName(string(value.begin(),value.end()));
	};
}

void PrefabWithMesh_Plant::_setScale( const wstring & attribute, const wstring & value )
{
	static Vector3 scale;
	if (attribute == x_scale)
	{
		scale.x = ValueToDouble(value);
	} else if (attribute == y_scale)
	{
		scale.y = ValueToDouble(value);
	} else if (attribute == z_scale)
	{
		scale.z = ValueToDouble(value);
	} else if (attribute == closeNode)
	{
		if (_prefabWithMesh == NULL)
		{
			throw("PrefabWithMesh SetScale: try to use uninitialized prefab");
		}
		_prefabWithMesh->setScale(scale);
		scale.x = scale.y = scale.z = 0.0;
	} else
	{
		throw My_Exception("PrefabWithMesh_Plant _setScale: Missing attribute type");
	}
}

void PrefabWithMesh_Plant::_setRotation( const wstring & attribute, const wstring & value )
{
	static rotation_struct rot;
	if (attribute == x_rot)
	{
		rot.x_rot = ValueToDouble(value);
	} else if (attribute == y_rot)
	{
		rot.y_rot = ValueToDouble(value);
	} else if (attribute == z_rot)
	{
		rot.z_rot = ValueToDouble(value);
	} else if (attribute == closeNode)
	{
		if (_prefabWithMesh == NULL)
		{
			throw("PrefabWithMesh SetRotation: try to use uninitialized prefab");
		}
		_prefabWithMesh->setRotation(rot);
		rot.x_rot = rot.y_rot = rot.z_rot = 0;
	} else
	{
		throw My_Exception("PrefabPlantWithMesh _setRotation: Missing attribute type");
	}
}



PrefabWithMesh_Plant::PrefabWithMesh_Plant()
{
}

PrefabWithMesh_Plant::~PrefabWithMesh_Plant()
{

}

bool PrefabWithMesh_Plant::setAttribute( const wstring & attribute, const wstring & value )
{
	wstring name = elements.top();

	if (name == PrefabWithMesh_Plant::mesh)
	{
		_setMeshName(attribute, value);
	} else if (name == PrefabWithMesh_Plant::scale)
	{
		_setScale(attribute, value);
	}
	else if (name == PrefabWithMesh_Plant::rotation)
	{
		_setRotation(attribute, value);
	} else
	{
		return false;
	}
	return true;
}

bool PrefabWithMesh_Plant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute, value);
}

const wchar_t * PrefabPlant::max_acceleration   = L"max_acceleration";
const wchar_t * PrefabPlant::max_velocity       = L"max_velocity";
const wchar_t * PrefabPlant::max_angle_velocity = L"max_angle_velocity";
const wchar_t * PrefabPlant::standard_waepon    = L"standard_waepon";
const wchar_t * PrefabPlant::name	            = L"name";
const wchar_t * PrefabPlant::id		            = L"id";
const wchar_t * PrefabPlant::value	            = L"value";
const wchar_t * PrefabPlant::x_pos	            = L"x_pos";
const wchar_t * PrefabPlant::y_pos	            = L"y_pos";
const wchar_t * PrefabPlant::z_pos	            = L"z_pos";
const wchar_t * PrefabPlant::closeNode	        = L"close";
const wchar_t * PrefabPlant::yes                = L"yes";
const wchar_t * PrefabPlant::no                 = L"no";


const wchar_t * PrefabWithMesh_Plant::scale	  = L"scale";
const wchar_t * PrefabWithMesh_Plant::rotation= L"rotation";
const wchar_t * PrefabWithMesh_Plant::x_scale = L"x_scale";
const wchar_t * PrefabWithMesh_Plant::y_scale = L"y_scale";
const wchar_t * PrefabWithMesh_Plant::z_scale = L"z_scale";
const wchar_t * PrefabWithMesh_Plant::x_rot	  = L"x_rot";
const wchar_t * PrefabWithMesh_Plant::y_rot	  = L"y_rot";
const wchar_t * PrefabWithMesh_Plant::z_rot	  = L"z_rot";
const wchar_t * PrefabWithMesh_Plant::mesh	  = L"mesh";

const wchar_t * PrefabWithCollider_Plant::health		      = L"health";
const wchar_t * PrefabWithCollider_Plant::Colliders	          = L"Colliders";
const wchar_t * PrefabWithCollider_Plant::Collider            = L"Collider";
const wchar_t * PrefabWithCollider_Plant::offset              = L"offset";
const wchar_t * PrefabWithCollider_Plant::radius              = L"radius";
const wchar_t * PrefabWithCollider_Plant::inaccurate_Collider = L"inaccurate_Collider";
const wchar_t * PrefabWithCollider_Plant::explosion_id        = L"explosion_id";
