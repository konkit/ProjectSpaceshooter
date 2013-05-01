#include "PredabReader_XML.h"
#include "Exceptions.h"

using namespace std;


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

	
	if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &tmp.cwchPrefix)))
	{
		wprintf(L"Error getting prefix, error is %08.8lx", hr);
		HR(hr);
	}
	if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
	{
		wprintf(L"Error getting local name, error is %08.8lx", hr);
		HR(hr);
	}
	tmp.pwszPrefix = pwszPrefix;
	tmp.pwszLocalName = pwszLocalName;
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
	tmp.pwszLocalName = pwszValue;
	return tmp;
}


bool XML_Reader_Lite::hasNextElement()
{
	if (mErrorFlag || FAILED(hr))
	{
		return false;
	}
	first_attribute = true; // It open reading next element, so next will be readed first attribute
	return SUCCEEDED(hr = pReader->Read(&nodeType));
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

bool XML_Reader_Lite::hasNextAttribute()
{
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
		tmp.pwszLocalName = pwszLocalName;
		tmp.pwszPrefix = pwszPrefix;
		tmp.pwszValue = pwszValue;
		tmp.cwchPrefix = cwchPrefix;
		return tmp;
	}
}


//----------------------------------------------------------------------------------------


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
	while (!mReadyPrefab && mXMLReader->hasNextElement())
	{
		element = mXMLReader->getNextElement();
		if (element.nodeType == XmlNodeType_Element)
		{
			mGameObjectPlant->nextElement(element.pwszLocalName);
			while (mXMLReader->hasNextAttribute())
			{
				attribute = mXMLReader->getNextAttribute();
				if (attribute.cwchPrefix > 0)
				{
					mGameObjectPlant->setAttribute(attribute.pwszPrefix, attribute.pwszLocalName, attribute.pwszValue);
				} else
				{
					mGameObjectPlant->setAttribute(attribute.pwszLocalName, attribute.pwszValue);
				}
			}
			if (element.isEmptyElement)
			{
				mGameObjectPlant->closeElement(element.pwszLocalName);
			}
		} else if (element.nodeType == XmlNodeType_EndElement)
		{
			if (element.pwszLocalName == mGameObjectPlant->getPrefabRootNode())
			{
				return false;
			} 
			mGameObjectPlant->closeElement(element.pwszLocalName);
			if (element.pwszLocalName == mGameObjectPlant->getPrefabNodeName())
			{
				mReadyPrefab = mGameObjectPlant->IsPrefabReady();
				break;
			}
		}

	}
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
