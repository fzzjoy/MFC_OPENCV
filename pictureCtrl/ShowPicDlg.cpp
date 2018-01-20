// ShowPicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pictureCtrl.h"
#include "ShowPicDlg.h"
#include "afxdialogex.h"

#define SHOW_TIMER  1

// CShowPicDlg �Ի���

IMPLEMENT_DYNAMIC(CShowPicDlg, CDialogEx)

CShowPicDlg::CShowPicDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CShowPicDlg::IDD, pParent)
    , m_pDC(NULL)
{
}

CShowPicDlg::~CShowPicDlg()
{
    unInit();
}

void CShowPicDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowPicDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_PLAY, &CShowPicDlg::OnBnClickedButtonPlay)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CShowPicDlg::OnBnClickedButtonStop)
    ON_BN_CLICKED(IDOK, &CShowPicDlg::OnBnClickedOk)
    ON_WM_CLOSE()
END_MESSAGE_MAP()

// CShowPicDlg ��Ϣ�������

void CShowPicDlg::OnBnClickedButtonPlay()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    init();
    SetTimer(SHOW_TIMER, 33, NULL);
}

void CShowPicDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    cv::Mat frame;
    m_cvCap >> frame;

    if (!frame.empty())
    {
        IplImage img = IplImage(frame);
        drawPicToHDC(&img);
    }
    else
    {
        OutputDebugString(_T("queryFrame is Null!\n"));
    }

    CDialogEx::OnTimer(nIDEvent);
}

int CShowPicDlg::drawPicToHDC(IplImage *pImg)
{
    if (!pImg)
    {
        OutputDebugString(_T("pImg is NULL!\n"));
        return -1;
    }

    m_bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_bmpInfo.bmiHeader.biHeight = pImg->height;
    m_bmpInfo.bmiHeader.biWidth = pImg->width;
    m_bmpInfo.bmiHeader.biPlanes = 1;
    m_bmpInfo.bmiHeader.biBitCount = 24;
    m_bmpInfo.bmiHeader.biCompression = BI_RGB;
    m_bmpInfo.bmiHeader.biSizeImage = pImg->imageSize;
    m_bmpInfo.bmiHeader.biXPelsPerMeter = 0;
    m_bmpInfo.bmiHeader.biYPelsPerMeter = 0;
    m_bmpInfo.bmiHeader.biClrUsed = 0;
    m_bmpInfo.bmiHeader.biClrImportant = 0;

    // �ú�����������ָ������豸�����е�λͼ����ģʽ
    SetStretchBltMode(m_hDC, COLORONCOLOR);

    ::StretchDIBits(
        m_hDC,
        // Ĭ�ϻ���ԭ��Ϊ���Ͻǣ�X��������Ϊ����Y��������Ϊ��
        // ���ϸ��ű���X����Y����ȡ��
        m_rect.Width(), m_rect.Height(), -m_rect.Width(), -m_rect.Height(),
        0, 0, m_bmpInfo.bmiHeader.biWidth, m_bmpInfo.bmiHeader.biHeight,
        pImg->imageData, (PBITMAPINFO)&m_bmpInfo, DIB_RGB_COLORS, SRCCOPY);

    return 0;
}

void CShowPicDlg::init()
{
    if (!m_cvCap.isOpened())
    {
        m_cvCap = 0; // ������ͷ

        // CDC��MFC��DC��һ����
        m_pDC = GetDlgItem(IDC_IMAGE_SHOW)->GetDC();

        // ��ȡ�豸�����ĵľ��
        m_hDC = m_pDC->GetSafeHdc();

        // ��ȡ��������
        GetDlgItem(IDC_IMAGE_SHOW)->GetClientRect(&m_rect);
    }
}

void CShowPicDlg::OnBnClickedButtonStop()
{
    unInit();
    KillTimer(SHOW_TIMER);
}

BOOL CShowPicDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}

void CShowPicDlg::OnBnClickedOk()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CDialogEx::OnOK();
}

void CShowPicDlg::OnClose()
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    unInit();
    CDialogEx::OnClose();
}

void CShowPicDlg::unInit()
{
    if (m_cvCap.isOpened())
    {
        m_cvCap.release();
        m_cvCap = -1;

        if (m_pDC)
        {
            ReleaseDC(m_pDC);
            m_pDC = NULL;
        }
    }
}
