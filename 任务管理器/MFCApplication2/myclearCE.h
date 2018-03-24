#pragma once


// myclearCE

class myclearCE : public CEdit
{
	DECLARE_DYNAMIC(myclearCE)

public:
	myclearCE();
	CString myctr;
	virtual ~myclearCE();
	void EnumDir(CString pDir);
	CString rootctr;
	CString ctrmulu;
	void deleteFolder(TCHAR * load);
	void EnumLoad(TCHAR * load);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


