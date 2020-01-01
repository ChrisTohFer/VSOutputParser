#pragma once


// ParseFileDialog dialog

class ParseFileDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ParseFileDialog)

public:
	ParseFileDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ParseFileDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARSE_SINGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_filePath;
};
