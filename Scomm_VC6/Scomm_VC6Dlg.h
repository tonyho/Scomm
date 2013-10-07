// Scomm_VC6Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
#include "ntgraph.h"
#include "afxwin.h"
//}}AFX_INCLUDES

#if !defined(AFX_SCOMM_VC6DLG_H__83053864_9F6F_483E_9A8B_7A5A987583CC__INCLUDED_)
#define AFX_SCOMM_VC6DLG_H__83053864_9F6F_483E_9A8B_7A5A987583CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScomm_VC6Dlg dialog

class CScomm_VC6Dlg : public CDialog
{
// Construction
public:
	CScomm_VC6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScomm_VC6Dlg)
	enum { IDD = IDD_SCOMM_VC6_DIALOG };
	CMSComm	m_ctrlComm;
	CString	m_send;
	CString	m_receive;
//	CString	m_DisplayTemp;
	//float	m_float;
	CNTGraph	m_Graph;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScomm_VC6Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScomm_VC6Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONSend();
	afx_msg void OnButtonH();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnButtonSendall();
	afx_msg void OnButtonCurve();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelMode();
	afx_msg void OnButtonDisplayallcurve();


	//afx_msg void OnChooseskin();
	//afx_msg void OnSkinplusplus();

	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int Str2Hex(CString , CByteArray &);
	char HexChar(char );
//	CString m_send;
	afx_msg void OnBnClickedButtonOpen();
	// 用于记录列表的string
	CString StrComOfCombo;
	CComboBox ControlOfComCombo;
	// Baud 的 ComboBox 控制量
	CComboBox ControlComboBaud;
	// 用于记录  存储波特率的ComboBox的值 的CString
	CString StrForBaudCombo;
	afx_msg void OnBnClickedButtonClearReceive();
	// 命令输入框的控制变量
	CEdit CMDTobeSend;
	// 延时ComboBox的控制量
	CEdit ControlOfDealy;
//	CString StrForCMD;
	CComboBox ControlComboDealy;
	CString StrForEditDelay;
	afx_msg void OnBnClickedButtonQuit();

protected:
	HWND StatusBar;  // 状态栏
public:
	afx_msg void OnBnClickedStaticContinusSet();
	CEdit ControlOfDataLength;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOMM_VC6DLG_H__83053864_9F6F_483E_9A8B_7A5A987583CC__INCLUDED_)
