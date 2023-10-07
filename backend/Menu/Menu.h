#pragma once

#include <Windows.h>
#include <string>
#include <memory>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "../Framework/MenuFramework.h"
#include <unordered_map>

class CMenu
{
public:
	CMenu( );
	static CMenu& get( ) {
		static CMenu instance;
		return instance;
	}

public:
	void Initialize();
	void Draw();

	bool IsMenuOpened();
	void SetMenuOpened(bool v);

	D3DCOLOR GetMenuColor();
	
	int Menu_key = VK_INSERT;
private:
	bool m_bInitialized;
	bool m_bIsOpened;
	
	int m_nCurrentTab;
	int m_nCurrentLegitTab;
};