
// 硬编码超级列表框.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// C硬编码超级列表框App:
// 有关此类的实现，请参阅 硬编码超级列表框.cpp
//

class C硬编码超级列表框App : public CWinApp
{
public:
	C硬编码超级列表框App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C硬编码超级列表框App theApp;
//删除空字符串
void RemoveSpaces(CString& str);