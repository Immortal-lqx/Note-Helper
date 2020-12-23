#pragma once


// Settings 对话框

class Settings : public CDialogEx
{
	DECLARE_DYNAMIC(Settings)

public:
	Settings(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Settings();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFindpath();
	afx_msg void OnBnClickedBtnDiv();
	afx_msg void OnBnClickedBtnUpwin();

public:
	bool topwindow = true;	//确定是否窗口置顶	//功能已经实现！
	bool apart = true;	//确定是否按课表分类保存笔记
	CString filePath = NULL;//存放选择的目录路径(主文件夹)
	void readPath();
};