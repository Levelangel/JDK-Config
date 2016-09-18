
// JDK ConfigDlg.h : 头文件
//

#pragma once

// CJDKConfigDlg 对话框
class CJDKConfigDlg : public CDialogEx
{
// 构造
public:
	CJDKConfigDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JDKCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
