#pragma once


// Helps 对话框

class Helps : public CDialogEx
{
	DECLARE_DYNAMIC(Helps)

public:
	Helps(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Helps();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
