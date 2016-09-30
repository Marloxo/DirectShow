#pragma once
#include <dshow.h>


#define WM_GRAPHNOTIFY WM_APP +1 //private message.


void Play(HWND hwnd, TCHAR* FileName);
int Stop();
void Pause();
bool GetCompletionEvent();
void ThrowIfError(HRESULT hr);
TCHAR* ShowDialog();
