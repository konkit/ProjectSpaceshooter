#include "stdafx.h"
#include "PrefabPlant.h"
#include "EnemyPrefabPlant.h"
#include "Exceptions.h"
PrefabPlant::PrefabPlant(void)
	: prefabReady(true)
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
		break;
	case PREFAB_TYPE::StaticPrefab:
		break;
	case PREFAB_TYPE::EffectPrefab:
		break;
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

void PrefabWithColider_Plant::_setColider( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::close)
	{
		if (prefabWithColider == NULL)
		{
			throw My_Exception("PrefabWithColider setColider: Can't add colider into nonexistent prefab");
		}
		prefabWithColider->addColider(colider);
		clearColider();
	} else
	{
		throw My_Exception("EnemyPrefabPlant _setCollider: Missing attribute type");
	}
}

void PrefabWithColider_Plant::_setColiderOffset( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::x_pos)
	{
		colider.offset.x_pos= ValueToUINT(value);
	} else if (attribute == PrefabPlant::y_pos)
	{
		colider.offset.y_pos = ValueToUINT(value);
	} else if (attribute == PrefabPlant::z_pos)
	{
		colider.offset.z_pos = ValueToUINT(value);
	} else if (attribute == PrefabPlant::close)
	{
		return;
	}	else
	{
		wstring tmp(L"EnemyPrefabPlant _setColiderOffset: Missing attribute type: ");
		tmp += attribute; 
		throw My_Exception(tmp);
	}
}

void PrefabWithColider_Plant::_setColiderRadian( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		colider.radian = ValueToUINT(value);
	} else if (attribute == PrefabPlant::close)
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
	colider.offset.x_pos = colider.offset.y_pos = colider.offset.z_pos = 0;
	colider.radian = 0;
}


PrefabWithColider_Plant::PrefabWithColider_Plant()
	:prefabWithColider(NULL)
{
	methodToFillColiderProperty = &PrefabWithColider_Plant::_doNothing;
}

bool PrefabWithColider_Plant::SetMethodToFillColiderProperty( const wstring & name )
{

	if (name == PrefabPlant::coliders)
	{
		methodToFillColiderProperty = &PrefabWithColider_Plant::_doNothing;
	}
	else if (name == PrefabPlant::colider)
	{
		methodToFillColiderProperty = &PrefabWithColider_Plant::_setColider;
	}	
	else if (name == PrefabPlant::offset)
	{
		if (methodToFillColiderProperty == &PrefabWithColider_Plant::_setColider)
		{
			methodToFillColiderProperty = &PrefabWithColider_Plant::_setColiderOffset;
		} else
		{
			throw My_Exception("PrefabWithColider_Plant nextElement: incorrect Prefab format - offset is not inside colider node");
		}
	}
	else if (name == PrefabPlant::radian)
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
	static scale_struct scale;
	if (attribute == PrefabPlant::x_scale)
	{
		scale.x_scale = ValueToUINT(value);
	} else if (attribute == PrefabPlant::y_scale)
	{
		scale.y_scale = ValueToUINT(value);
	} else if (attribute == PrefabPlant::z_scale)
	{
		scale.z_scale = ValueToUINT(value);
	} else if (attribute == PrefabPlant::close)
	{
		if (_prefabWithMesh == NULL)
		{
			throw("PrefabWithMesh SetScale: try to use uninitialized prefab");
		}
		_prefabWithMesh->setScale(scale);
		scale.x_scale = scale.y_scale = scale.z_scale = 0;
	} else
	{
		throw My_Exception("PrefabWithMesh_Plant _setScale: Missing attribute type");
	}
}

void PrefabWithMesh_Plant::_setRotation( const wstring & attribute, const wstring & value )
{
	static rotation_struct rot;
	if (attribute == PrefabPlant::x_rot)
	{
		rot.x_rot = ValueToUINT(value);
	} else if (attribute == PrefabPlant::y_rot)
	{
		rot.y_rot = ValueToUINT(value);
	} else if (attribute == PrefabPlant::z_rot)
	{
		rot.z_rot = ValueToUINT(value);
	} else if (attribute == PrefabPlant::close)
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
	if (name == PrefabPlant::mesh)
	{
		methodToFillMeshProperty = &PrefabWithMesh_Plant::_setMeshName;
	} else if (name == PrefabPlant::scale)
	{
		methodToFillMeshProperty = &PrefabWithMesh_Plant::_setScale;
	}
	else if (name == PrefabPlant::rotation)
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




const wchar_t * PrefabPlant::max_acceleration = L"max_acceleration";
const wchar_t * PrefabPlant::max_velocity=L"max_velocity";
const wchar_t * PrefabPlant::max_angle_velocity = L"max_angle_velocity";
const wchar_t * PrefabPlant::health			 = L"health";
const wchar_t * PrefabPlant::scale			 = L"scale";
const wchar_t * PrefabPlant::rotation		 = L"rotation";
const wchar_t * PrefabPlant::coliders		 = L"coliders";
const wchar_t * PrefabPlant::standard_waepon = L"standard_waepon";
const wchar_t * PrefabPlant::name	= L"name";
const wchar_t * PrefabPlant::id		= L"id";
const wchar_t * PrefabPlant::value	= L"value";
const wchar_t * PrefabPlant::x_scale= L"x_scale";
const wchar_t * PrefabPlant::y_scale= L"y_scale";
const wchar_t * PrefabPlant::z_scale= L"z_scale";
const wchar_t * PrefabPlant::x_rot	= L"x_rot";
const wchar_t * PrefabPlant::y_rot	= L"y_rot";
const wchar_t * PrefabPlant::z_rot	= L"z_rot";
const wchar_t * PrefabPlant::x_pos	= L"x_pos";
const wchar_t * PrefabPlant::y_pos	= L"y_pos";
const wchar_t * PrefabPlant::z_pos	= L"z_pos";
const wchar_t * PrefabPlant::close	= L"close";

const wchar_t * PrefabPlant::mesh	= L"mesh";
const wchar_t * PrefabPlant::colider= L"colider";
const wchar_t * PrefabPlant::offset = L"offset";
const wchar_t * PrefabPlant::radian = L"radian";
