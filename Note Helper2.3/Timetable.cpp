// Timetable.cpp: 实现文件
//

#include "pch.h"
#include "Note Helper.h"
#include "Timetable.h"
#include "afxdialogex.h"
#include "fstream"


// Timetable 对话框

IMPLEMENT_DYNAMIC(Timetable, CDialogEx)

Timetable::Timetable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
}

Timetable::~Timetable()
{
}

void Timetable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Timetable, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SAVETABLE, &Timetable::OnBnClickedBtnSavetable)
	ON_BN_CLICKED(IDC_BTN_GIVEUP, &Timetable::OnBnClickedBtnGiveup)
END_MESSAGE_MAP()


// Timetable 消息处理程序

void Timetable::OnBnClickedBtnSavetable()
{
	// TODO: 在此添加控件通知处理程序代码
	//用于缓冲的临时CString
	//CString tempstr;
	//获取ID_SimPause按钮的文本内容，其中ID_SimPause为按钮的ID
	//GetDlgItem(IDC_BTN_SAVETABLE)->GetWindowText(tempstr);
	//其中ID_SimPause为按钮的ID,””内为按钮的文字内容
	if (savetimetable)
	{
		savetimetable = false;
		GetDlgItem(IDC_BTN_SAVETABLE)->SetWindowText("编辑课表");
		//这里需要一个改变编辑框为只读属性，并且可以保存编辑框内容并显示的算法或函数，最好弹出一个保存成功的对话框
		CString strTable = NULL;
		for (int i = 0; i < 13; i++)
		{
			CString strText;
			GetDlgItemText(IDC_EDIT1 + i, strText);		                //获取要保存的文字信息
			GetDlgItem(IDC_EDIT1 + i)->EnableWindow(FALSE);				//让编辑框失效
			strTable = strTable + strText + "\n";
		}

		std::ofstream out("timetable.dat");
		out << strTable;

//----创建课表文件夹
		CString strFileName = _T("savepath.dat");
		CStdioFile file;
		CString filePath;
		file.Open(strFileName, CFile::modeRead);
		file.ReadString(filePath);
		file.Close();
		filePath = filePath + "\\";

		CString strFileNamex = _T("apart.dat");			//读取配置文件，看要不要分类保存
		CString str;
		CStdioFile filex;
		filex.Open(strFileNamex, CFile::modeRead);
		filex.ReadString(str);
		filex.Close();

		CreateDirectory(filePath + "SAVE", NULL);//创建文件夹,这里创建一个最基本的文件夹，默认保存的地方
		if (str == "true")
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

	}
	else
	{
		savetimetable = true;
		GetDlgItem(IDC_BTN_SAVETABLE)->SetWindowText("保存课表");
		//这里需要一个改变编辑框为读写属性的函数或算法、让课表可以编辑！
		for (int i = 0; i < 13; i++)
		{
			GetDlgItem(IDC_EDIT1 + i)->EnableWindow(TRUE);
		}

	}
}

void Timetable::OnBnClickedBtnGiveup()
{
	// TODO: 在此添加控件通知处理程序代码
	savetimetable = false;
	GetDlgItem(IDC_BTN_SAVETABLE)->SetWindowText("编辑课表");
	ShowTimeTable();
	for (int i = 0; i < 13; i++)
		GetDlgItem(IDC_EDIT1 + i)->EnableWindow(FALSE);
}

void Timetable::ShowTimeTable()
{
	CString strFileName = _T("timetable.dat");
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
		CString strValue = NULL;
		file.ReadString(strValue);
		GetDlgItem(IDC_EDIT1 + i)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT1 + i)->SetWindowText(strValue);//先清除再输入
	}
	file.Close();
}