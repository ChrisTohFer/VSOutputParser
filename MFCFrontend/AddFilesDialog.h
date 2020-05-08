#pragma once


// AddFilesDialog dialog

class AddFilesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AddFilesDialog)

public:
	AddFilesDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddFilesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDFILES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	LRESULT OnDropFiles(WPARAM, LPARAM);
	afx_msg void OnBnClickedOk();

	//Members
private:
	CVSListBox addfiles_listbox;

public:
	
};
