
// pictureCtrlDlg.h : ͷ�ļ�
//

#pragma once

#include "ShowPicDlg.h"

// CpictureCtrlDlg �Ի���
class CpictureCtrlDlg : public CDialogEx
{
// ����
public:

	CpictureCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��
    ~CpictureCtrlDlg();


// �Ի�������
	enum { IDD = IDD_PICTURECTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
