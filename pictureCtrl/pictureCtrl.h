
// pictureCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CpictureCtrlApp: 
// �йش����ʵ�֣������ pictureCtrl.cpp
//

class CpictureCtrlApp : public CWinApp
{
public:
	CpictureCtrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CpictureCtrlApp theApp;