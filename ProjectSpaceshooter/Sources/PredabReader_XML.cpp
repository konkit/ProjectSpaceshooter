#include "PredabReader_XML.h"

using namespace std;


PredabReader_XML::PredabReader_XML( string fileName, PREFAB_TYPE prefabType )
{
	hr = S_OK;
	pFileStream = NULL;
	pReader = NULL;
	mErrorFlag = false;
	readyPrefab = false;
	openReadingPrefab = false;

	//Open read-only input stream
	if (FAILED(hr = SHCreateStreamOnFile(fileName.c_str(), STGM_READ, &pFileStream)))
	{
		wprintf(L"Error creating file reader, error is %08.8lx", hr);
		HR(hr);
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
	mPrefabPlant = PrefabPlant::CreatePrefabPlantFor(prefabType);
}



Prefab & PredabReader_XML::getNext()
{
	XmlNodeType nodeType;
	if (mErrorFlag == true)
	{
		throw My_Exception("Try to read from broken file");
	}
	readyPrefab = false;
	while (S_OK == (hr = pReader->Read(&nodeType)) && !readyPrefab)
	{
		switch (nodeType)
		{
		case XmlNodeType_XmlDeclaration:
			break;
		case XmlNodeType_Element:
			readXml_Element();
			break;
		case XmlNodeType_EndElement:
			readXML_EndElement();
			break;
		case XmlNodeType_Whitespace:
			break;
		case XmlNodeType_Text:
			readXML_Text();
			break;
		case XmlNodeType_CDATA:
		case XmlNodeType_ProcessingInstruction:
		case XmlNodeType_Comment:
		case XmlNodeType_DocumentType:
		default:
				break;
		}

	}
	return mPrefabPlant->getCreatedPrefab();
}

PredabReader_XML::~PredabReader_XML( void )
{
	if(pFileStream)
		pFileStream->Release();
	if(pReader)
		pReader->Release();

	PrefabPlant::DeletePrefabPlant(mPrefabPlant);
}

bool PredabReader_XML::CHKHR( HRESULT state )
{
	if (FAILED(hr))
	{
		mErrorFlag = true;
	}
	CleanUp();
	return mErrorFlag;
}

bool PredabReader_XML::HR( HRESULT state )
{
	CleanUp();
	return mErrorFlag = true;
}

bool PredabReader_XML::CleanUp()
{
	if(pFileStream)
		pFileStream->Release();
	if(pReader)
		pReader->Release();
	
	pFileStream = NULL;
	pReader = NULL;

	return true;
}

void PredabReader_XML::readXml_Element()
{
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	UINT cwchPrefix;
	BOOL isEmptyElement = pReader->IsEmptyElement();

	
	if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
	{
		wprintf(L"Error getting prefix, error is %08.8lx", hr);
		HR(hr);
	}
	if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
	{
		wprintf(L"Error getting local name, error is %08.8lx", hr);
		HR(hr);
	}

	if (mPrefabPlant->getPrefabNodeName() == pwszLocalName && openReadingPrefab)
	{
		throw My_Exception("XML Reader: Declarate Prefab in prefab.");
	}

	if (cwchPrefix > 0)
		mPrefabPlant->nextElement(pwszPrefix, pwszLocalName);
	else
		mPrefabPlant->nextElement(pwszLocalName);

	if (FAILED(hr = readAttributes()))
	{
		wprintf(L"Error reading attributes, error is %08.8lx", hr);
		HR(hr);
	}
	if(isEmptyElement)
		mPrefabPlant->closeElement(pwszLocalName);
}

void PredabReader_XML::readXML_EndElement()
{
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	UINT cwchPrefix;
	if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
	{
		wprintf(L"Error getting prefix, error is %08.8lx", hr);
		HR(hr);
	}
	if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
	{
		wprintf(L"Error getting local name, error is %08.8lx", hr);
		HR(hr);
	}

	//Skip insignificant node
	if (mPrefabPlant->getPrefabRootNode() == pwszLocalName)
		return;
	if (mPrefabPlant->getPrefabNodeName() == pwszLocalName)
	{
		openReadingPrefab = false;
		readyPrefab = mPrefabPlant->IsPrefabReady();
	}

	if (cwchPrefix > 0)
		mPrefabPlant->closeElement(pwszPrefix, pwszLocalName);
	else
		mPrefabPlant->closeElement(pwszLocalName);
}

void PredabReader_XML::readXML_Text()
{
	const WCHAR* pwszValue;
	if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
	{
		wprintf(L"Error getting value, error is %08.8lx", hr);
		HR(hr);
	}
		mPrefabPlant->setAttribute(NULL, pwszValue);
}

HRESULT PredabReader_XML::readAttributes()
{
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	const WCHAR* pwszValue;
	HRESULT hr = pReader->MoveToFirstAttribute();

	if (S_FALSE == hr)
		return hr;
	if (S_OK != hr)
	{
		wprintf(L"Error moving to first attribute, error is %08.8lx", hr);
		return hr;
	}
	else
	{
		while (TRUE)
		{
			if (!pReader->IsDefault())
			{
				UINT cwchPrefix;
				if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
				{
					wprintf(L"Error getting prefix, error is %08.8lx", hr);
					return hr;
				}
				if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
				{
					wprintf(L"Error getting local name, error is %08.8lx", hr);
					return hr;
				}
				if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
				{
					wprintf(L"Error getting value, error is %08.8lx", hr);
					return hr;
				}
				if (cwchPrefix > 0)
					mPrefabPlant->setAttribute(pwszPrefix, pwszLocalName, pwszValue);
				else
					mPrefabPlant->setAttribute(pwszLocalName, pwszValue);
			}

			if (S_OK != pReader->MoveToNextAttribute())
				break;
		}
	}
	return hr;
}

bool PredabReader_XML::hasNext()
{
	if (mErrorFlag || FAILED(hr))
	{
		return false;
	}
	return readToNextPrefab();
}

bool PredabReader_XML::readToNextPrefab()
{
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	UINT cwchPrefix;
	BOOL isEmptyElement = pReader->IsEmptyElement();
	XmlNodeType nodeType;
	wstring tmp;
	if (mErrorFlag == true)
	{
		return false;
	}
	resetPrefab();

	while (S_OK == (hr = pReader->Read(&nodeType)) && !readyPrefab)
	{
		switch (nodeType)
		{
		case XmlNodeType_XmlDeclaration:
			break;
		case XmlNodeType_Element:

			if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
			{
				wprintf(L"Error getting prefix, error is %08.8lx", hr);
				HR(hr);
				return false;
			}
			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
			{
				wprintf(L"Error getting local name, error is %08.8lx", hr);
				HR(hr);
				return false;
			}
			tmp = mPrefabPlant->getPrefabRootNode();
			//Skip insignificant nodes
			if (mPrefabPlant->getPrefabRootNode() == pwszLocalName)
				break;
			if(!wcscmp(L"max_id",pwszLocalName))
				break;

			if (mPrefabPlant->getPrefabNodeName() != pwszLocalName)
				break;
			
			if (mPrefabPlant->getPrefabNodeName() == pwszLocalName && openReadingPrefab)
			{
				throw My_Exception("XML Reader: Declarate Prefab in prefab.");
			} else
			{
				openReadingPrefab = true;
			}

			if (cwchPrefix > 0)
				mPrefabPlant->nextElement(pwszPrefix, pwszLocalName);
			else
				mPrefabPlant->nextElement(pwszLocalName);

			if (FAILED(hr = readAttributes()))
			{
				wprintf(L"Error reading attributes, error is %08.8lx", hr);
				HR(hr);
			}
			if(isEmptyElement)
				throw My_Exception("XML Reader: There is empty prefab in file, stopped parsing");

			return SUCCEEDED(hr);

		default:
			break;
		}

	}
		return false;
}

void PredabReader_XML::resetPrefab()
{
	mPrefabPlant->resetPrefab();
	readyPrefab = false;
}
