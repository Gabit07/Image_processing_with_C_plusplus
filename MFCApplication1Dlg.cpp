
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString str;
	std::vector<BYTE> pSrcImage;
	std::vector<BYTE> pDstImage;

	int nHeight = 3;
	int nWidth = 4;
	int nTotal = nHeight * nWidth;

	pSrcImage.assign(nTotal, 0);
	pDstImage.assign(nTotal, 0);

	for (size_t i = 0; i < nTotal; i++)
	{
		pSrcImage[i] = i;
	}

	// print 1D image
	fnPrint1DImage(pSrcImage.data(), nHeight, nWidth);

	// rotate 1D image by 90 degree clockwise
	fnRotate1D90CW(pSrcImage.data(), pDstImage.data(), nHeight, nWidth);

	// print rotated 1D image
	fnPrint1DImage(pDstImage.data(), nWidth, nHeight);

	// rotate 1D image by 90 degree counter clockwise
	fnRotate1D90CCW(pSrcImage.data(), pDstImage.data(), nHeight, nWidth);

	// print rotated 1D image
	fnPrint1DImage(pDstImage.data(), nWidth, nHeight);

	std::vector<std::vector<BYTE>> pSrcImage2D;
	std::vector<std::vector<BYTE>> pDstImage2D;
	
	pSrcImage2D.assign(nHeight, std::vector<BYTE>());

	for (size_t i = 0; i < nHeight; i++)
	{
		pSrcImage2D[i].assign(nWidth, 0);
	}

	pDstImage2D.assign(nWidth, std::vector<BYTE>());

	for (size_t i = 0; i < nWidth; i++)
	{
		pDstImage2D[i].assign(nHeight, 0);
	}

	int nHeight2D = pSrcImage2D.size();
	int nWidth2D = pSrcImage2D[0].size();

	// Assigning value

	int n = 0;
	for (size_t i = 0; i < nHeight2D; i++)
	{
		for (size_t j = 0; j < nWidth2D; j++)
		{
			pSrcImage2D[i][j] = n++;
		}
	}

	// rotate 2D image by 90 degree clockwise
	fnRotate2D90CW(pSrcImage2D, pDstImage2D, nHeight, nWidth);

	// print rotated 2D image
	fbPrint2DImage(pDstImage2D, nWidth, nHeight);

	// rotate 2D image by 90 degree counter clockwise
	fnRotate2D90CCW(pSrcImage2D, pDstImage2D, nHeight, nWidth);

	// print rotated 2D image
	fbPrint2DImage(pDstImage2D, nWidth, nHeight);
}

BOOL CMFCApplication1Dlg::fnRotate1D90CW(BYTE* pSrcImg, BYTE* pDstImg, int nHeight, int nWidth)
{
	// rotate 1D image by 90 degree clockwise

	for (size_t i = 0; i < nWidth; i++)
	{
		for (size_t j = 0; j < nHeight; j++)
		{
			pDstImg[i * nHeight + j] = pSrcImg[nWidth * (nHeight - 1 - j) + i];
			// DstImage's width = nHeight and SrcImage's width = nWidth
		}
	}

	return TRUE;
}

BOOL CMFCApplication1Dlg::fnRotate1D90CCW(BYTE* pSrcImg, BYTE* pDstImg, int nHeight, int nWidth)
{
	// rotate 1D image by 90 degree counter clockwise

	for (size_t i = 0; i < nWidth; i++)
	{
		for (size_t j = 0; j < nHeight; j++)
		{
			pDstImg[i * nHeight + j] = pSrcImg[nWidth * j + nHeight - i];
			// DstImage's width = nHeight and SrcImage's width = nWidth
		}
	}

	return TRUE;
}

BOOL CMFCApplication1Dlg::fnRotate2D90CW(std::vector<std::vector<BYTE>> &pSrcImg, std::vector<std::vector<BYTE>>& pDstImg, int nHeight, int nWidth)
{
	// rotate 2D image by 90 degree clockwise

	for (size_t i = 0; i < nWidth; i++)
	{
		for (size_t j = 0; j < nHeight; j++)
		{
			pDstImg[i][j] = pSrcImg[nHeight - 1 - j][i];
		}
	}

	return TRUE;
}

BOOL CMFCApplication1Dlg::fnRotate2D90CCW(std::vector<std::vector<BYTE>>& pSrcImg, std::vector<std::vector<BYTE>>& pDstImg, int nHeight, int nWidth)
{
	// rotate 2D image by 90 degree counter clockwise

	for (size_t i = 0; i < nWidth; i++)
	{
		for (size_t j = 0; j < nHeight; j++)
		{
			pDstImg[i][j] = pSrcImg[j][nHeight - i];
		}
	}
	return TRUE;
}

void CMFCApplication1Dlg::fnPrint1DImage(BYTE* pImg, int nHeight, int nWidth)
{
	CString str;

	for (size_t i = 0; i < nHeight; i++)
	{
		for (size_t j = 0; j < nWidth; j++)
		{
			if (j > 0)
			{
				str.AppendFormat("%d", pImg[i * nWidth + j]);
				if (pImg[i * nWidth + j] / 10 > 0) str.AppendFormat(" ");
				else str.AppendFormat("  ");
			}
			else
			{
				str.Format("%d", pImg[i * nWidth + j]);
				if (pImg[i * nWidth + j] / 10 > 0) str.AppendFormat(" ");
				else str.AppendFormat("  ");
			}
		}
		str.AppendFormat("\n");
		TRACE(str.GetString());
	}

	str.Format("\n");
	TRACE(str.GetString());
}

void CMFCApplication1Dlg::fbPrint2DImage(std::vector<std::vector<BYTE>>& pImg, int nHeight, int nWidth)
{
	CString str;

	for (size_t i = 0; i < nHeight; i++)
	{
		for (size_t j = 0; j < nWidth; j++)
		{
			if (j > 0)
			{
				str.AppendFormat("%d", pImg[i][j]);
				if (pImg[i][j] / 10 > 0) str.AppendFormat(" ");
				else str.AppendFormat("  ");
			}
			else
			{
				str.Format("%d", pImg[i][j]);
				if (pImg[i][j] / 10 > 0) str.AppendFormat(" ");
				else str.AppendFormat("  ");
			}
		}
		str.AppendFormat("\n");
		TRACE(str.GetString());
	}

	str.Format("\n");
	TRACE(str.GetString());
}