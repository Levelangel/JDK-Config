
// JDK Config.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#pragma comment (lib,"Version.lib")
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

// CJDKConfigApp: 
// �йش����ʵ�֣������ JDK Config.cpp
//

class CJDKConfigApp : public CWinApp
{
public:
	CJDKConfigApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJDKConfigApp theApp;