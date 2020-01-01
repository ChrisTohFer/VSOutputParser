// ParseFileDialog.cpp : implementation file
//

#include "pch.h"
#include "MFCTest.h"
#include "ParseFileDialog.h"
#include "afxdialogex.h"

//
#include "VerboseParser/VerboseOutputParser.h"


// ParseFileDialog dialog

IMPLEMENT_DYNAMIC(ParseFileDialog, CDialogEx)

ParseFileDialog::ParseFileDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PARSE_SINGLE, pParent)
{

}

ParseFileDialog::~ParseFileDialog()
{
}

void ParseFileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_PATH_INPUT, m_filePath);
}


BEGIN_MESSAGE_MAP(ParseFileDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ParseFileDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ParseFileDialog message handlers


void ParseFileDialog::OnBnClickedOk()
{
	WCHAR path[100];
	m_filePath.GetWindowTextW(path, 100);
	VERBOSE::LOG_CONTENT log = VERBOSE::ParseLogFile(std::wstring(path));

	CDialogEx::OnOK();
}
