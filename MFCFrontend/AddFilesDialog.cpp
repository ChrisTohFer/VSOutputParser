// AddFilesDialog.cpp : implementation file
//

#include "pch.h"
#include "MFCFrontend.h"
#include "AddFilesDialog.h"
#include "afxdialogex.h"

//Manual includes
#include "VerboseParser/Parser.h"

// AddFilesDialog dialog

IMPLEMENT_DYNAMIC(AddFilesDialog, CDialogEx)

AddFilesDialog::AddFilesDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDFILES, pParent)
{

}

AddFilesDialog::~AddFilesDialog()
{
}

void AddFilesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDFILES_LISTBOX, addfiles_listbox);
}


BEGIN_MESSAGE_MAP(AddFilesDialog, CDialogEx)
	ON_MESSAGE(WM_DROPFILES, &AddFilesDialog::OnDropFiles)
	ON_BN_CLICKED(IDOK, &AddFilesDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// AddFilesDialog message handlers


LRESULT AddFilesDialog::OnDropFiles(WPARAM wParam, LPARAM)
{
	auto files_handle = reinterpret_cast<HDROP>(wParam);

	auto count = DragQueryFileA(files_handle, 0xFFFFFFFF, nullptr, 0);
	for (auto i = 0u; i < count; ++i)
	{
		char buffer[256];
		DragQueryFileA(files_handle, i, buffer, sizeof(buffer));
		addfiles_listbox.AddItem(CString(buffer));
	}

	DragFinish(files_handle);
	return 0;
}

void AddFilesDialog::OnBnClickedOk()
{
	auto count = addfiles_listbox.GetCount();
	
	if (count == 1)
	{
		VERBOSE::parse_and_add(addfiles_listbox.GetItemText(0).GetString());
	}
	else if(count > 1)
	{
		//Parse multiple
		std::vector<std::wstring> paths;
		for (auto i = 0; i < count; ++i)
			paths.push_back(addfiles_listbox.GetItemText(i).GetString());

		VERBOSE::parse_and_add(paths);
	}

	CDialogEx::OnOK();
}
