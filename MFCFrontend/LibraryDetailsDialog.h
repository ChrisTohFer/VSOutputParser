#pragma once


// LibraryDetailsDialog dialog

class LibraryDetailsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(LibraryDetailsDialog)

public:
	LibraryDetailsDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LibraryDetailsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBDETAILS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_parent_edit;
	CEdit m_name_edit;
	CEdit m_path_edit;
	CEdit m_type_edit;
	CEdit m_default_edit;
	CListBox m_references_list;
};
