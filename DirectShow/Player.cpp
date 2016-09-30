#include "stdafx.h"
#include <dshow.h>

//This is needed for virtually 
//everything in BrowseFolder.
#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>
#include <string>
#include <iostream>
using namespace std;


//Define my function
int Stop();
void ThrowIfError(HRESULT hr);
bool GetCompletionEvent();

// TODO: Initialize Global Var
IGraphBuilder *pGraph = NULL;
IMediaControl *pControl = NULL;
IMediaEventEx   *pEventEx = NULL;

void Play(HWND hwnd, TCHAR* FileName)
{
	HRESULT hr;
	try
	{
		if (pGraph)
			return;

		// Initialize the COM library.
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			Stop();
			MessageBox(0, TEXT("ERROR !"), TEXT("ERROR - Could not initialize COM library"), 0);
			return;
		}

		// Create the filter graph manager and query for interfaces.
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void **)&pGraph);
		if (FAILED(hr))
		{
			Stop();
			MessageBox(0, TEXT("ERROR !"), TEXT("ERROR - Could not create the Filter Graph Manager."), 0);
			return;
		}

		hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
		hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEventEx);

		// Build the graph. IMPORTANT: Change this string to a file on your system.
		hr = pGraph->RenderFile(FileName, NULL);
		//ThrowIfError(hr);
		if (FAILED(hr))
			MessageBox(0, TEXT("ERROR - Could not Find the request file to play."), TEXT("ERROR !"), 0);


		if (SUCCEEDED(hr))
		{	// Run the graph.
			hr = pControl->Run();
			ThrowIfError(hr);
			// Wait for completion.
			// Note: Do not use INFINITE in a real application, because it
			// can block indefinitely.
			/*long evCode;
			pEventEx->WaitForCompletion(INFINITE, &evCode);*/
		}

		//Get notification when something happened
		pEventEx->SetNotifyWindow((OAHWND)hwnd, WM_GRAPHNOTIFY, 0);
	}
	catch (TCHAR szErr)
	{
		ThrowIfError(hr);
	}
}

int Stop()
{
	if (pGraph)
	{
		pGraph->Release();
		pGraph = NULL;
	}

	if (pControl)
	{
		pControl->Release();
		pControl = NULL;
	}

	if (pEventEx)
	{
		pEventEx->SetNotifyWindow((OAHWND)NULL, WM_GRAPHNOTIFY, 0);
		pEventEx->Release();
		pEventEx = NULL;
	}

	CoUninitialize();
	return 0;
}

bool GetCompletionEvent()
{
	if (pEventEx == NULL)
		return false;

	while (true)
	{
		long evCode;
		LONG_PTR param1, param2;
		HRESULT hr = pEventEx->GetEvent(&evCode, &param1, &param2, 250);

		if (FAILED(hr))
			return false;

		hr = pEventEx->FreeEventParams(evCode, param1, param2);
		ThrowIfError(hr);

		if (evCode == EC_COMPLETE)
			return true;
	}
}

//Show Error for HRESULT
void ThrowIfError(HRESULT hr)
{
	if (FAILED(hr))
	{
		TCHAR szErr[MAX_ERROR_TEXT_LEN];
		DWORD res = AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
		if (res == 0)
		{
			StringCchPrintf(szErr, MAX_ERROR_TEXT_LEN, TEXT("Unknown Error: 0x%2x"), hr);
		}
		MessageBox(0, szErr, TEXT("Basically, without saying too much, you're screwed. Royally and totally."), MB_OK | MB_ICONERROR);
		//throw szErr;
	}
}



TCHAR* ShowDialog()
{
	//check if there is file already playing
	if (pGraph)
	{
		MessageBox(0, TEXT("Stop Played File First!!"), _T("Info"),
			MB_OK | MB_ICONINFORMATION);
		return NULL;
	}

	TCHAR*DefaultExtension = 0;
	TCHAR*FileName = new TCHAR[MAX_PATH];;
	TCHAR*Filter = 0;
	int FilterIndex = 0;
	int Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	TCHAR*InitialDir = 0;
	HWND Owner = 0;
	TCHAR*Title = 0;


	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Owner;
	ofn.lpstrDefExt = DefaultExtension;
	ofn.lpstrFile = FileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = Filter;
	ofn.nFilterIndex = FilterIndex;
	ofn.lpstrInitialDir = InitialDir;
	ofn.lpstrTitle = Title;
	ofn.Flags = Flags;

	GetOpenFileName(&ofn);

	if (_tcslen(FileName) == 0)
	{
		MessageBox(0, TEXT("NO File Selected!!"), _T("Info"),
			MB_OK | MB_ICONINFORMATION);
		return NULL;
	}

	return FileName;
}