#include "EnemyPrefabPlant.h"


const wstring EnemyPrefabPlant::rootEnemyPrefabsNode(L"ship_prefabs");
const wstring EnemyPrefabPlant::prefabName(L"ship");

EnemyPrefabPlant::EnemyPrefabPlant()
{

}

EnemyPrefabPlant::~EnemyPrefabPlant()
{

}

void EnemyPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	(this->*methodToFillProperty)(attribute,value);
}

void EnemyPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	setAttribute(attribute,value);
}


void EnemyPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

void EnemyPrefabPlant::resetPrefab()
{
	_enemyPrefab.resetFields();
}

const wstring & EnemyPrefabPlant::getPrefabRootNode()
{
	return rootEnemyPrefabsNode;
}

const wstring & EnemyPrefabPlant::getPrefabName()
{
	return prefabName;
}

void EnemyPrefabPlant::nextElement( const wstring & name )
{
	elements.push(name);
	setMethodToFillProperty(name);

}

void EnemyPrefabPlant::nextElement( const wstring & prefix, const wstring & name )
{
	nextElement(name);
}
void EnemyPrefabPlant::closeElement( const wstring & name )
{
	if(elements.empty() || elements.top() != name)
		throw My_Exception("Close XML Element: XML document don't meet standard");
	else
		elements.pop();
	(this->*methodToFillProperty)(L"close",L"");

	if (elements.empty())
	{
		prefabReady = true;
	} else
	{
		setMethodToFillProperty(elements.top());
	}
}

void EnemyPrefabPlant::closeElement( const wstring & prefix, const wstring & name )
{
	closeElement(name);
}

void EnemyPrefabPlant::setMethodToFillProperty( const wstring & name )
{
	if (name == EnemyPrefabPlant::ship)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setPrefabID;
	} else if (name == EnemyPrefabPlant::ship_name)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setShipName;
	} else if (name == PrefabPlant::mesh)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setMeshName;
	} else if (name == PrefabPlant::max_velocity)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setMaxVelocity;
	}
	else if (name == PrefabPlant::max_acceleration)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setMaxAcceleration;
	}
	else if (name == PrefabPlant::max_angle_velocity)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setMaxAngleVellocity;
	}
	else if (name == PrefabPlant::health)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setMaxHealth;
	}
	else if (name == PrefabPlant::scale)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setScale;
	}
	else if (name == PrefabPlant::rotation)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setRotation;
	}
	else if (name == PrefabPlant::coliders)
	{
		methodToFillProperty = &EnemyPrefabPlant::_doNothing;
	}
	else if (name == PrefabPlant::colider)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setColider;
	}	
	else if (name == PrefabPlant::offset)
	{
		if (methodToFillProperty == &EnemyPrefabPlant::_setColider)
		{
			methodToFillProperty = &EnemyPrefabPlant::_setColiderOffset;
		} else
		{
			throw My_Exception("EnemyPrefabPlant nextElement: incorrect Enemy Prefab format - offset is not inside colider node");
		}
	}
	else if (name == PrefabPlant::radian)
	{
		if (methodToFillProperty == &EnemyPrefabPlant::_setColider)
		{
			methodToFillProperty = &EnemyPrefabPlant::_setColiderRadian;
		} else
		{
			throw My_Exception("EnemyPrefabPlant nextElement: incorrect Enemy Prefab format - radian is not inside colider node");
		}
	}
	else if (name == PrefabPlant::standard_waepon)
	{
		methodToFillProperty = &EnemyPrefabPlant::_setWaeponPrefab;
	}	
	else
	{
		methodToFillProperty = &EnemyPrefabPlant::_doNothing;
	}

}


Prefab * EnemyPrefabPlant::getCreatedPrefab()
{
	return static_cast<Prefab *>(&_enemyPrefab);
}

void EnemyPrefabPlant::_setPrefabID( const wstring & attribute, const wstring & value )
{
	if (attribute == id)
	{
		unsigned int id;
		id = ValueToUINT(value);
		_enemyPrefab.setPrefabID(id);
	};
}

void EnemyPrefabPlant::_setWaeponPrefab( const wstring & attribute, const wstring & value )
{
	if (attribute == id)
	{
		unsigned int id;
		id = ValueToUINT(value);
		_enemyPrefab.setWeaponPrefabID(id);
	};
}

void EnemyPrefabPlant::_setMeshName( const wstring & attribute, const wstring & value )
{
	if (attribute == name)
	{
		_enemyPrefab.setMeshName(string(value.begin(),value.end()));
	};
}



void EnemyPrefabPlant::_setMaxVelocity( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned int val;
		val = ValueToUINT(value);
		_enemyPrefab.setMaxVelocity(val);
	};
}

void EnemyPrefabPlant::_setMaxAcceleration( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned int val;
		val = ValueToUINT(value);
		_enemyPrefab.setMaxAcceleration(val);
	};
}

void EnemyPrefabPlant::_setMaxAngleVellocity( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned int val;
		val = ValueToUINT(value);
		_enemyPrefab.setMaxAngleVelocity(val);
	};
}

void EnemyPrefabPlant::_setMaxHealth( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned int val;
		val = ValueToUINT(value);
		_enemyPrefab.setMaxHealth(val);
	};
}

void EnemyPrefabPlant::_setScale( const wstring & attribute, const wstring & value )
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
		_enemyPrefab.setScale(scale);
		scale.x_scale = scale.y_scale = scale.z_scale = 0;
	} else
	{
		throw My_Exception("EnemyPrefabPlant _setScale: Missing attribute type");
	}
}

void EnemyPrefabPlant::_setRotation( const wstring & attribute, const wstring & value )
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
		_enemyPrefab.setRotation(rot);
		rot.x_rot = rot.y_rot = rot.z_rot = 0;
	} else
	{
		throw My_Exception("EnemyPrefabPlant _setRotation: Missing attribute type");
	}
}

void EnemyPrefabPlant::_setColider( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::close)
	{
		_enemyPrefab.addColider(colider);
		clearColider();
	} else
	{
		throw My_Exception("EnemyPrefabPlant _setCollider: Missing attribute type");
	}
}

void EnemyPrefabPlant::_setColiderOffset( const wstring & attribute, const wstring & value )
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

void EnemyPrefabPlant::_setColiderRadian( const wstring & attribute, const wstring & value )
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

void EnemyPrefabPlant::clearColider()
{
	colider.offset.x_pos = colider.offset.y_pos = colider.offset.z_pos = 0;
	colider.radian = 0;
}

void EnemyPrefabPlant::_setShipName( const wstring & attribute, const wstring & value )
{

}

void EnemyPrefabPlant::_doNothing( const wstring & attribute, const wstring & value )
{
	return;
}

const wchar_t * EnemyPrefabPlant::ship_name = L"ship_name";
const wchar_t * EnemyPrefabPlant::ship	= L"ship";
