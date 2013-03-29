#include "ResoursceLoader.h"
#include <ole2.h>
#include <xmllite.h>
#include <stdio.h>
#include <shlwapi.h>

#pragma warning(disable : 4127)  // conditional expression is constant
#define CHKHR(stmt)             do { hr = (stmt); if (FAILED(hr)) goto CleanUp; } while(0)
#define HR(stmt)                do { hr = (stmt); goto CleanUp; } while(0)
#define SAFE_RELEASE(I)         do { if (I){ I->Release(); } I = NULL; } while(0)

using namespace std;
ResoursceLoader::~ResoursceLoader()
{

}

ResoursceLoader::ResoursceLoader()
{

}

void ResoursceLoader::loadPrefabs( GameData & _gameData )
{
	//loadEnemyPrefabs(_gameData);
}

//void ResoursceLoader::loadEnemyPrefabs( GameData & _gameData )
//{
//	HRESULT hr = S_OK;
//	IStream *pFileStream = NULL;
//	IXmlReader *pReader = NULL;
//	XmlNodeType nodeType;
//	const WCHAR* pwszPrefix;
//	const WCHAR* pwszLocalName;
//	const WCHAR* pwszValue;
//	UINT cwchPrefix;
//
//	//Open read-only input stream
//	if (FAILED(hr = SHCreateStreamOnFile("EnemyPrefabls", STGM_READ, &pFileStream)))
//	{
//		wprintf(L"Error creating file reader, error is %08.8lx", hr);
//		HR(hr);
//	}
//
//	if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
//	{
//		wprintf(L"Error creating xml reader, error is %08.8lx", hr);
//		HR(hr);
//	}
//
//	if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
//	{
//		wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
//		HR(hr);
//	}
//
//	if (FAILED(hr = pReader->SetInput(pFileStream)))
//	{
//		wprintf(L"Error setting input for reader, error is %08.8lx", hr);
//		HR(hr);
//	}
//
//	//read until there are no more nodes
//	while (S_OK == (hr = pReader->Read(&nodeType)))
//	{
//		switch (nodeType)
//		{
//		case XmlNodeType_XmlDeclaration:
//			wprintf(L"XmlDeclaration\n");
//			//if (FAILED(hr = WriteAttributes(pReader)))
//			//{
//			//	wprintf(L"Error writing attributes, error is %08.8lx", hr);
//			//	HR(hr);
//			//}
//			break;
//		case XmlNodeType_Element:
//			if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
//			{
//				wprintf(L"Error getting prefix, error is %08.8lx", hr);
//				HR(hr);
//			}
//			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
//			{
//				wprintf(L"Error getting local name, error is %08.8lx", hr);
//				HR(hr);
//			}
//			if (cwchPrefix > 0)
//				wprintf(L"Element: %s:%s\n", pwszPrefix, pwszLocalName);
//			else
//				wprintf(L"Element: %s\n", pwszLocalName);
//
//			//if (FAILED(hr = WriteAttributes(pReader)))
//			//{
//			//	wprintf(L"Error writing attributes, error is %08.8lx", hr);
//			//	HR(hr);
//			//}
//
//			if (pReader->IsEmptyElement() )
//				wprintf(L" (empty)");
//			break;
//		case XmlNodeType_EndElement:
//			if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
//			{
//				wprintf(L"Error getting prefix, error is %08.8lx", hr);
//				HR(hr);
//			}
//			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
//			{
//				wprintf(L"Error getting local name, error is %08.8lx", hr);
//				HR(hr);
//			}
//			if (cwchPrefix > 0)
//				wprintf(L"End Element: %s:%s\n", pwszPrefix, pwszLocalName);
//			else
//				wprintf(L"End Element: %s\n", pwszLocalName);
//			break;
//		case XmlNodeType_Text:
//		case XmlNodeType_Whitespace:
//			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
//			{
//				wprintf(L"Error getting value, error is %08.8lx", hr);
//				HR(hr);
//			}
//			wprintf(L"Text: >%s<\n", pwszValue);
//			break;
//		case XmlNodeType_CDATA:
//			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
//			{
//				wprintf(L"Error getting value, error is %08.8lx", hr);
//				HR(hr);
//			}
//			wprintf(L"CDATA: %s\n", pwszValue);
//			break;
//		case XmlNodeType_ProcessingInstruction:
//			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
//			{
//				wprintf(L"Error getting name, error is %08.8lx", hr);
//				HR(hr);
//			}
//			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
//			{
//				wprintf(L"Error getting value, error is %08.8lx", hr);
//				HR(hr);
//			}
//			wprintf(L"Processing Instruction name:%s value:%s\n", pwszLocalName, pwszValue);
//			break;
//		case XmlNodeType_Comment:
//			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
//			{
//				wprintf(L"Error getting value, error is %08.8lx", hr);
//				HR(hr);
//			}
//			wprintf(L"Comment: %s\n", pwszValue);
//			break;
//		case XmlNodeType_DocumentType:
//			wprintf(L"DOCTYPE is not printed\n");
//			break;
//		}
//	}
//CleanUp:
//	SAFE_RELEASE(pFileStream);
//	SAFE_RELEASE(pReader);
//}
//
