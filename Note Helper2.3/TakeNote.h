#pragma once


// TakeNote 对话框

class TakeNote : public CDialogEx
{
	DECLARE_DYNAMIC(TakeNote)

public:
	TakeNote(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TakeNote();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSavenote();
	afx_msg void OnBnClickedBtnCleara();
private:
	void AppendText(int nItemId, LPSTR lpString);
	void getpath();
	CString thepath;
};
