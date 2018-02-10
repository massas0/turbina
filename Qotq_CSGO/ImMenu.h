#pragma once
#include "SDK.h"

namespace ImMenu {
	void GuiInit(HWND, IDirect3DDevice9*);
	void Open();
	void Draw();
	extern bool D3Init;
	extern ImFont* Im_Font;
}