#pragma once


// Timetable 对话框

class Timetable : public CDialogEx
{
	DECLARE_DYNAMIC(Timetable)

public:
	Timetable(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Timetable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	BOOL savetimetable = false;

public:
	void ShowTimeTable();

public:
	afx_msg void OnBnClickedBtnSavetable();
	afx_msg void OnBnClickedBtnGiveup();
};
