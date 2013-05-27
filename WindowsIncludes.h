#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <D3D11.h>

#define SAFE_RELEASE( p ) if( (p) ) { (p)->Release(); (p) = NULL; }
