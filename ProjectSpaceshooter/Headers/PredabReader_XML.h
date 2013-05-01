#pragma once

#include <ole2.h>
#include <xmllite.h>
#include <stdio.h>
#include <shlwapi.h>
#include <string>
#include "Prefabs.h"
#include "PrefabPlant.h"
#include <string>

// If there isn't used XML Lite, use this XmlNodeType in your XML Reader
#ifndef __XmlLite_LIBRARY_DEFINED__
typedef 
	enum XmlNodeType
{
	XmlNodeType_None	= 0,
	XmlNodeType_Element	= 1,
	XmlNodeType_Attribute	= 2,
	XmlNodeType_Text	= 3,
	XmlNodeType_CDATA	= 4,
	XmlNodeType_ProcessingInstruction	= 7,
	XmlNodeType_Comment	= 8,
	XmlNodeType_DocumentType	= 10,
	XmlNodeType_Whitespace	= 13,
	XmlNodeType_EndElement	= 15,
	XmlNodeType_XmlDeclaration	= 17,
	_XmlNodeType_Last	= 17
} 	XmlNodeType;
#endif // XmlNodeType

struct XML_Element
{
	wstring pwszPrefix;
	wstring pwszLocalName;
	UINT cwchPrefix;
	BOOL isEmptyElement;
	XmlNodeType nodeType;
//	XML_Element() : pwszPrefix(0), pwszLocalName(0), cwchPrefix(0), isEmptyElement(false){}
};
struct XML_Attribute
{
	UINT cwchPrefix;
	wstring pwszPrefix;
	wstring pwszLocalName;
	wstring pwszValue;
};




/**
 * Class with open XML document and read prefab description from indicated file.
 * To use this class set file name and expected prefab type in class constructor,
 * next use: hasNext and getNext methods to read whole file
 * hasNext method check if there is any prefab to read in indicated file
 * getNext method return read prefab, but you must down cast returned prefab.
 * @author Zyga
 */


class XML_Reader
{
public:
	virtual bool hasNextElement() = 0;
	virtual XML_Element getNextElement() = 0;
	virtual bool hasNextAttribute() = 0;
	virtual XML_Attribute getNextAttribute() = 0;
};

class XML_Reader_Lite : public XML_Reader
{
public:
	XML_Reader_Lite(string fileName);
	~XML_Reader_Lite(void);

	virtual bool hasNextElement();
	virtual XML_Element getNextElement();
	virtual bool hasNextAttribute();
	virtual XML_Attribute getNextAttribute();
private:
	XML_Element readXML_Text();
	XML_Element readXML_EndElement();
	XML_Element readXml_Element();
//	HRESULT readAttributes(XML_Attribute & attribut);
	bool CHKHR(HRESULT state);
	bool HR(HRESULT state);
	bool CleanUp();
	HRESULT hr;
	IStream *pFileStream;
	IXmlReader *pReader;
	string mFileName;
	bool mErrorFlag;
	XmlNodeType nodeType;
	HRESULT STDMETHODCALLTYPE hr_attr;
	bool first_attribute;
};

class GameObjectReader
{
public:
	GameObjectReader(PrefabPlant * _gameObjectPlant, XML_Reader * _XMLReader);
	bool hasNext();
	Prefab & getNext();
	void resetPrefab();
private:
	bool mReadyPrefab;
	PrefabPlant * mGameObjectPlant;
	XML_Reader * mXMLReader;
};