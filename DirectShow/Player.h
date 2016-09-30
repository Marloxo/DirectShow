#pragma once
#include <dshow.h>

int Play();
int Stop();
long Get_Event();
void ThrowIfError(HRESULT hr);
