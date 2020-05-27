// LibraryDetailsDialog.cpp : implementation file
//

#include "pch.h"
#include "MFCFrontend.h"
#include "LibraryDetailsDialog.h"
#include "afxdialogex.h"


// LibraryDetailsDialog dialog

IMPLEMENT_DYNAMIC(LibraryDetailsDialog, CDialogEx)

LibraryDetailsDialog::LibraryDetailsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBDETAILS, pParent)
{

}

LibraryDetailsDialog::~LibraryDetailsDialog()
{
}

void LibraryDetailsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARENT_EDIT, m_parent_edit);
	DDX_Control(pDX, IDC_NAME_EDIT, m_name_edit);
	DDX_Control(pDX, IDC_PATH_EDIT, m_path_edit);
	DDX_Control(pDX, IDC_TYPE_EDIT, m_type_edit);
	DDX_Control(pDX, IDC_DEFAULT_EDIT, m_default_edit);
	DDX_Control(pDX, IDC_REFERENCES_EDIT, m_references_list);
}

BOOL LibraryDetailsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	{
		std::wstring str(m_library.parent.begin(), m_library.parent.end());
		m_parent_edit.SetWindowTextW(str.c_str());
	}
	{
		std::wstring str(m_library.name.begin(), m_library.name.end());
		m_name_edit.SetWindowTextW(str.c_str());
	}
	{
		std::wstring str(m_library.path.begin(), m_library.path.end());
		m_path_edit.SetWindowTextW(str.c_str());
	}

	m_type_edit.SetWindowTextW(m_library.type == VERBOSE::LIB_TYPE::STATIC ? L"Static" : L"DLL");
	m_default_edit.SetWindowTextW(m_library.defaultLib ? L"Default" : L"Not default");

	return 0;
}


BEGIN_MESSAGE_MAP(LibraryDetailsDialog, CDialogEx)
END_MESSAGE_MAP()


// LibraryDetailsDialog message handlers
