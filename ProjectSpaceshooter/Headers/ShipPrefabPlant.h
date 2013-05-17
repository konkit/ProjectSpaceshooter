#pragma once
#include "PrefabPlant.h"

class ShipPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant, virtual public MovablePrefab_Plant
{
public:
	ShipPrefabPlant();
	~ShipPrefabPlant();

	void setText(const wstring & text );
	Prefab & getCreatedPrefab();
	void virtual resetPrefab();
	virtual const wstring getPrefabRootNode();
	virtual const wstring getPrefabNodeName();
	virtual const wstring getPrefabName();

	virtual bool setAttribute( const wstring & attribute, const wstring & value );
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );
private:
	void _setWaeponPrefab(const wstring & attribute, const wstring & value);
	void _setCameraHandler(const wstring & attribute, const wstring & value);
	void _setCameraHandlerOffset( const wstring & attribute, const wstring & value );
	void _setCameraHandlerLookAt( const wstring & attribute, const wstring & value );
	static const wstring rootEnemyPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * ship_name;
	static const wchar_t * lookAt;
	static const wchar_t * camera;
	static const wchar_t * cameraHandlers;

	ShipPrefab _shipPrefab;
	cameraHandler _cameraHandler;
};