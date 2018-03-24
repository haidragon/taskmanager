#pragma once


// myCEdit

class myCEdit : public CEdit
{
	DECLARE_DYNAMIC(myCEdit)

public:
	myCEdit();
	virtual ~myCEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CString ctr;
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


