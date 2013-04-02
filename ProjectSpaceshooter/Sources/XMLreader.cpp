#include "XMLreader.h"

using namespace std;


XMLreader::XMLreader( string fileName, PREFAB_TYPE prefabType )
	: hr(S_OK), pFileStream(NULL), pReader(NULL), mErrorFlag(false)
{
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

Prefab XMLreader::getNext()
{
	XmlNodeType nodeType;
	//const WCHAR* pwszValue;
	//const WCHAR* pwszPrefix;
	//const WCHAR* pwszLocalName;
	//UINT cwchPrefix;
	while (S_OK == (hr = pReader->Read(&nodeType)))
	{
		switch (nodeType)
		{
		case XmlNodeType_XmlDeclaration:
			break;
		case XmlNodeType_Element:
			readXmlElement();
			break;
		case XmlNodeType_EndElement:
			readXMLEndElement();
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
}

XMLreader::~XMLreader( void )
{
	if(pFileStream)
		pFileStream->Release();
	if(pReader)
		pReader->Release();
}

bool XMLreader::CHKHR( HRESULT state )
{
	if (FAILED(hr))
	{
		mErrorFlag = true;
	}
	CleanUp();
	return mErrorFlag;
}

bool XMLreader::HR( HRESULT state )
{
	CleanUp();
	return mErrorFlag = true;
}

bool XMLreader::CleanUp()
{
	if(pFileStream)
		pFileStream->Release();
	if(pReader)
		pReader->Release();
	
	pFileStream = NULL;
	pReader = NULL;

	return true;
}

void XMLreader::readXmlElement()
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
	if (cwchPrefix > 0)
		mPrefabPlant->nextElement(pwszLocalName, pwszPrefix);
	else
		mPrefabPlant->nextElement(pwszLocalName);
	if (FAILED(hr = readAttributes()))
	{
		wprintf(L"Error writing attributes, error is %08.8lx", hr);
		HR(hr);
	}
	if (pReader->IsEmptyElement() )
		wprintf(L" (empty)");
}

void XMLreader::readXMLEndElement()
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
	if (cwchPrefix > 0)
		mPrefabPlant->nextElement(pwszLocalName, pwszPrefix);
	else
		mPrefabPlant->nextElement(pwszLocalName);
}

void XMLreader::readXML_Text()
{
	const WCHAR* pwszValue;
	if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
	{
		wprintf(L"Error getting value, error is %08.8lx", hr);
		HR(hr);
	}
		mPrefabPlant->setAttribute(NULL, pwszValue);
}
