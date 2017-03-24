// font_drawDlg.h : header file
//

#if !defined(AFX_FONT_DRAWDLG_H__E1E0BB40_A61F_46FF_85FB_B26CB224419E__INCLUDED_)
#define AFX_FONT_DRAWDLG_H__E1E0BB40_A61F_46FF_85FB_B26CB224419E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

#define POINTS_ON_CURVE 100	//曲线绘制等分次数

//定义字体格式
#define  ONE_BEZIER		1
#define  TWO_BEZIER		2
#define  THREE_BEZIER	3
/////////////////////////////////////////////////////////////////////////////
// CFont_drawDlg dialog
int CALLBACK MyEnumFontProc(ENUMLOGFONTEX* lpelf,NEWTEXTMETRICEX* lpntm,DWORD nFontType,long lParam);


class CFont_drawDlg : public CDialog
{
// Construction
public:
	CFont_drawDlg(CWnd* pParent = NULL);	// standard constructor
	~CFont_drawDlg();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFont_drawDlg)
	enum { IDD = IDD_FONT_DRAW_DIALOG };
	CStatic	m_draw_bmp;
	CSpinButtonCtrl	m_spinSize;
	CListBox	m_ctrlFontList;
	CEdit	m_edSize;
	CEdit	m_edFace;
	CStatic	m_DrawPicture;
	CString	m_changeSize;
	CString	m_Input_Word;
	CString	m_strFontName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFont_drawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFont_drawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdSize();
	afx_msg void OnChangeInput();
	afx_msg void OnCreatFont();
	afx_msg void OnDeltaposSpinSize(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeLfonts();
	afx_msg void OnSaveBmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void fill_font_list(void);
	void data_init(void);
	int  ChangeFontSize(int newsize);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void display_draw(void);
	double Fixed2Double(FIXED Fxd);
	FIXED Double2Fixed(double Dbl);
	BOOL  one_Bezier(CDC *pDC, const POINT* lpPoints, int nCount);
	BOOL  second_Bezier(CDC *pDC, const POINT* lpPoints, int nCount);
	BOOL  three_Bezier(CDC *pDC,const POINT* lpPoints, int nCount);
	int   MakeQuadratic(POINT **lpPoints,POINTFX StartPoint,TTPOLYCURVE *Curve,TEXTMETRIC &TextMetric,POINT Origin);
	void  DrawCurve(CDC *pDC, BYTE *pBuffer, int BufferLength, GLYPHMETRICS gm, POINT Origin,char* szText);
	void  DrawContour(CDC *pDC,int X, int Y,char* theChar);
	BOOL  CFont_drawDlg::second_Bezier_1(CDC *pDC,POINTFX StartPoint,TTPOLYCURVE *Curve,TEXTMETRIC &TextMetric,POINT Origin);
	string int_to_string(int n);
	POINT  GetPoint(POINTFX fx, TEXTMETRIC &TextMetric, POINT Origin);
	void save_file_txt(char* szText,vector<POINT>lpPoints, int nCount);
	void save_file_txt1(vector<POINT>&lpPoints,string str);
	void CFont_drawDlg::three_para(CDC *pDC,POINTFX StartPoint,TTPOLYCURVE *Curve,TEXTMETRIC &TextMetric,POINT Origin);

	SYSTEMTIME st;			//系统时间

public:
	int		font_Angle;
	int		font_Bold;
	BOOL	font_Italic;
	int		font_size;
	const char* file_name;	//文件路径
	double		change_font_size;

	CPen  m_Pen_Line;		//直线画笔
	CPen  m_Pen_Bezier;		//贝塞尔曲线
	CPen  m_Pen_Close;
	CFont m_Font;			//字体

	int save_num;
	bool save_once;

	int m_intBits;//位图大小
	bool m_save_bmp;
	LPBITMAPINFO pbmpinfo;
	LPBITMAPFILEHEADER pfileinfo;
	void FormBitmapInfo(int nWidth, int nHeight, int nBits);
	void FormFileHeader(int nWidth, int nHeight,int nBits);
	void DrawCurve_bmp(CDC *pDC,BYTE * pBuf);//绘制bmp字体
	void display_draw_bmp(void);
	int charLineW;

	int m_intPixX;
	int m_intPixY;

	BYTE *pBuffer;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONT_DRAWDLG_H__E1E0BB40_A61F_46FF_85FB_B26CB224419E__INCLUDED_)
