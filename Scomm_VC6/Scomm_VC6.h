// Scomm_VC6.h : main header file for the SCOMM_VC6 application
//

#if !defined(AFX_SCOMM_VC6_H__7E389472_3DFC_4723_B269_C7208D7AB345__INCLUDED_)
#define AFX_SCOMM_VC6_H__7E389472_3DFC_4723_B269_C7208D7AB345__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScomm_VC6App:
// See Scomm_VC6.cpp for the implementation of this class
//

class CScomm_VC6App : public CWinApp
{
public:
	CScomm_VC6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScomm_VC6App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScomm_VC6App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOMM_VC6_H__7E389472_3DFC_4723_B269_C7208D7AB345__INCLUDED_)
