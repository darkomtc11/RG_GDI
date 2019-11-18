
// Vezba3.h : main header file for the Vezba3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVezba3App:
// See Vezba3.cpp for the implementation of this class
//

class CVezba3App : public CWinApp
{
public:
	CVezba3App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVezba3App theApp;
