#pragma once
#include <dshow.h>



#define WM_GRAPHNOTIFY WM_APP +1 //private message.



void Play(HWND hwnd);
int Stop();
long Get_Event();
void ThrowIfError(HRESULT hr);
