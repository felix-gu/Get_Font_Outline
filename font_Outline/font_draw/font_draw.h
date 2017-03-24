// font_draw.h : main header file for the FONT_DRAW application
//

#if !defined(AFX_FONT_DRAW_H__F38486D5_ACA8_40DD_BE9E_C58307AECA6F__INCLUDED_)
#define AFX_FONT_DRAW_H__F38486D5_ACA8_40DD_BE9E_C58307AECA6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFont_drawApp:
// See font_draw.cpp for the implementation of this class
//

class CFont_drawApp : public CWinApp
{
public:
	CFont_drawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFont_drawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFont_drawApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONT_DRAW_H__F38486D5_ACA8_40DD_BE9E_C58307AECA6F__INCLUDED_)
