#include "ShipPrefabPlant.h"


const wstring ShipPrefabPlant::rootEnemyPrefabsNode(L"ship_prefabs");
const wstring ShipPrefabPlant::prefabName(L"ship");

const wchar_t * ShipPrefabPlant::ship_name = L"ship_name";
const wchar_t * ShipPrefabPlant::cameraHandlers = L"camera_handlers";
const wchar_t * ShipPrefabPlant::camera = L"camera";
const wchar_t * ShipPrefabPlant::lookAt = L"lookAt";


ShipPrefabPlant::ShipPrefabPlant()
{
	PrefabPlant::setPrefab(static_cast<Prefab*>(&_shipPrefab));
	PrefabWithCollider_Plant::setPrefab(static_cast<PrefabWithCollider*>(&_shipPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&_shipPrefab)); 
	MovablePrefab_Plant::setPrefab(static_cast<MovablePrefab*>(&_shipPrefab));
}

ShipPrefabPlant::~ShipPrefabPlant()
{

}

void ShipPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

void ShipPrefabPlant::resetPrefab()
{
	_shipPrefab.resetPrefab();
	prefabReady = false;
	_cameraHandler.resetCameraHandler();	
}

const wstring ShipPrefabPlant::getPrefabRootNode()
{
	return wstring(rootEnemyPrefabsNode);
}

const wstring ShipPrefabPlant::getPrefabNodeName()
{
	return wstring(prefabName);
}


Prefab & ShipPrefabPlant::getCreatedPrefab()
{
	return static_cast<Prefab &>(_shipPrefab);
}

void ShipPrefabPlant::_setWaeponPrefab( const wstring & attribute, const wstring & value )
{
	if (attribute == id)
	{
		unsigned int id;
		id = ValueToUINT(value);
		_shipPrefab.setWeaponPrefabID(id);
	};
}




const wstring ShipPrefabPlant::getPrefabName()
{
	return wstring(ship_name);
}

bool ShipPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	wstring stack_top = elements.top(); 
	wstring stack_prev(L"");
	if (elements.size() > 1)
	{
		//There is required to know value which is below top of stack
		elements.pop();
		stack_prev = elements.top();
		elements.push(stack_top);
	}


	if (PrefabPlant::setAttribute(attribute, value))
	{
		return true;
	} else if(MovablePrefab_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (PrefabWithMesh_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (PrefabWithCollider_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (stack_top == PrefabPlant::standard_waepon)
	{
		_setWaeponPrefab(attribute, value);
	} else if (stack_prev == cameraHandlers)
	{
		if (stack_top == camera)
		{
			_setCameraHandler(attribute, value);
		} else
			return false;
	} else if (stack_prev == camera)
	{
		if(stack_top == offset)
		{
			_setCameraHandlerOffset(attribute, value);
		}
		else if (stack_top == lookAt)
		{
			_setCameraHandlerLookAt(attribute, value);
		}
	}  else
	{
		return false;
	}

}

bool ShipPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute, value);
}

void ShipPrefabPlant::_setCameraHandler( const wstring & attribute, const wstring & value )
{
	if (attribute == name)
	{
		_cameraHandler.name = string(value.begin(), value.end());
	} else if (attribute == closeNode)
	{
		_shipPrefab.addCameraHandler(_cameraHandler);
	} else
		throw ParserException(L"Incorrect attribute " + attribute);
}
void ShipPrefabPlant::_setCameraHandlerOffset( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::x_pos)
	{
		_cameraHandler.offset.x= ValueToDouble(value);
	} else if (attribute == PrefabPlant::y_pos)
	{
		_cameraHandler.offset.y = ValueToDouble(value);
	} else if (attribute == PrefabPlant::z_pos)
	{
		_cameraHandler.offset.z = ValueToDouble(value);
	} else if (attribute == PrefabPlant::closeNode)
	{
		return;
	}	else
	{
		throw ParserException(L"Incorrect attribute = " + attribute + L" in _setCameraHandlerOffset");
	}
}

void ShipPrefabPlant::_setCameraHandlerLookAt( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::x_pos)
	{
		_cameraHandler.lookAt.x= ValueToDouble(value);
	} else if (attribute == PrefabPlant::y_pos)
	{
		_cameraHandler.lookAt.y = ValueToDouble(value);
	} else if (attribute == PrefabPlant::z_pos)
	{
		_cameraHandler.lookAt.z = ValueToDouble(value);
	} else if (attribute == PrefabPlant::closeNode)
	{
		return;
	}	else
	{
		throw ParserException(L"Incorrect attribute = " + attribute + L" in _setCameraHandlerOffset");
	}
}




