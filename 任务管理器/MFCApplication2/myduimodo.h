#pragma once
#include "afxcmn.h"


// myduimodo 对话框

class myduimodo : public CDialogEx
{
	DECLARE_DYNAMIC(myduimodo)

public:
	myduimodo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~myduimodo();
	DWORD pid;
	bool Enumheap(DWORD PID);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
public:
	CListCtrl myduictrl;
};
