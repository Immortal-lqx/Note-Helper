
// Note HelperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Note Helper.h"
#include "Note HelperDlg.h"
#include "afxdialogex.h"
#include "fstream"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNoteHelperDlg 对话框



CNoteHelperDlg::CNoteHelperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEHELPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNoteHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNoteHelperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNoteHelperDlg::OnBnClickedOk)
	ON_COMMAND(ID_MENU_TAKENOTE, &CNoteHelperDlg::OnMenuTakenote)
	ON_COMMAND(ID_MENU_MONITOR, &CNoteHelperDlg::OnMenuMonitor)
	ON_COMMAND(ID_MENU_TIMETABLE, &CNoteHelperDlg::OnMenuTimetable)
	ON_COMMAND(ID_MENU_SETTING, &CNoteHelperDlg::OnMenuSetting)
	ON_COMMAND(ID_MENU_HELP, &CNoteHelperDlg::OnMenuHelp)
	ON_COMMAND(ID_MENU_ABOUT, &CNoteHelperDlg::OnMenuAbout)
	ON_COMMAND(ID_BREAKOUT, &CNoteHelperDlg::OnBreakout)
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CNoteHelperDlg 消息处理程序

BOOL CNoteHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//窗口置顶

	RegisterHotKey(m_hWnd, 9898, MOD_ALT, 'Q');//注册热键
	RegisterHotKey(m_hWnd, 8787, MOD_ALT, 'W');
	
	std::ofstream out("apart.dat");
	out << "true";

//设置一系列的窗口
	monitor = new ClipboardMonitor();
	monitor->Create(IDD_DIALOG1);
	monitor->ShowWindow(SW_HIDE);

	note = new TakeNote();
	note->Create(IDD_DIALOG2);
	note->ShowWindow(SW_HIDE);

	table = new Timetable();
	table->Create(IDD_DIALOG3);
	table->ShowTimeTable();
	table->ShowWindow(SW_HIDE);

	set = new Settings();
	set->Create(IDD_DIALOG4);
	set->readPath();
	set->ShowWindow(SW_HIDE);

	help = new Helps();
	help->Create(IDD_DIALOG5);
	help->ShowWindow(SW_HIDE);

	about = new About();
	about->Create(IDD_DIALOG6);
	about->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNoteHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNoteHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNoteHelperDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (set->filePath.IsEmpty())
	{
		if (MessageBox(_T("第一次使用请指定保存路径！"), _T("提示"), MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK)
		{
			this->ShowWindow(SW_HIDE);
			set->ShowWindow(SW_SHOW);
			set->OnBnClickedBtnFindpath();
			windowname = 4;
		}
		return;
	}
	
	this->ShowWindow(SW_HIDE);
	monitor->ShowWindow(SW_SHOW);
	windowname = 1;
}

void CNoteHelperDlg::OnMenuMonitor()
{
	// TODO: 在此添加命令处理程序代码
	GetPlace();
	if (rect != NULL)
		monitor->MoveWindow(rect);
	windowname = 1;

	monitor->ShowWindow(SW_SHOW);
}

void CNoteHelperDlg::OnMenuTakenote()
{
	// TODO: 在此添加命令处理程序代码
	GetPlace();
	if (rect != NULL)
		note->MoveWindow(rect);
	windowname = 2;

	note->ShowWindow(SW_SHOW);
}

void CNoteHelperDlg::OnMenuTimetable()
{
	// TODO: 在此添加命令处理程序代码
	GetPlace();
	if (rect != NULL)
		table->MoveWindow(rect);
	windowname = 3;

	table->ShowWindow(SW_SHOW);
}

void CNoteHelperDlg::OnMenuSetting()
{
	// TODO: 在此添加命令处理程序代码
	GetPlace();
	if (rect != NULL)
		set->MoveWindow(rect);
	windowname = 4;

	set->ShowWindow(SW_SHOW);
}

void CNoteHelperDlg::OnMenuHelp()
{
	// TODO: 在此添加命令处理程序代码
	GetPlace();
	if (rect != NULL)
		help->MoveWindow(rect);
	windowname = 5;

	help->ShowWindow(SW_SHOW);
}

void CNoteHelperDlg::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	GetPlace();
	if (rect != NULL)
		about->MoveWindow(rect);
	windowname = 6;

	about->ShowWindow(SW_SHOW);
}

void CNoteHelperDlg::OnBreakout()
{
	// TODO: 在此添加命令处理程序代码
	DestroyWindow();
}

void CNoteHelperDlg::GetPlace()
{
	switch (windowname)
	{
	case 1:
		monitor->GetWindowRect(rect);
		monitor->ShowWindow(SW_HIDE);
		break;
	case 2:
		note->GetWindowRect(rect);
		note->ShowWindow(SW_HIDE);
		break;
	case 3:
		table->GetWindowRect(rect);
		table->ShowWindow(SW_HIDE);
		break;
	case 4:
		set->GetWindowRect(rect);
		set->ShowWindow(SW_HIDE);
		break;
	case 5:
		help->GetWindowRect(rect);
		help->ShowWindow(SW_HIDE);
		break;
	case 6:
		about->GetWindowRect(rect);
		about->ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
}

void CNoteHelperDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nHotKeyId == 9898)
	{
		monitor->ShowWindow(SW_HIDE);
		note->ShowWindow(SW_HIDE);
		table->ShowWindow(SW_HIDE);
		set->ShowWindow(SW_HIDE);
		help->ShowWindow(SW_HIDE);
		about->ShowWindow(SW_HIDE);
		this->ShowWindow(SW_SHOW);
	}
	else if (nHotKeyId == 8787)
		HideandShow();

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CNoteHelperDlg::HideandShow()
{
	int x = windowname;
	if (visible)
		visible = false;
	else
	{
		visible = true;
		x = x + 10;
	}
	switch (x)
	{
	case 1:
		monitor->ShowWindow(SW_HIDE);
		break;
	case 2:
		note->ShowWindow(SW_HIDE);
		break;
	case 3:
		table->ShowWindow(SW_HIDE);
		break;
	case 4:
		set->ShowWindow(SW_HIDE);
		break;
	case 5:
		help->ShowWindow(SW_HIDE);
		break;
	case 6:
		about->ShowWindow(SW_HIDE);
		break;
	case 11:
		monitor->ShowWindow(SW_SHOW);
		break;
	case 12:
		note->ShowWindow(SW_SHOW);
		break;
	case 13:
		table->ShowWindow(SW_SHOW);
		break;
	case 14:
		set->ShowWindow(SW_SHOW);
		break;
	case 15:
		help->ShowWindow(SW_SHOW);
		break;
	case 16:
		about->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}