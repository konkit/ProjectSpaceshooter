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
class PredabReader_XML
{
public:
	PredabReader_XML(string fileName, PREFAB_TYPE prefabType);
	~PredabReader_XML(void);
	bool hasNext();
	Prefab * getNext();

private:
	bool readToNextPrefab();

	void resetPrefab();

	void readXML_Text();
	void readXML_EndElement();
	void readXml_Element();
	HRESULT readAttributes();
	bool openReadingPrefab;
	bool readyPrefab;
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

