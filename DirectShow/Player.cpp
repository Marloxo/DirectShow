#include "stdafx.h"
#include <dshow.h>

//Define my function
int Stop();
void ThrowIfError(HRESULT hr);
long Get_Event();

// TODO: Initialize Global Var
IGraphBuilder *pGraph = NULL;
IMediaControl *pControl = NULL;
IMediaEventEx   *pEventEx = NULL;

void Play(HWND hwnd)
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
		hr = pGraph->RenderFile(L"C:\\video.avi", NULL);
		ThrowIfError(hr);

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
		pEventEx->Release();
		pEventEx = NULL;
	}

	CoUninitialize();
	return 0;
}

long Get_Event()
{
	long evCode;
	LONG_PTR param1, param2;
	HRESULT hr = pEventEx->GetEvent(&evCode, &param1, &param2, 250);

	if (SUCCEEDED(hr))
	{
		hr = pEventEx->FreeEventParams(evCode, param1, param2);
		ThrowIfError(hr);
	}
	return evCode;
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