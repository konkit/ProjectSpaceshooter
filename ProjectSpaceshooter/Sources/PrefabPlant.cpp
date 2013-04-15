#include "stdafx.h"
#include "PrefabPlant.h"
#include "EnemyPrefabPlant.h"
#include "BulletPrefabPlant.h"

#include "Exceptions.h"
#include "StaticPrefabPlant.h"
#include "EffectPrefabPlant.h"
#include "WeaponPrefab_Plant.h"
PrefabPlant::PrefabPlant(void)
	: prefabReady(false)
{
}


PrefabPlant::~PrefabPlant(void)
{
}

void PrefabPlant::nextElement( const wstring & name )
{
	elements.push(name);
	setMethodToFillProperty(name);
}


void PrefabPlant::nextElement( const wstring & name, const wstring & prefix )
{
	nextElement(name);
}

void PrefabPlant::closeElement( const wstring & name )
{
	if(elements.empty() || elements.top() != name)
		throw My_Exception("Close XML Element: XML document don't meet standard");
	else
		elements.pop();

	fillPrefabProperty(L"close", L"");

	if (elements.empty())
	{
		prefabReady = true;
	} else
	{
		setMethodToFillProperty(elements.top());
	}}

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

unsigned int PrefabPlant::ValueToUINT(const wstring &value )
{ 
	wchar_t *pEnd;
	unsigned int id = static_cast<unsigned int> (wcstol(value.c_str(), &pEnd, 10));
	return id;
}

double PrefabPlant::ValueToDouble(const wstring &value )
{ 
	wchar_t *pEnd;
	return wcstod(value.c_str(), &pEnd);
}

void PrefabWithColider_Plant::_setColider( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::closeNode)
	{
		if (prefabWithColider == NULL)
		{
			throw My_Exception("PrefabWithColider setColider: Can't add colider into nonexistent prefab");
		}
		prefabWithColider->addColider(colider_str);
		clearColider();
	} else
	{
		throw My_Exception("PrefabWithColider _setCollider: Missing attribute type");
	}
}

void PrefabWithColider_Plant::_setColiderOffset( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::x_pos)
	{
		colider_str.offset.x= ValueToUINT(value);
	} else if (attribute == PrefabPlant::y_pos)
	{
		colider_str.offset.y = ValueToUINT(value);
	} else if (attribute == PrefabPlant::z_pos)
	{
		colider_str.offset.z = ValueToUINT(value);
	} else if (attribute == PrefabPlant::closeNode)
	{
		return;
	}	else
	{
		wstring tmp(L"PrefabWithColider_Plant _setColiderOffset: Missing attribute type: ");
		tmp += attribute; 
		throw My_Exception(tmp);
	}
}

void PrefabWithColider_Plant::_setColiderRadian( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		colider_str.radian = ValueToUINT(value);
	} else if (attribute == PrefabPlant::closeNode)
	{
		return;
	} else
	{
		wstring tmp(L"EnemyPrefabPlant _setColiderRadian: Missing attribute type: ");
		tmp += attribute; 
		throw My_Exception(tmp);
	}
}

void PrefabWithColider_Plant::clearColider()
{
	colider_str.offset.x = colider_str.offset.y = colider_str.offset.z = 0;
	colider_str.radian = 0;
}


PrefabWithColider_Plant::PrefabWithColider_Plant()
	:prefabWithColider(NULL)
{
	methodToFillColiderProperty = &PrefabWithColider_Plant::_doNothing;
}

bool PrefabWithColider_Plant::SetMethodToFillColiderProperty( const wstring & name )
{

	if (name == PrefabWithColider_Plant::health)
	{
		methodToFillColiderProperty = &PrefabWithColider_Plant::_setMaxHealth;
	} else if (name == PrefabWithColider_Plant::coliders)
	{
		methodToFillColiderProperty = &PrefabWithColider_Plant::_doNothing;
	}
	else if (name == PrefabWithColider_Plant::colider)
	{
		methodToFillColiderProperty = &PrefabWithColider_Plant::_setColider;
	}	
	else if (name == PrefabWithColider_Plant::offset)
	{
		if (methodToFillColiderProperty == &PrefabWithColider_Plant::_setColider)
		{
			methodToFillColiderProperty = &PrefabWithColider_Plant::_setColiderOffset;
		} else
		{
			throw My_Exception("PrefabWithColider_Plant nextElement: incorrect Prefab format - offset is not inside colider node");
		}
	}
	else if (name == PrefabWithColider_Plant::radian)
	{
		if (methodToFillColiderProperty == &PrefabWithColider_Plant::_setColider)
		{
			methodToFillColiderProperty = &PrefabWithColider_Plant::_setColiderRadian;
		} else
		{
			throw My_Exception("PrefabWithColider_Plant nextElement: incorrect Prefab format - radian is not inside colider node");
		}
	} else
	{
		return false;
	}
	return true;
}

PrefabWithColider_Plant::~PrefabWithColider_Plant()
{

}

void PrefabWithColider_Plant::_setMaxHealth( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned int val;
		val = ValueToUINT(value);
		prefabWithColider->setMaxHealth(val);
	};
}

void PrefabPlant::_doNothing( const wstring & attribute, const wstring & value )
{
	return;
}

void PrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	fillPrefabProperty(attribute, value);
}

void PrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	setAttribute(attribute,value);
}

void PrefabPlant::setPrefab( Prefab * pref )
{
	_prefab = pref;
}

bool PrefabPlant::SetMethodToFillBasicProperty( const wstring & name )
{
	if (name == getPrefabNodeName())
	{
		methodToFillBasicProperty = &PrefabPlant::_setPrefabID;
	} else if (name == getPrefabName())
	{
		methodToFillBasicProperty = &PrefabPlant::_setPrefabName;
	} else
	{
		return false;
	}
		return true;
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
		scale.x = ValueToUINT(value);
	} else if (attribute == y_scale)
	{
		scale.y = ValueToUINT(value);
	} else if (attribute == z_scale)
	{
		scale.z = ValueToUINT(value);
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

bool PrefabWithMesh_Plant::SetMethodToFillMeshProperty( const wstring & name )
{
	if (name == PrefabWithMesh_Plant::mesh)
	{
		methodToFillMeshProperty = &PrefabWithMesh_Plant::_setMeshName;
	} else if (name == PrefabWithMesh_Plant::scale)
	{
		methodToFillMeshProperty = &PrefabWithMesh_Plant::_setScale;
	}
	else if (name == PrefabWithMesh_Plant::rotation)
	{
		methodToFillMeshProperty = &PrefabWithMesh_Plant::_setRotation;
	} else
	{
		return false;
	}
		return true;
}

PrefabWithMesh_Plant::PrefabWithMesh_Plant()
{
	methodToFillMeshProperty = &PrefabWithMesh_Plant::_doNothing;
}

PrefabWithMesh_Plant::~PrefabWithMesh_Plant()
{

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

const wchar_t * PrefabWithColider_Plant::health		= L"health";
const wchar_t * PrefabWithColider_Plant::coliders	= L"coliders";
const wchar_t * PrefabWithColider_Plant::colider    = L"colider";
const wchar_t * PrefabWithColider_Plant::offset     = L"offset";
const wchar_t * PrefabWithColider_Plant::radian     = L"radian";
