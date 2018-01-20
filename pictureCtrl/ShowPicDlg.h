#pragma once

#include "opencv2\opencv.hpp"
#include "opencv\cv.h"

// CShowPicDlg �Ի���

class CShowPicDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CShowPicDlg)

public:
    CShowPicDlg(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CShowPicDlg();

    // �Ի�������
    enum { IDD = IDD_DIALOG_SHOWPICTURE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonPlay();

private:
    void init();
    void unInit();
    int drawPicToHDC(IplImage *pImg);

    cv::VideoCapture    m_cvCap;
    BITMAPINFO          m_bmpInfo;
    CDC                 m_memDC;
    CDC                 *m_pDC;
    HDC                 m_hDC;
    CBitmap             m_bmp;
    CRect               m_rect;
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedButtonStop();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnClose();
};
