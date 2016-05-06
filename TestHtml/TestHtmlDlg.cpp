
// TestHtmlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestHtml.h"
#include "TestHtmlDlg.h"
#include "afxdialogex.h"
#include <ctime>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestHtmlDlg dialog




CTestHtmlDlg::CTestHtmlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestHtmlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestHtmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}

BEGIN_MESSAGE_MAP(CTestHtmlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestHtmlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestHtmlDlg message handlers

BOOL CTestHtmlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestHtmlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestHtmlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestHtmlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI httpRequest2(LPVOID lp){
	CTestHtmlDlg* dlg=(CTestHtmlDlg*)lp;
	dlg->httpRequest();

	return 0;
}

void CTestHtmlDlg::OnBnClickedButton1()
{
HANDLE handle=	CreateThread(NULL,0,httpRequest2,this,0,NULL);
}

void CTestHtmlDlg::httpRequest(){
	try{
	WSADATA WSAData;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 0 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( 0 != err ) //检查Socket初始化是否成功
	{
		AfxMessageBox(_T("Socket2.0初始化失败，Exit!"));
		return ;
	}
	int soc;
	soc=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN srv_addr;
	srv_addr.sin_port=htons(8080);
	srv_addr.sin_family=AF_INET;
	srv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int nNetTimeout = 1000*10; //1秒
	//发送时限
	setsockopt( soc, SOL_SOCKET, SO_SNDTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
	//接收时限
	setsockopt( soc, SOL_SOCKET, SO_RCVTIMEO, ( char * )&nNetTimeout, sizeof( int ) );

	connect(soc,(LPSOCKADDR)&srv_addr,sizeof(srv_addr));
	char content[256]={0};
	char reqParm[]="&vbatt=1&time=100";
	char sz[]="GET /sc/machine?_type=web&_method=getMachineState";
	char sz2[]=	" HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection:keep-alive\r\n\r\n";
	strcat(content,sz);
	strcat(content,reqParm);
	strcat(content,sz2);
	send(soc,content,strlen(content),0);
	static char webcon[BUFSIZ];
	CString info;
	time_t first=time(0);
	while ( recv(soc,webcon, BUFSIZ, 0) > 0)
	{ 
		info+=CString(webcon);
		strnset(webcon, '\0', BUFSIZ);
	}
	time_t second=time(0);
	char t[20]={0};
	
	double a=difftime(second,first);
	char s[100];
	sprintf(s,"%.2lf",a);
	//to_string(difftime(second,first));
	MessageBox(CString(s));
	m_listbox.AddString(info);
	}catch(...){
		AfxMessageBox(_T("异常"));
	}
	return ;
}