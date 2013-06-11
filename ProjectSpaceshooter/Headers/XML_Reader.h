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

/**  
 * This is structure which describe XML node
 * @author Zyga
 */
struct XML_Element
{
	wstring prefix;
	wstring elementName;
	UINT countPrefix;
	// If element look like <name />  it is empty element so have only attribute
	BOOL isEmptyElement;
	XmlNodeType nodeType;
	XML_Element() : countPrefix(0), isEmptyElement(false), nodeType(XmlNodeType_None){}
};

/**
 * This is a structure which describe XML attribute name  
 * @author Zyga
 */
struct XML_Attribute
{
	UINT countPrefix;
	wstring prefix;
	wstring attributeName;
	wstring attributeValue;
};

/** 
 * This is an interface which you can use to connect your own XML reader.  
 * Your XML reader must implement this interface to make GameObjectReader work.
 * @author Zyga
 */
class XML_Reader
{
public:

	/** 
	* Method move XML Parser to next node, and check if there is more nodes
	* @return if there is any node to read return true
	* @author Zyga
	*/
	virtual bool readToNextElement() = 0;

	/**
	* Method returned filled structure describing actual read XML node 
	* @return filled structure which describe actual XML Node
	* @author Zyga
	*/
	virtual XML_Element getNextElement() = 0;
	
	/**
	* Method move XML parser to next attribute associated to actual XML node
	* @return If there are any attribute to read return true
	* @author Zyga
	*/
	virtual bool readToNextAttribute() = 0;

	/** 
	* Read attribute from XML file and parse it into attribute structure
	* @return filled structure describing attribute associated to actual XML node
	* @author Zyga
	*/
	virtual XML_Attribute getNextAttribute() = 0;
};


#ifdef _WIN32

/**
 * It is XML Reader which use Xmllite included into windows
 * @author Zyga
 */
class XML_Reader_Lite : public XML_Reader
{
public:

	/**
	* Open XML file to read.
	* @param string fileName name and path to XML file.
	* @author Zyga
	*/
	XML_Reader_Lite(string fileName);
	~XML_Reader_Lite(void);

	virtual bool readToNextElement();
	virtual XML_Element getNextElement();
	virtual bool readToNextAttribute();
	virtual XML_Attribute getNextAttribute();
private:
	XML_Element readXML_Text();
	XML_Element readXML_EndElement();
	XML_Element readXml_Element();
	bool CHKHR(HRESULT state);
	bool HR(HRESULT state);
	bool CleanUp();
	HRESULT hr;
	IStream *pFileStream;
	IXmlReader *pReader;
	string mFileName;
	bool mErrorFlag;
	XmlNodeType nodeType;
	HRESULT hr_attr;
	bool first_attribute;
};
#endif

#ifdef __linux__

/**
 * If you will use game under Linux system rename and implement this class
 * @author 
 */
class Linux_XML_Reader : public XML_Reader
{
	virtual bool readToNextElement();
	virtual XML_Element getNextElement();
	virtual bool readToNextAttribute();
	virtual XML_Attribute getNextAttribute();

};
#endif

/**
 * This is class used to read GameObject from XML file. This use external gameObjectPlant and XML Reader
 * Class don't allocate any memory and don't destroy gameObjectPlant and XMLReader.
 * gameObjectPlant and XML reader must be given when class is created, and must be free by caller;
 * hasNext method check if there is any prefab to read in indicated file
 * getNext method return read prefab, but you must down cast returned prefab.
 * @author Zyga
 */
class GameObjectReader
{
public:
	/**
	* Class constructor need created gameObjectPlant which take data read from XML file and parse it into gameObject properties,
	* and XML_Reader to read from XML files
	* Objects given through params must be construct and destroy by caller 
	* @param PrefabPlant * _gameObjectPlant
	* @param XML_Reader * _XMLReader
	* @author Zyga
	*/
	GameObjectReader(PrefabPlant * _gameObjectPlant, XML_Reader * _XMLReader);
	
	/**
	* This method try to construct gameObject base on data in XML file, if it is successful return true
	* @author Zyga
	* @return if read gameObject is correct return true 
	*/
	bool hasNext();

	/**
	* Get read gameObject.
	* @return Return gameObject which is read from file
	* @author Zyga
	*/	
	Prefab & getNext();

	/**
	 * @return Numbers of prefabs which is stored in file. It is saved as first line after root node in XML
	 * @author Zyga
	 */
	unsigned countOfPrefabs();
private:
	void resetPrefab();
	bool readToNextObject();
	bool mReadyPrefab;
	PrefabPlant * mGameObjectPlant;
	XML_Reader * mXMLReader;
};