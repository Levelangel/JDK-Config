
// JDK ConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JDK Config.h"
#include "JDK ConfigDlg.h"
#include "afxdialogex.h"
//#include "atlbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJDKConfigDlg �Ի���



CJDKConfigDlg::CJDKConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJDKConfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
}

void CJDKConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJDKConfigDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTNBROSWER, &CJDKConfigDlg::OnBnClickedBtnbroswer)
	ON_BN_CLICKED(IDC_BTNEXIT, &CJDKConfigDlg::OnBnClickedBtnexit)
	ON_STN_CLICKED(IDC_STATIC_CHOOSEDIR, &CJDKConfigDlg::OnClickedStaticChoosedir)
END_MESSAGE_MAP()


// CJDKConfigDlg ��Ϣ�������

BOOL CJDKConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	this->SetWindowText(TEXT("JDK���������Զ����á����ᰮר��"));
	GetJavaVersion();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJDKConfigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJDKConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJDKConfigDlg::OnOK(){}
void CJDKConfigDlg::OnCancel(){}

void CJDKConfigDlg::OnClose()
{
	CDialogEx::OnCancel();
}

void CJDKConfigDlg::GetJavaVersion()
{
	HKEY hKey;
	HKEY root = HKEY_LOCAL_MACHINE;
	CString SubKey = TEXT("SOFTWARE\\JavaSoft\\Java Development Kit");
	REGSAM REG_TYPE = KEY_READ;
	if (IsWow64())
	{
		REG_TYPE = REG_TYPE | KEY_WOW64_64KEY;
	}
	long ret = RegOpenKeyEx(root, SubKey, 0, REG_TYPE, &hKey);
	if (ERROR_SUCCESS == ret)
	{
		unsigned char dwValue[256];
		DWORD dwSize = sizeof(dwValue);
		DWORD dwType = REG_SZ;
		if (RegQueryValueEx(hKey, TEXT("CurrentVersion"), nullptr, &dwType, dwValue, &dwSize) != ERROR_SUCCESS)
		{
			this->GetDlgItem(IDC_STATIC_JDKVERSION)->SetWindowText(_T("û�в��ҵ�JDK"));
			RegCloseKey(hKey);
			return;
		}
		this->GetDlgItem(IDC_STATIC_JDKVERSION)->SetWindowText((LPTSTR)dwValue);
		//����������رմ򿪵�hKEY
		RegCloseKey(hKey);
		SubKey += "\\";
		SubKey += reinterpret_cast<LPTSTR>(dwValue);
		ret = RegOpenKeyEx(root, SubKey, 0, REG_TYPE, &hKey);
		if (ERROR_SUCCESS == ret)
		{
			unsigned char dwPathValue[256];
			DWORD dwPathSize = sizeof(dwPathValue);
			if (RegQueryValueEx(hKey, TEXT("JavaHome"), nullptr, &dwType, dwPathValue, &dwPathSize) != ERROR_SUCCESS)
			{
				this->GetDlgItem(IDC_STATIC_JDKVERSION)->SetWindowText(_T("û�в��ҵ�JDK"));
			}
			RegCloseKey(hKey);
			this->GetDlgItem(IDC_BTNBROSWER)->EnableWindow(TRUE);
			this->GetDlgItem(IDC_STATIC_JDKPATH)->SetWindowText((LPCTSTR)dwPathValue);
		}		
	}
	
}


BOOL CJDKConfigDlg::IsWow64()
{
	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = reinterpret_cast<LPFN_ISWOW64PROCESS>(GetProcAddress(GetModuleHandleA("kernel32"), "IsWow64Process"));
	if (NULL != fnIsWow64Process)
	{
		fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
	}
	return bIsWow64;
}

void CJDKConfigDlg::OnBnClickedBtnbroswer()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString JDKPath;
	this->GetDlgItem(IDC_STATIC_JDKPATH)->GetWindowText(JDKPath);
	if (JDKPath == TEXT("û�в��ҵ�JDK"))
	{
		AfxMessageBox(TEXT("û�в��ҵ�JDK·����"));
		return;
	}
	HKEY hKey;
	HKEY root = HKEY_LOCAL_MACHINE;
	CString SubKey = TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment");
	REGSAM REG_TYPE = KEY_ALL_ACCESS;
	if (IsWow64())
	{
		REG_TYPE = REG_TYPE | KEY_WOW64_64KEY;
	}
	long ret = RegOpenKeyEx(root, SubKey, 0, REG_TYPE, &hKey);
	if (ERROR_SUCCESS == ret)
	{
		DWORD dwType;
		CString path;
		unsigned char tmppath[10000];
		DWORD dwSize = sizeof(tmppath);
		RegQueryValueEx(hKey, TEXT("Path"), NULL, &dwType, (LPBYTE)&tmppath, &dwSize);
		path = (LPCTSTR)tmppath;
		path += TEXT(";");
		CString tmpPath = TEXT("");
		while (path.Find(TEXT(";"), 0) != -1)
		{
			if (path.Find(TEXT(";"), 0) == 0)
			{
				path = path.Right(path.GetLength() - 1);
				continue;
			}
			CString tmp = TEXT("");
			tmp = path.Left(path.Find(TEXT(";"), 0));
			if (_taccess_s(tmp, 0) == ENOENT)
			{
				continue;
			}
			tmpPath += (tmp + TEXT(";"));
			path = path.Right(path.GetLength() - tmp.GetLength() -1);
		}

		if (-1 == tmpPath.Find((JDKPath + TEXT("\\bin")), 0))
		{
			tmpPath += (JDKPath + TEXT("\\bin;"));
			RegSetValueEx(hKey, TEXT("Path"), NULL, REG_EXPAND_SZ, (const BYTE*)tmpPath.GetBuffer(), tmpPath.GetLength() * 2);
		}

		CString dwValue;
		dwValue = (TEXT(".;") + JDKPath + TEXT("\\lib\\dt.jar;") + JDKPath + TEXT("\\lib\\tools.jar"));
		RegSetValueEx(hKey, TEXT("CLASSPATH"), NULL, REG_EXPAND_SZ, (const BYTE*)dwValue.GetBuffer(), dwValue.GetLength() * 2);

		RegCloseKey(hKey);
		
		MessageBox(TEXT("���óɹ���ע������������Ч��"),TEXT("��Ϣ"),0 + 64);
	}
}


void CJDKConfigDlg::OnBnClickedBtnexit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CJDKConfigDlg::OnClickedStaticChoosedir()
{
	BROWSEINFO bro;
	::ZeroMemory(&bro, sizeof(BROWSEINFO));
	bro.hwndOwner = this->m_hWnd;
	bro.lpszTitle = TEXT("��ѡ��JDK��·����");
	bro.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON;
	bro.pidlRoot = NULL;
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&bro);
	if (lpidlBrowse != NULL)
	{
		TCHAR szFolderPath[MAX_PATH] = { 0 };
		::SHGetPathFromIDList(lpidlBrowse, szFolderPath);
		CString path = szFolderPath;
		path += TEXT("\\bin");
		if (!PathFileExists(path + TEXT("\\java.exe")))
		{
			MessageBox(TEXT("ѡ����ļ��в���JDKĿ¼���磺C:\\Program Files\\Java\\jdk1.8.0_101��"),TEXT("����"),0+16);
			return;
		}
		DWORD dwSize = GetFileVersionInfoSize(path + TEXT("\\java.exe"), NULL);
		if (dwSize != 0)
		{
			TCHAR *pszAppVersion = new TCHAR[dwSize + 1];
			if (pszAppVersion)
			{
				memset(pszAppVersion, 0, sizeof(TCHAR)*(dwSize + 1));
				GetFileVersionInfo(path + TEXT("\\java.exe"), NULL, dwSize, pszAppVersion);
				CString strVersion;
				UINT nLen(0);
				VS_FIXEDFILEINFO *pFileInfo(NULL);
				VerQueryValue(pszAppVersion, TEXT("\\"), (LPVOID*)&pFileInfo, &nLen);
				if (pFileInfo)
				{
					strVersion.Format(TEXT("1.%d"), HIWORD(pFileInfo->dwFileVersionMS));
					this->GetDlgItem(IDC_STATIC_JDKVERSION)->SetWindowText(strVersion);
					this->GetDlgItem(IDC_STATIC_JDKPATH)->SetWindowText(szFolderPath);
					this->GetDlgItem(IDC_BTNBROSWER)->EnableWindow(TRUE);
				}
			}
		}
	}
}
