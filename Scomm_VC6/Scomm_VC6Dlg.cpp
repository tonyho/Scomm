// Scomm_VC6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scomm_VC6.h"
#include "Scomm_VC6Dlg.h"

#include <cstdlib>
#include <cstdio>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XMax 10
#define YCenter 25
#define  Range 8

double TempGet = 0.0;

BOOL COMOpen = FALSE;

 int DealyMsForCMD = 200 ; // 用于发送命令间隔设置

 int MinDataLength  = 0;

char CScomm_VC6Dlg::HexChar(char c)
{
	
	if( (c >= '0') && (c <= '9') )
		return c - 0x30;
	else if ((c >= 'A') && (c <= 'F') )
	{
		return c - 'A' + 10;
	}
	else if ((c >= 'a') && (c <= 'f') )
	{
		return c - 'a' + 10;
	}
	
	else 
		return -1;
	
}

int  CScomm_VC6Dlg::Str2Hex(CString str, CByteArray &senddata)
{
	int i = 0;
	
	int hexdata,lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	senddata.SetSize(len/2);
	
	
	for (i = 0; i < len; )
	{
		char lstr,hstr = str[i];
		
		if (hstr == '\0')
		{
			i ++;
			continue;
		}
		i++;
		
		if (i >= len)
		{
			break;
		}
		
		lstr = str[i];
		hexdata = HexChar(hstr);
		lowhexdata = HexChar(lstr);
		
		if ( (hexdata == 16) || (lowhexdata == 16) )
		{
			break;
		}
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		senddata[hexdatalen] = (char) hexdata;
		hexdatalen ++;
	}
	return hexdatalen;
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScomm_VC6Dlg dialog

CScomm_VC6Dlg::CScomm_VC6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScomm_VC6Dlg::IDD, pParent)
	, StrComOfCombo(_T(""))
	, StrForBaudCombo(_T(""))

	, StrForEditDelay(_T(""))
{
	//{{AFX_DATA_INIT(CScomm_VC6Dlg)
	m_send = _T("");
	m_receive = _T("");
//	m_DisplayTemp = _T("");
//	m_float = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScomm_VC6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScomm_VC6Dlg)
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_SEND, m_send);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_receive);
	//	DDX_Text(pDX, IDC_EDIT_DISPLAY_TEMP, m_DisplayTemp);
	//DDX_Text(pDX, IDC_EDIT_FLOAT, m_float);
	DDX_Control(pDX, IDC_NTGRAPHCTRL1, m_Graph);
	//}}AFX_DATA_MAP
	DDX_CBString(pDX, IDC_COMBO_COM, StrComOfCombo);
	DDX_Control(pDX, IDC_COMBO_COM, ControlOfComCombo);
	DDX_Control(pDX, IDC_COMBO_BAUD, ControlComboBaud);
	DDX_CBString(pDX, IDC_COMBO_BAUD, StrForBaudCombo);
	DDX_Control(pDX, IDC_EDIT_CMDTOBESEND, CMDTobeSend);
	DDX_Control(pDX, IDC_EDIT_CMD_DELAY, ControlOfDealy);
	//	DDX_CBString(pDX, IDC_COMBO_DELAYMS, StrForCMD);
	//	DDX_Control(pDX, IDC_COMBO_DELAYMS, ControlComboDealy);
	DDX_Text(pDX, IDC_EDIT_CMD_DELAY, StrForEditDelay);
	DDX_Control(pDX, IDC_EDIT_RECIEVE_DATA_LENGTH, ControlOfDataLength);
}

BEGIN_MESSAGE_MAP(CScomm_VC6Dlg, CDialog)
	//{{AFX_MSG_MAP(CScomm_VC6Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON_Send, OnBUTTONSend)
//	ON_BN_CLICKED(IDC_BUTTON_H, OnButtonH)
	ON_BN_CLICKED(IDC_BUTTON_SENDALL, OnButtonSendall)
	ON_BN_CLICKED(IDC_BUTTON_CURVE, OnButtonCurve)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_DISPLAYALLCURVE, OnButtonDisplayallcurve)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CScomm_VC6Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECEIVE, &CScomm_VC6Dlg::OnBnClickedButtonClearReceive)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CScomm_VC6Dlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_STATIC_CONTINUS_SET, &CScomm_VC6Dlg::OnBnClickedStaticContinusSet)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScomm_VC6Dlg message handlers

BOOL CScomm_VC6Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString StrForStatusBar = " 沈阳理工大学08级自动化 何雄军 2010-11-20";

	CTime NowTimeForStatusBar;
	CString StrNowTime;
	NowTimeForStatusBar = CTime::GetCurrentTime();
	StrNowTime = NowTimeForStatusBar.Format("%H:%M:%S");

	StrForStatusBar +=  "   程序打开时间: ";
	StrForStatusBar += StrNowTime;

	StatusBar = ::CreateStatusWindow(WS_CHILD|WS_VISIBLE,StrForStatusBar ,this->m_hWnd,IDD_SCOMM_VC6_DIALOG);
	::SendMessage(StatusBar,SB_SETBKCOLOR,0,(long)RGB(13,124,124));

	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("1");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("2");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("3");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("4");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("5");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("6");

	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("7");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("8");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("9");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("10");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("11");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("12");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("13");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("14");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("15");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString("16");

	((CComboBox *)GetDlgItem(IDC_COMBO_COM))->SetCurSel(6);  // 是从0开始的  而不是1    这里6为COM7

	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("300");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("600");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("1200");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("2400");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("4800");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("9600");

	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("19200");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("38400");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("43000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("56000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("57600");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString("115200");

	((CComboBox *)GetDlgItem(IDC_COMBO_BAUD))->SetCurSel(5);  // 是从0开始的  而不是1    这里6为COM7
	

	
	
	



//==============Default Element0===================//
	m_Graph.SetAxisColor (RGB(255,255,0));   
	m_Graph.SetLabelColor (RGB(128,10,255));   // Label Color

//	m_Graph.SetPlotAreaColor(RGB(122,222,50));
	// (1) - Flat
	// (2) - Scope (raised frame and sunken plot area borders)
	// (3) - 3DFrame (a bitmap frame picture)
	m_Graph.SetFrameStyle(1); 
	
	m_Graph.SetGridColor(RGB(100,50,0));
		m_Graph.SetElementLineColor(RGB(255,125,0));
	m_Graph.SetShowGrid (TRUE);
	
	m_Graph.SetCursorColor (RGB(255,0,0));
	m_Graph.SetTrackMode (1);
	

	m_Graph.SetXLabel ("时间");
	m_Graph.SetYLabel("温度");
	m_Graph.SetCaption("温度检测系统");
//	m_Graph.SetXTime(TRUE);
	m_Graph.SetRange(0,XMax,YCenter-Range,YCenter+Range);
	m_Graph.SetXGridNumber(20);
	m_Graph.SetYGridNumber(20);


//	m_Graph.PlotXY(0.5,0.5,0);
// 	for (double x = 0; x < 5; x=x+0.002)
// 	{
// 		m_Graph.PlotXY(x,4*sin(x*2*3.14)+20,0);
// 	}

	
//==============Element1===================//
	m_Graph.AddElement();
	m_Graph.SetElementLineColor(RGB(225,0,0));
	m_Graph.SetElementIdentify(FALSE);
	
// 		for (double x1 = 0; x1 < 5; x1=x1+0.002)
// 		{
// 			m_Graph.PlotXY(x1,-10*sin(x1*2*3.14)+30,1);
// 	 	}


		//==============Element2===================//
		m_Graph.AddElement();
		m_Graph.SetElementLineColor(RGB(10,200,10));
		m_Graph.SetElementIdentify(FALSE);
// 		for (double x2 = 0; x2 < 5; x2=x2+0.002)
// 		{
// 			m_Graph.PlotXY(x2,5*cos(x2*2*3.14)+30,2);
// 	 	}

		//==============Element3===================//
		m_Graph.AddElement();
		m_Graph.SetElementLineColor(RGB(100,200,0));
		m_Graph.SetElementIdentify(FALSE);

		//==============Element4===================//
		m_Graph.AddElement();
		m_Graph.SetElementLineColor(RGB(100,200,100));
		m_Graph.SetElementIdentify(FALSE);
//		m_Graph.PlotXY(2,30,4);
//		m_Graph.PlotXY(3,35,4);

	

	//m_receive = "H";
	m_send = "P";
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScomm_VC6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScomm_VC6Dlg::OnPaint() 
{
	/*
	CString StrForStatusBar;

	CTime NowTimeForStatusBar;
	CString StrNowTime;
	NowTimeForStatusBar = CTime::GetCurrentTime();
	StrNowTime = NowTimeForStatusBar.Format("%H:%M:%S");

	StrForStatusBar +=  "   程序打开时间: ";
	StrForStatusBar += StrNowTime;
		StatusBar = ::CreateStatusWindow(WS_CHILD|WS_VISIBLE,StrForStatusBar ,this->m_hWnd,IDD_SCOMM_VC6_DIALOG);
	::SendMessage(StatusBar,SB_SETBKCOLOR,0,(long)RGB(255,124,124));
	*/

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

	

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	
	
	//StrForStatusBar
	

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScomm_VC6Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/*
void CScomm_VC6Dlg::OnBUTTONSend() 
{
	// TODO: Add your control notification handler code here

	m_receive = "";
	CByteArray hexdata;
	m_send = "48";     //1
	
	int len = Str2Hex(m_send,hexdata);
	m_ctrlComm.SetOutput(COleVariant(hexdata));
	Sleep(100);
	UpdateData(FALSE);
	
}
*/
/*
void CScomm_VC6Dlg::OnButtonH() 
{
	// TODO: Add your control notification handler code here
		m_ctrlComm.SetOutput(COleVariant("P"));
		
	//	m_ctrlComm.SetOutput(COleVariant("T"));
	
}
*/

BEGIN_EVENTSINK_MAP(CScomm_VC6Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CScomm_VC6Dlg)
	ON_EVENT(CScomm_VC6Dlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

 double TemDouble = 0.0;
 int FlagToDrew = 0;

void CScomm_VC6Dlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here

	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[512];
	CString strtemp;
//	CString data;




	
//	m_receive.Empty();
	if ( 2  ==  m_ctrlComm.GetCommEvent() )
	{
		if(m_ctrlComm.GetInBufferCount() % MinDataLength == 0)   // 关键的一句  这里的GetInBufferCount为缓冲区接收到的字符数（如+25.8为5） 
			//  这就是5的来由
		{
		variant_inp = m_ctrlComm.GetInput();
		safearray_inp = variant_inp;
		
		len = safearray_inp.GetOneDimSize();
		
		for (k = 0; k<len; k++)
		{
			safearray_inp.GetElement(&k, rxdata+k);
		}
		
		for (k = 0; k<len; k++)
		{
			BYTE bt = *(char *)(rxdata+k);
			
			strtemp.Format("%c",bt);		
		
		//	data+= strtemp;
			m_receive += strtemp;
		//	if(m_receive.GetLength() >20)
			//	m_receive.Empty();
		}
		UpdateData(FALSE);

		TempGet = 0.0;
		int LengthOfm_receive = m_receive.GetLength();
		
		char TempStrDoulbe[6] = {m_receive[LengthOfm_receive-4],m_receive[LengthOfm_receive-3],m_receive[LengthOfm_receive-2],m_receive[LengthOfm_receive-1],m_receive[LengthOfm_receive], '\0'};
	//	 TemDouble = atof(m_receive);
		TemDouble = atof(TempStrDoulbe);//从字符型转换成float型
		CString TemString;
		TemString.Format("%f",TemDouble);//将TempDouble从float转换成 CString型

	
		//	MessageBox(TemString);
		FlagToDrew = 1;
	}
	}
	
	UpdateData(FALSE);


//	GetDlgItem()
	
}

void CScomm_VC6Dlg::OnButtonSendall() 
{
	// TODO: Add your control notification handler code here
//	CString StringToSend;
	UpdateData(TRUE);   // m_send 
	
	m_ctrlComm.SetOutput(COleVariant(m_send));
//	MessageBox(m_send);
//	MessageBox(m_receive);

}

void CScomm_VC6Dlg::OnButtonCurve() 
{
	// TODO: Add your control notification handler code here
	static int counterForClicked = 0;
	
	if(TRUE == COMOpen)
	{
		
		
		counterForClicked ++;

		if(counterForClicked  == 1 )
		{
			
			SetTimer(0,DealyMsForCMD,NULL);
		}

		if (counterForClicked == 2 )
		{
			KillTimer(0);
		
		}
		if (counterForClicked == 2)
		{
			counterForClicked = 0;
		}
	}
	else 
		MessageBox("看来忘记打开串口了,哈哈","提示");
}
	static int CounterForXE20 = 1;
void CScomm_VC6Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	

	switch (nIDEvent)
	{
	case 0:
		CString StrCmdToBeSend;  // 用于储存 IDC_EDIT_CMDTOBESEND 输入的命令
		GetDlgItemText(IDC_EDIT_CMDTOBESEND,StrCmdToBeSend); // 发送命令
		
       //	m_ctrlComm.SetOutput(COleVariant("P"));  // 首先发出P  
			m_ctrlComm.SetOutput(COleVariant(StrCmdToBeSend)); 
       	if (FlagToDrew == 1)
		{
			//====================Graph
			static	double  x3 =0.0;
			x3 += 0.125;
			m_Graph.PlotXY(x3,TemDouble,4);
			if (x3 == XMax*CounterForXE20)
			{
			
				CounterForXE20 ++;
				//	m_Graph.ClearGraph();
				//m_Graph.DeleteElement()
				//x3 = 0.0;
				m_Graph.SetRange( XMax*(CounterForXE20-1),XMax*CounterForXE20,TemDouble-3.0,TemDouble+3.0);
			}
		}
	FlagToDrew = 0;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CScomm_VC6Dlg::OnCancelMode(void)
{
	
}

void CScomm_VC6Dlg::OnButtonDisplayallcurve() 
{
	// TODO: Add your control notification handler code here
	static int CounterForDisplayAllCurve = 0;
	CounterForDisplayAllCurve ++;
	if (1 == CounterForDisplayAllCurve)
	{
		m_Graph.SetRange(0,XMax*CounterForXE20,YCenter-Range,YCenter+Range);
	} 
	else
	{
	  m_Graph.SetRange( XMax*(CounterForXE20-1),XMax*CounterForXE20,TemDouble-3.0,TemDouble+3.0);
	   CounterForDisplayAllCurve = 0;
	}
	
	
}

void CScomm_VC6Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	
	static int CounterForOpen = 0;
	CounterForOpen ++;

	

ControlOfDealy.GetWindowText(StrForEditDelay);
DealyMsForCMD=atoi(StrForEditDelay);
	//ControlComboDealy.GetWindowText(StrForCMD);
	//DealyMsForCMD=atoi(StrForCMD);

	CString StrDataLength;  // 用于存放长度的string
	ControlOfDataLength.GetWindowText(StrDataLength);
	MinDataLength = atoi(StrDataLength); // 转换成int型



	ControlOfComCombo.GetWindowText(StrComOfCombo);
//	char a[2]={StrComOfCombo[0],'\0'};
	int ComNum=atoi(StrComOfCombo);

	ControlComboBaud.GetWindowText(StrForBaudCombo);// 获得波特率Cstring
	CString StrForBaud;

if ( (FALSE == COMOpen) && (CounterForOpen %2 == 1) )
{

	m_ctrlComm.SetCommPort(ComNum);
	m_ctrlComm.SetInputMode(1);
	m_ctrlComm.SetInBufferSize(2048);

	m_ctrlComm.SetRThreshold(1);
	m_ctrlComm.SetSThreshold(1);

	//m_ctrlComm.SetSettings("9600,n,8,1");  StrForBaud = StrForBaudCombo + ",n,8,1"
	StrForBaud = StrForBaudCombo + ",n,8,1";   // 得到完整的 波特率设置 String 
	m_ctrlComm.SetSettings(StrForBaud); 

	m_ctrlComm.SetPortOpen(TRUE);

	COMOpen = TRUE;

	SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");
	SetDlgItemText(IDC_STATIC_STATUS,"已打开");
	
}

if (TRUE == COMOpen  && (CounterForOpen%2  == 0) )
{
		SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");
		SetDlgItemText(IDC_STATIC_STATUS,"未打开");
		KillTimer(0);
	    m_ctrlComm.SetPortOpen(FALSE);
		COMOpen = FALSE;
}
if (2000 == CounterForOpen)
{
	CounterForOpen = 0;
}

}

void CScomm_VC6Dlg::OnBnClickedButtonClearReceive()
{
	// TODO: 在此添加控件通知处理程序代码
	if (COMOpen)
	{
		m_receive.Empty();
		UpdateData(FALSE);
	}
}

void CScomm_VC6Dlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (COMOpen)
	{
			m_ctrlComm.SetPortOpen(FALSE);
	}
		skinppExitSkin();	   // 皮肤资源释放
	CDialog::OnCancel();

}

void CScomm_VC6Dlg::OnBnClickedStaticContinusSet()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("For Love, For Dream ");
}
