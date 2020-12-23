// Helps.cpp: 实现文件
//

#include "pch.h"
#include "Note Helper.h"
#include "Helps.h"
#include "afxdialogex.h"


// Helps 对话框

IMPLEMENT_DYNAMIC(Helps, CDialogEx)

Helps::Helps(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

Helps::~Helps()
{
}

void Helps::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Helps, CDialogEx)
END_MESSAGE_MAP()


// Helps 消息处理程序
