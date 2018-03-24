#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// threadmod 对话框

class threadmod : public CDialogEx
{
	DECLARE_DYNAMIC(threadmod)

public:
	threadmod(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~threadmod();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool Enumthread(DWORD pid);
	bool Enumthread();
	//afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	CListCtrl mythreadlistctrl;
	CString threadid;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
