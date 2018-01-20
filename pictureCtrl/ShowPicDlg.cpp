// ShowPicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pictureCtrl.h"
#include "ShowPicDlg.h"
#include "afxdialogex.h"

#define SHOW_TIMER  1

// CShowPicDlg 对话框

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

// CShowPicDlg 消息处理程序

void CShowPicDlg::OnBnClickedButtonPlay()
{
    // TODO:  在此添加控件通知处理程序代码
    init();
    SetTimer(SHOW_TIMER, 33, NULL);
}

void CShowPicDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
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

    // 该函数可以设置指定输出设备环境中的位图拉伸模式
    SetStretchBltMode(m_hDC, COLORONCOLOR);

    ::StretchDIBits(
        m_hDC,
        // 默认绘制原点为左上角，X方向向右为正，Y方向向下为正
        // 加上负号表明X或者Y方向取反
        m_rect.Width(), m_rect.Height(), -m_rect.Width(), -m_rect.Height(),
        0, 0, m_bmpInfo.bmiHeader.biWidth, m_bmpInfo.bmiHeader.biHeight,
        pImg->imageData, (PBITMAPINFO)&m_bmpInfo, DIB_RGB_COLORS, SRCCOPY);

    return 0;
}

void CShowPicDlg::init()
{
    if (!m_cvCap.isOpened())
    {
        m_cvCap = 0; // 打开摄像头

        // CDC是MFC的DC的一个类
        m_pDC = GetDlgItem(IDC_IMAGE_SHOW)->GetDC();

        // 获取设备上下文的句柄
        m_hDC = m_pDC->GetSafeHdc();

        // 获取绘制区域
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

    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CShowPicDlg::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialogEx::OnOK();
}

void CShowPicDlg::OnClose()
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
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
