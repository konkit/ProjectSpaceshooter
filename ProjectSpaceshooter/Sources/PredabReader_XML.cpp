#include "PredabReader_XML.h"
#include "Exceptions.h"

using namespace std;

#ifdef _WIN32

XML_Reader_Lite::XML_Reader_Lite(string fileName)
{
	hr = S_OK;
	pFileStream = NULL;
	pReader = NULL;
	mErrorFlag = false;
	
	//Open read-only input stream
	if (FAILED(hr = SHCreateStreamOnFile((LPCTSTR) fileName.c_str(), STGM_READ, &pFileStream)))
	{
		wprintf(L"Error creating file reader, error is %08.8lx", hr);
		HR(hr);
		throw My_Exception(string("Error creating file reader. File = ") + fileName);
	}

	if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
	{
		wprintf(L"Error creating xml reader, error is %08.8lx", hr);
		HR(hr);
	}

	if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
	{
		wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
		HR(hr);
	}

	if (FAILED(hr = pReader->SetInput(pFileStream)))
	{
		wprintf(L"Error setting input for reader, error is %08.8lx", hr);
		HR(hr);
	}
}


XML_Reader_Lite::~XML_Reader_Lite( void )
{
	if(pFileStream)
		pFileStream->Release();
	if(pReader)
		pReader->Release();
}

bool XML_Reader_Lite::CHKHR( HRESULT state )
{
	if (FAILED(hr))
	{
		mErrorFlag = true;
	}
	CleanUp();
	return mErrorFlag;
}

bool XML_Reader_Lite::HR( HRESULT state )
{
	CleanUp();
	return mErrorFlag = true;
}

bool XML_Reader_Lite::CleanUp()
{
	if(pFileStream)
		pFileStream->Release();
	if(pReader)
		pReader->Release();
	
	pFileStream = NULL;
	pReader = NULL;

	return true;
}

XML_Element XML_Reader_Lite::readXml_Element()
{
	XML_Element tmp;
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	tmp.isEmptyElement = pReader->IsEmptyElement();

	
	if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &tmp.countPrefix)))
	{
		wprintf(L"Error getting prefix, error is %08.8lx", hr);
		HR(hr);
	}
	if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
	{
		wprintf(L"Error getting local name, error is %08.8lx", hr);
		HR(hr);
	}
	tmp.prefix = pwszPrefix;
	tmp.elementName = pwszLocalName;
	return tmp;
}



XML_Element XML_Reader_Lite::readXML_Text()
{
	XML_Element tmp;
	const WCHAR* pwszValue;
	if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
	{
		wprintf(L"Error getting value, error is %08.8lx", hr);
		HR(hr);
	}
	tmp.elementName = pwszValue;
	return tmp;
}


bool XML_Reader_Lite::readToNextElement()
{
	if (mErrorFlag == true || hr != S_OK)
	{
		return false;
	}
	first_attribute = true; // This method will move XML parser to next XML node, so attribute will be read from first attribute
	hr = pReader->Read(&nodeType);
	return hr == S_OK;
}

XML_Element XML_Reader_Lite::getNextElement()
{
	XML_Element tmp;
	if (mErrorFlag == true)
	{
		throw My_Exception("Try to read from broken file");
	}
	if(S_OK == hr)
	{
		switch (nodeType)
		{
		case XmlNodeType_XmlDeclaration:
			break;
		case XmlNodeType_Element:
		case XmlNodeType_EndElement:
			tmp = readXml_Element();
			break;
		case XmlNodeType_Whitespace:
			break;
		case XmlNodeType_Text:
			tmp = readXML_Text();
			break;
		case XmlNodeType_CDATA:
		case XmlNodeType_ProcessingInstruction:
		case XmlNodeType_Comment:
		case XmlNodeType_DocumentType:
		default:
			break;
		}
		tmp.nodeType = nodeType;
		return tmp;
	}
	return XML_Element();
}

bool XML_Reader_Lite::readToNextAttribute()
{
	// This method assume that after move to next element 'first_attribute' is set to 'true'
	if (first_attribute)
	{
		hr_attr = pReader->MoveToFirstAttribute();
		first_attribute = false;
	} else
	{
		hr_attr = pReader->MoveToNextAttribute();
	}
	if (S_OK == hr_attr)
		return true;
	else
		return false;
}

XML_Attribute XML_Reader_Lite::getNextAttribute()
{
	XML_Attribute tmp;
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	const WCHAR* pwszValue;
	UINT cwchPrefix;
	

	if (S_FALSE == hr_attr)
		return tmp;
	else
	{
		if (!pReader->IsDefault())
		{
			if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
			{
				throw My_Exception("Error getting prefix, error is " + std::to_string(hr));
			}
			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
			{
				throw My_Exception("Error getting local name, error is " + std::to_string(hr));
			}
			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
			{
				throw My_Exception("Error getting value, error is "  + std::to_string(hr));
			}
		}
		tmp.attributeName = pwszLocalName;
		tmp.prefix = pwszPrefix;
		tmp.attributeValue = pwszValue;
		tmp.countPrefix = cwchPrefix;
		return tmp;
	}
}

#endif
//----------------------------------------------------------------------------------------
#ifdef __linux__
bool Linux_XML_Reader::readToNextElement()
{
	throw std::exception("The method or operation is not implemented.");
}

XML_Element Linux_XML_Reader::getNextElement()
{
	throw std::exception("The method or operation is not implemented.");
}

bool Linux_XML_Reader::readToNextAttribute()
{
	throw std::exception("The method or operation is not implemented.");
}

XML_Attribute Linux_XML_Reader::getNextAttribute()
{
	throw std::exception("The method or operation is not implemented.");
}
#endif

GameObjectReader::GameObjectReader( PrefabPlant * _gameObjectPlant, XML_Reader * _XMLReader )
{
	mGameObjectPlant = _gameObjectPlant;
	mXMLReader = _XMLReader;
}

bool GameObjectReader::hasNext()
{
	resetPrefab();
	XML_Element element;
	XML_Attribute attribute;

	// It there is no more object's to read return.
	if (!readToNextObject())
		return false;

	do 
	{
		element = mXMLReader->getNextElement();
		if (element.nodeType == XmlNodeType_Element)
		{
			mGameObjectPlant->nextElement(element.elementName);
			while (mXMLReader->readToNextAttribute())
			{
				attribute = mXMLReader->getNextAttribute();
				if (attribute.countPrefix > 0)
				{
					mGameObjectPlant->setAttribute(attribute.prefix, attribute.attributeName, attribute.attributeValue);
				} else
				{
					mGameObjectPlant->setAttribute(attribute.attributeName, attribute.attributeValue);
				}
			}
			if (element.isEmptyElement)
			{
				mGameObjectPlant->closeElement(element.elementName);
			}
		} else if (element.nodeType == XmlNodeType_EndElement)
		{
			if (element.elementName == mGameObjectPlant->getPrefabRootNode())
			{
				return false;
			} 
			mGameObjectPlant->closeElement(element.elementName);
			if (element.elementName == mGameObjectPlant->getPrefabNodeName())
			{
				mReadyPrefab = mGameObjectPlant->IsPrefabReady();
				break;
			}
		}
	} while (!mReadyPrefab && mXMLReader->readToNextElement());
	return mReadyPrefab;
}

Prefab & GameObjectReader::getNext()
{
	return mGameObjectPlant->getCreatedPrefab();
}

void GameObjectReader::resetPrefab()
{
	mGameObjectPlant->resetPrefab();
	mReadyPrefab = false;
}

bool GameObjectReader::readToNextObject()
{
	XML_Element element;
	while (mXMLReader->readToNextElement())
	{
		element = mXMLReader->getNextElement();
		if (element.nodeType == XmlNodeType_Element && element.elementName == mGameObjectPlant->getPrefabNodeName())
			{
				return true;
			} 
	}
	return false;
}

unsigned GameObjectReader::countOfPrefabs()
{
	XML_Element element;
	XML_Attribute attribute;
	while (mXMLReader->readToNextElement())
	{
		element = mXMLReader->getNextElement();
		if (element.nodeType == XmlNodeType_Element && wstring(element.elementName) == wstring(L"max_id"))
		{
			while(mXMLReader->readToNextAttribute())
			{
				attribute = mXMLReader->getNextAttribute();
				if (attribute.attributeName == wstring(L"id"))
				{
					return ValueToUINT(attribute.attributeValue);
				}
			}
			throw My_Exception("There isn't attribute 'id' in max_id node");
		} 
	}
	throw My_Exception("There isn't max_id in this file");
}

