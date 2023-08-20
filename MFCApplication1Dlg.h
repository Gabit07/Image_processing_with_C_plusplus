
// MFCApplication1Dlg.h : header file
//

#pragma once
#include <vector>
#include <numeric>

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	BOOL fnRotate1D90CW(BYTE* pSrcImg, BYTE* pDstImg, int nHeight, int nWidth);
	BOOL fnRotate1D90CCW(BYTE* pSrcImg, BYTE* pDstImg, int nHeight, int nWidth);
	BOOL fnRotate2D90CW(std::vector<std::vector<BYTE>>& pSrcImg, std::vector<std::vector<BYTE>>& pDstImg, int nHeight, int nWidth);
	BOOL fnRotate2D90CCW(std::vector<std::vector<BYTE>>& pSrcImg, std::vector<std::vector<BYTE>>& pDstImg, int nHeight, int nWidth);
	void fnPrint1DImage(BYTE* pImg, int nHeight, int nWidth);
	void fbPrint2DImage(std::vector<std::vector<BYTE>>& pImg, int nHeight, int nWidth);
};
