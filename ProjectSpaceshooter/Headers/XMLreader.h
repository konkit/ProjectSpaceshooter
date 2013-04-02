#pragma once

#include <ole2.h>
#include <xmllite.h>
#include <stdio.h>
#include <shlwapi.h>
#include <string>
#include "Prefabs.h"
#include "PrefabPlant.h"


/**
 * Class with open XML document and read prefab description from indicated file.
 * To use this class set file name and expected prefab type in class constructor,
 * next use: hasNext and getNext methods to read whole file
 * hasNext method check if there is any prefab to read in indicated file
 * getNext method return read prefab, but you must down cast returned prefab.
 * @author Zyga
 */
class XMLreader
{
public:
	XMLreader(string fileName, PREFAB_TYPE prefabType);
	~XMLreader(void);
	bool hasNext();
	Prefab getNext();

	void readXML_Text();

	void readXMLEndElement();

	void readXmlElement();

private:
	HRESULT readAttributes();
	bool CHKHR(HRESULT state);
	bool HR(HRESULT state);
	bool CleanUp();
	HRESULT hr;
	IStream *pFileStream;
	IXmlReader *pReader;
	PrefabPlant * mPrefabPlant;
	string mFileName;
	bool mErrorFlag;
};

