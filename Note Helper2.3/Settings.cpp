// Settings.cpp: 实现文件
//

#include "pch.h"
#include "Note Helper.h"
#include "Settings.h"
#include "afxdialogex.h"
#include "fstream"

// Settings 对话框

IMPLEMENT_DYNAMIC(Settings, CDialogEx)

Settings::Settings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{
}

Settings::~Settings()
{
}

void Settings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Settings, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FINDPATH, &Settings::OnBnClickedBtnFindpath)
	ON_BN_CLICKED(IDC_BTN_DIV, &Settings::OnBnClickedBtnDiv)
	ON_BN_CLICKED(IDC_BTN_UPWIN, &Settings::OnBnClickedBtnUpwin)
END_MESSAGE_MAP()


// Settings 消息处理程序


void Settings::OnBnClickedBtnFindpath()
{
	// TODO: 在此添加控件通知处理程序代码

	//注意！目前就弄出来个创建文件夹、浏览文件夹，没有把需要的功能实现，szpath这个变量要改改！
	char szPath[MAX_PATH] = { 0 };
	ZeroMemory(szPath, sizeof(szPath));
	
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = (LPSTR)szPath;
	bi.lpszTitle = _T("请选择所需的目录：");
	bi.ulFlags = BIF_BROWSEINCLUDEFILES | BIF_NEWDIALOGSTYLE;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(lp, (LPSTR)szPath);

	CString str1, str2;

	if (lp && SHGetPathFromIDList(lp, (LPSTR)szPath))
	{

		str1.Format(_T("选择的路径为： %s"), szPath);
		if (MessageBox(str1, _T("路径"), MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL) 
		{
			return;
		}
		else 
		{	
			//这里是需要具体实现根据课表创建文件夹的地方（注意一个课程名可能对应多节课程！！！）（对FileName动手就行！）
			str2.Format(_T("%s"), szPath);
			filePath = str2 + "\\";//路径+文件名
			CreateDirectory(filePath + "SAVE", NULL);//创建文件夹,这里创建一个最基本的文件夹，默认保存的地方
			
			std::ofstream out("savepath.dat");
			out << filePath;
			GetDlgItem(IDC_EDIT_SHOWPATH)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT_SHOWPATH)->SetWindowText(filePath);//先清除再输入

			if (apart)
			{
				CString strFileName = _T("timetable.dat");			//读取课表
				if (!PathFileExists(strFileName))
				{
					return;
				}
				CStdioFile file;
				if (!file.Open(strFileName, CFile::modeRead))
				{
					return;
				}
				for (int i = 0; i < 13; i++)
				{
					CString FileName;
					file.ReadString(FileName);
					CreateDirectory(filePath + FileName, NULL);
				}
				file.Close();
			}
			UpdateData(FALSE);
		}
	}
	else
	{
		AfxMessageBox(_T("无效的目录，请重新选择"));
		return;
	}

}


void Settings::OnBnClickedBtnDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	if (apart)
	{
		std::ofstream out("apart.dat");
		out << "false";

		apart = false;
		GetDlgItem(IDC_BTN_DIV)->SetWindowText("否");
	}
	else
	{
		std::ofstream out("apart.dat");
		out << "true";

		apart = true;
		GetDlgItem(IDC_BTN_DIV)->SetWindowText("是");
	}
}


void Settings::OnBnClickedBtnUpwin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (topwindow)
	{
		topwindow = false;
		GetDlgItem(IDC_BTN_UPWIN)->SetWindowText("否");
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//取消窗口置顶
	}
	else
	{
		topwindow = true;
		GetDlgItem(IDC_BTN_UPWIN)->SetWindowText("是");
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//窗口置顶
	}

}

void Settings::readPath()
{
	CString strFileName = _T("savepath.dat");
	if (!PathFileExists(strFileName))
	{
		return;
	}
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead))
	{
		return;
	}
	file.ReadString(filePath);
	GetDlgItem(IDC_EDIT_SHOWPATH)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_SHOWPATH)->SetWindowText(filePath);//先清除再输入
	file.Close();
}