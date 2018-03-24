#pragma once
#include "afxcmn.h"


// mywinmodo 对话框

class mywinmodo : public CDialogEx
{
	DECLARE_DYNAMIC(mywinmodo)

public:
	mywinmodo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~mywinmodo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	
public:
	CRect rc;
	void Enumwin();
	DWORD nwidth;
	CListCtrl mywinctrl;
};
extern HWND pWnd;