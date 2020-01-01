
// MFCTest.h : main header file for the MFCTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCTestApp:
// See MFCTest.cpp for the implementation of this class
//

class CMFCTestApp : public CWinApp
{
public:
	CMFCTestApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCTestApp theApp;
