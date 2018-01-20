
// pictureCtrlDlg.h : 头文件
//

#pragma once

#include "ShowPicDlg.h"

// CpictureCtrlDlg 对话框
class CpictureCtrlDlg : public CDialogEx
{
// 构造
public:

	CpictureCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数
    ~CpictureCtrlDlg();


// 对话框数据
	enum { IDD = IDD_PICTURECTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
    CShowPicDlg             *m_picDlgPtr;
public:
    afx_msg void OnBnClickedCameraCapture();
    afx_msg void OnClose();
};
