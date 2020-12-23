// About.cpp: 实现文件
//

#include "pch.h"
#include "Note Helper.h"
#include "About.h"
#include "afxdialogex.h"


// About 对话框

IMPLEMENT_DYNAMIC(About, CDialogEx)

About::About(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(About, CDialogEx)
END_MESSAGE_MAP()


// About 消息处理程序
