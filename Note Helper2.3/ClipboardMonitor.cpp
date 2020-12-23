// ClipboardMonitor.cpp: 实现文件
//

#include "pch.h"
#include "Note Helper.h"
#include "ClipboardMonitor.h"
#include "afxdialogex.h"
#include "fstream"
#include "Note HelperDlg.h"

// ClipboardMonitor 对话框

IMPLEMENT_DYNAMIC(ClipboardMonitor, CDialogEx)

ClipboardMonitor::ClipboardMonitor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ClipboardMonitor::~ClipboardMonitor()
{
}

void ClipboardMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ClipboardMonitor, CDialogEx)
	ON_BN_CLICKED(ID_BTN_START, &ClipboardMonitor::OnBnClickedBtnStart)
	ON_BN_CLICKED(ID_BTN_STOP, &ClipboardMonitor::OnBnClickedBtnStop)
	ON_BN_CLICKED(ID_CLEAR, &ClipboardMonitor::OnBnClickedClear)
	ON_EN_CHANGE(IDC_EDIT_SHOW, &ClipboardMonitor::OnEnChangeEditShow)
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
END_MESSAGE_MAP()


// ClipboardMonitor 消息处理程序

void ClipboardMonitor::AppendText(int nItemId, LPSTR lpString)
{
	CString strText;
	GetDlgItemText(nItemId, strText);
	if (strText.GetLength() == 0)
	{
		strText += lpString;
	}
	else
	{
		strText += "\r\n";
		strText += lpString;
	}

	SetDlgItemText(nItemId, strText);
	((CEdit*)GetDlgItem(nItemId))->SetSel(0, -1);
}


void ClipboardMonitor::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_isMonitor == false)
	{
		m_hWndClip = SetClipboardViewer();
		m_isMonitor = true;
		SetWindowText("Note Helper 开始监视");		//改变窗口标题
	}
	else
		AppendText(IDC_EDIT_SHOW, "已启动监视！");
}


void ClipboardMonitor::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_isMonitor == true)
	{
		ChangeClipboardChain(m_hWndClip);
		m_isMonitor = false;
		SetWindowText("Note Helper");		//改变窗口标题
	}
	else
		AppendText(IDC_EDIT_SHOW, "已停止监视！");
}


void ClipboardMonitor::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_SHOW, NULL);
}


void ClipboardMonitor::OnEnChangeEditShow()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void ClipboardMonitor::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter)
{
	CDialogEx::OnChangeCbChain(hWndRemove, hWndAfter);

	// TODO: 在此处添加消息处理程序代码
	if (m_hWndClip == hWndRemove)
		m_hWndClip = hWndAfter;

	::SendMessage(m_hWndClip, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter);
}


void ClipboardMonitor::OnDrawClipboard()
{
	CDialogEx::OnDrawClipboard();

	// TODO: 在此处添加消息处理程序代码
	OpenClipboard();
	if (IsClipboardFormatAvailable(CF_TEXT))
	{
		HANDLE hmem = ::GetClipboardData(CF_TEXT);
		char* pData = (char*)GlobalLock(hmem);
		CString strData = pData;
		AppendText(IDC_EDIT_SHOW, strData.GetBuffer());

		//--------------保存文本信息，成功！-----------------------------------------
		getpath();
		thepath = thepath + ".txt";
		std::ofstream out(thepath);
		out << pData;
		//-------------------------------------------------------------------------

		GlobalUnlock(hmem);//内存解锁-newadd
	}
	//---------------保存图片,会报错！！！---------------------------------------
	else if (IsClipboardFormatAvailable(CF_DIB))
	{
		//下面有问题，保存几张后就会有hBitmap！=0
		//release下弄就行！！！
		HBITMAP hBitmap = NULL;
		hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
		CImage image;

		if (!image.IsNull())    //Attach前，必须确认image中无位图，否则会弹出异常
			image.Destroy();

		getpath();
		thepath = thepath + ".png";

		image.Attach(hBitmap);						//hBitmap转化为CImage这条语句出的问题！！！
		image.Save(thepath, Gdiplus::ImageFormatPNG);

		char* pData = "图片保存成功";
		CString strData = pData;
		AppendText(IDC_EDIT_SHOW, strData.GetBuffer());

		//GlobalUnlock(hBitmap);

	}
	CloseClipboard();
	::SendMessage(m_hWndClip, WM_DRAWCLIPBOARD, 0, 0);
}

void ClipboardMonitor::getpath()
{
	CString strFileName = _T("apart.dat");			//读取配置文件，看要不要分类保存
	CString str;
	CStdioFile file;
	file.Open(strFileName, CFile::modeRead);
	file.ReadString(str);
	file.Close();

	CString strFileNamex = _T("savepath.dat");		//读配置文件，确定主文件夹位置
	CString	path;
	CStdioFile filex;
	filex.Open(strFileNamex, CFile::modeRead);
	filex.ReadString(path);
	filex.Close();
	path = path + "\\";

	CString strFileNamez = _T("timetable.dat");		//读取课表，确定子文件夹位置
	CString	course[14] = { NULL };					//课名
	CStdioFile filez;
	if (PathFileExists(strFileNamez))				//如果课表存在；
	{
		filez.Open(strFileNamez, CFile::modeRead);
		for (int i = 0; i < 13; i++)
		{
			filez.ReadString(course[i]);
		}
		filez.Close();
	}

	TCHAR szName[MAX_PATH] = { 0 };					//目前的时间
	SYSTEMTIME st = { 0 };
	::GetLocalTime(&st);
	_stprintf(szName, _T("\\%02d-%02d-%02d-%03d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	thepath.Empty();

	int thetime = st.wHour * 100 + st.wMinute;

	if (str == "true")			//说明要分类保存
	{
		if (thetime >= 825 && thetime <= 920)
		{
			if (course[0].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[0] + szName;
		}
		else if (thetime >= 920 && thetime <= 1015)
		{
			if (course[1].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[1] + szName;
		}
		else if (thetime >= 1025 && thetime <= 1120)
		{
			if (course[2].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[2] + szName;
		}
		else if (thetime >= 1120 && thetime <= 1215)
		{
			if (course[3].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[3] + szName;
		}
		else if (thetime >= 1215 && thetime <= 1310)
		{
			if (course[4].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[4] + szName;
		}
		else if (thetime >= 1310 && thetime <= 1355)
		{
			if (course[5].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[5] + szName;
		}
		else if (thetime >= 1355 && thetime <= 1450)
		{
			if (course[6].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[6] + szName;
		}
		else if (thetime >= 1450 && thetime <= 1545)
		{
			if (course[7].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[7] + szName;
		}
		else if (thetime >= 1555 && thetime <= 1650)
		{
			if (course[8].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[8] + szName;
		}
		else if (thetime >= 1650 && thetime <= 1745)
		{
			if (course[9].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[9] + szName;
		}
		else if (thetime >= 1855 && thetime <= 1950)
		{
			if (course[10].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[10] + szName;
		}
		else if (thetime >= 1950 && thetime <= 2045)
		{
			if (course[11].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[11] + szName;
		}
		else if (thetime >= 2045 && thetime <= 2130)
		{
			if (course[12].IsEmpty())
				thepath = path + "SAVE" + szName;
			else
				thepath = path + course[12] + szName;
		}
		else
		{
			thepath = path + "SAVE" + szName;
		}
	}
	else                        //说明不要分类保存
	{
		thepath = path + "SAVE" + szName;
	}
}