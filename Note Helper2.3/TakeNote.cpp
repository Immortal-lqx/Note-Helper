// TakeNote.cpp: 实现文件
//

#include "pch.h"
#include "Note Helper.h"
#include "TakeNote.h"
#include "afxdialogex.h"
#include "fstream"
#include "Note HelperDlg.h"


// TakeNote 对话框

IMPLEMENT_DYNAMIC(TakeNote, CDialogEx)

TakeNote::TakeNote(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

TakeNote::~TakeNote()
{
}

void TakeNote::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TakeNote, CDialogEx)
	ON_BN_CLICKED(ID_BTN_SAVENOTE, &TakeNote::OnBnClickedBtnSavenote)
	ON_BN_CLICKED(IDC_BTN_CLEARa, &TakeNote::OnBnClickedBtnCleara)
END_MESSAGE_MAP()


// TakeNote 消息处理程序

void TakeNote::AppendText(int nItemId, LPSTR lpString)
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

void TakeNote::OnBnClickedBtnSavenote()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	GetDlgItemText(IDC_EDIT_SHOWa, strText);		                //获取要保存的文字信息
	
	if (strText != "笔记保存成功！" && strText != "笔记已保存！")
	{
		getpath();
		thepath = thepath + ".txt";
		std::ofstream out(thepath);
		out << strText;

		SetDlgItemText(IDC_EDIT_SHOWa, NULL);

		char* pData = "笔记保存成功！";
		CString strData = pData;
		AppendText(IDC_EDIT_SHOWa, strData.GetBuffer());
	}
	else
	{
		SetDlgItemText(IDC_EDIT_SHOWa, NULL);

		char* pData = "笔记已保存！";
		CString strData = pData;
		AppendText(IDC_EDIT_SHOWa, strData.GetBuffer());
	}
}


void TakeNote::OnBnClickedBtnCleara()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_SHOWa, NULL);
}


void TakeNote::getpath()
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
		if (thetime>=825 && thetime<=920)
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