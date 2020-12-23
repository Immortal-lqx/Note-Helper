#pragma once


// ClipboardMonitor 对话框

class ClipboardMonitor : public CDialogEx
{
	DECLARE_DYNAMIC(ClipboardMonitor)

public:
	ClipboardMonitor(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ClipboardMonitor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	HWND m_hWndClip=NULL;
	bool m_isMonitor=false;
	void AppendText(int nItemId, LPSTR lpString);
	void getpath();
	CString thepath;
public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedClear();
	afx_msg void OnEnChangeEditShow();
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDrawClipboard();
};
