
// Note HelperDlg.h: 头文件
//

#pragma once
#include "About.h"
#include "ClipboardMonitor.h"
#include "Helps.h"
#include "Settings.h"
#include "TakeNote.h"
#include "Timetable.h"



// CNoteHelperDlg 对话框
class CNoteHelperDlg : public CDialogEx
{
// 构造
public:
	CNoteHelperDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEHELPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	ClipboardMonitor* monitor = NULL;
	TakeNote* note = NULL;
	Timetable* table = NULL;
	Settings* set = NULL;
	Helps* help = NULL;
	About* about = NULL;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnMenuTakenote();
	afx_msg void OnMenuMonitor();
	afx_msg void OnMenuTimetable();
	afx_msg void OnMenuSetting();
	afx_msg void OnMenuHelp();
	afx_msg void OnMenuAbout();
	afx_msg void OnBreakout();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

private:
	int windowname = 0;
	bool visible = true;
	CRect rect=NULL;
	void GetPlace();
	void HideandShow();
};
