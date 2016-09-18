
// JDK ConfigDlg.h : ͷ�ļ�
//

#pragma once

// CJDKConfigDlg �Ի���
class CJDKConfigDlg : public CDialogEx
{
// ����
public:
	CJDKConfigDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JDKCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void OnOK() override;
	void OnCancel() override;
	afx_msg void OnClose();
	void GetJavaVersion();
	BOOL IsWow64();
	afx_msg void OnBnClickedBtnbroswer();
	afx_msg void OnBnClickedBtnexit();
	afx_msg void OnClickedStaticChoosedir();
	CString getPath();
};
