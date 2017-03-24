// font_drawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "font_draw.h"
#include "font_drawDlg.h"
#include <iomanip> //�õ���ʽ���Ʒ�
#include <fstream>
#include <sstream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

int BITSTABLE[] = {2,5,17,65};

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFont_drawDlg dialog

CFont_drawDlg::CFont_drawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFont_drawDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFont_drawDlg)
	m_changeSize = _T("");
	m_Input_Word = _T("");
	m_strFontName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFont_drawDlg::~CFont_drawDlg()
{
	//����
	if (pBuffer!=NULL)
	{
		delete[] pBuffer;
		pBuffer = NULL;
	}
	if(pbmpinfo!=NULL)	
	{
		delete []pbmpinfo;
		pbmpinfo = NULL;
	}
	if(pfileinfo!=NULL)	
	{
		delete []pfileinfo;
		pfileinfo = NULL;
	}
}

void CFont_drawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFont_drawDlg)
	DDX_Control(pDX, IDC_Draw_BMP, m_draw_bmp);
	DDX_Control(pDX, IDC_SPIN_SIZE, m_spinSize);
	DDX_Control(pDX, IDC_LFONTS, m_ctrlFontList);
	DDX_Control(pDX, IDC_ED_SIZE, m_edSize);
	DDX_Control(pDX, IDC_ED_FACE, m_edFace);
	DDX_Control(pDX, IDC_Draw_Picture, m_DrawPicture);
	DDX_Text(pDX, IDC_ED_SIZE, m_changeSize);
	DDX_Text(pDX, IDC_Input, m_Input_Word);
	DDX_LBString(pDX, IDC_LFONTS, m_strFontName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFont_drawDlg, CDialog)
	//{{AFX_MSG_MAP(CFont_drawDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ED_SIZE, OnChangeEdSize)
	ON_EN_CHANGE(IDC_Input, OnChangeInput)
	ON_BN_CLICKED(IDC_CREAT_FONT, OnCreatFont)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIZE, OnDeltaposSpinSize)
	ON_LBN_SELCHANGE(IDC_LFONTS, OnSelchangeLfonts)
	ON_BN_CLICKED(IDC_Save_Bmp, OnSaveBmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFont_drawDlg message handlers

BOOL CFont_drawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	data_init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFont_drawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFont_drawDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}


void CFont_drawDlg::data_init(void)
{
	SetWindowText("����������ȡ����ģ��");	//���ô��ڱ���
	fill_font_list();	//��������б�

	m_edFace.SetWindowText(m_strFontName);	//������ʾ����

	//���������С
	font_size = 1200;
	font_Angle = 0;			//��ת�Ƕ�
	font_Bold = 400;		//FW_NORMAL ��׼����
	font_Italic = FALSE;	//����б

	//���������С
	char prompt[20];
	sprintf(prompt,"%d",font_size/10);
	m_edSize.SetWindowText(prompt);

	change_font_size = font_size/10;
	
	m_spinSize.SetBuddy(&m_edSize);
	m_spinSize.SetRange(20,235);
	
	//���ʳ�ʼ��
	m_Pen_Line.CreatePen(PS_SOLID,1,RGB(254,67,101));  // red
	m_Pen_Close.CreatePen(PS_SOLID,1,RGB(222,125,44)); // green
	m_Pen_Bezier.CreatePen(PS_SOLID,1,RGB(131,175,155));// blue
	
	m_Input_Word = "T";

	save_num = 0;
	save_once = false;

	m_intBits = 1;	//Ĭ��
	m_save_bmp = false;
	pbmpinfo = NULL;
	pfileinfo = NULL;
	charLineW = 0;
	m_intPixX = 0;
	m_intPixY = 0;

	pBuffer = NULL;

	
}

//�ص�����ʹ��ϵͳ����
int CALLBACK MyEnumFontProc(ENUMLOGFONTEX* lpelf,NEWTEXTMETRICEX* lpntm,DWORD nFontType,long lParam)
{
	CFont_drawDlg* pWnd=(CFont_drawDlg*) lParam;
	if(pWnd)
	{
		pWnd->m_ctrlFontList.AddString(lpelf->elfLogFont.lfFaceName);
		return 1;
	}
	return 0;
}

//���ϵͳ���嵽�б���
void CFont_drawDlg::fill_font_list(void)//�б����
{
	int iCurCount;
	CString strCurFont;
	CString strPrevFont="";
	LOGFONT lf;
	
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfFaceName[0]=NULL;
	lf.lfPitchAndFamily=0;
	m_ctrlFontList.ResetContent();
	CClientDC dc(this);
	::EnumFontFamiliesEx((HDC) dc,&lf,(FONTENUMPROC) MyEnumFontProc,(LPARAM) this,0);
	
	for (iCurCount = m_ctrlFontList.GetCount(); iCurCount > 0; iCurCount--)
	{
		m_ctrlFontList.GetText((iCurCount-1),strCurFont);
		if (strCurFont==strPrevFont)
		{
			m_ctrlFontList.DeleteString((iCurCount-1));
		}
		else
		{
			strPrevFont = strCurFont;
		}
	}
	
	m_ctrlFontList.SetCurSel(0);
	TRACE("the total is %d\n",m_ctrlFontList.GetCount());
	m_ctrlFontList.GetText(m_ctrlFontList.GetCurSel(),m_strFontName);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFont_drawDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//��������
void CFont_drawDlg::display_draw(void)
{
	
	CDC *pDC = m_DrawPicture.GetDC();	//��ȡ�������豸
	m_DrawPicture.Invalidate(FALSE);	//���ڵĿͻ�����Ч��ζ����Ҫ�ػ棬���������ػ�
	m_DrawPicture.UpdateWindow();	//ʹ���������ػ�

	char theChar[40];
	
	if (m_Input_Word == "")
	{
		m_Input_Word = "T";
	}
	strcpy(theChar,m_Input_Word);
	
	int PixY = pDC->GetDeviceCaps(LOGPIXELSY);	//�����СΪ����
	m_Font.CreatePointFont(int((font_size/72.0)*PixY), m_strFontName);

	//m_Font.CreatePointFont(font_size, m_strFontName);
	
	HFONT hfontold=(HFONT) pDC->SelectObject(m_Font);//���壬220��С	
	
	save_num++;
	
	DrawContour(pDC,0,0,theChar);//��ͼ����������

	pDC->SelectObject(hfontold);	
	DeleteObject(m_Font);
	m_Font.Detach();
	ReleaseDC(pDC);

}

//��BMP
void CFont_drawDlg::display_draw_bmp(void)
{
	CDC *pDC_bmp = m_draw_bmp.GetDC();	//��ȡ�������豸
	m_draw_bmp.Invalidate(FALSE);	//���ڵĿͻ�����Ч��ζ����Ҫ�ػ棬���������ػ�
	m_draw_bmp.UpdateWindow();	//ʹ���������ػ�

	char theChar[40];
	
	if (m_Input_Word == "")
	{
		m_Input_Word = "T";
	}
	strcpy(theChar,m_Input_Word);
	
	int PixY = pDC_bmp->GetDeviceCaps(LOGPIXELSY);	//�����СΪ����
	m_Font.CreatePointFont(int((font_size/72.0)*PixY), m_strFontName);
	
	HFONT hfontold_bmp=(HFONT) pDC_bmp->SelectObject(m_Font);//���壬220��С	

	DrawContour(pDC_bmp,0,0,theChar);//��ͼ����������

	pDC_bmp->SelectObject(hfontold_bmp);	
	DeleteObject(m_Font);
	m_Font.Detach();
	ReleaseDC(pDC_bmp);


}
//��������
void CFont_drawDlg::DrawContour(CDC *pDC,int X, int Y,char* theChar)
{
	GLYPHMETRICS gm;	//�洢��������λ�ýṹ
	MAT2 mat1;
	///����MAT 2*2����
	mat1.eM11 = Double2Fixed(1);//�̶���ת��
	mat1.eM12 = Double2Fixed(0);
	mat1.eM21 = Double2Fixed(0);
	mat1.eM22 = Double2Fixed(-1);

	MAT2 mat2={0,1,0,0,0,0,0,1};

	POINT Origin={X,Y};
	
	// Copy the string
	
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, theChar, -1, NULL, 0 );
	
	WCHAR *szText = new wchar_t[40];
	
	MultiByteToWideChar(CP_ACP, 0, theChar, -1, (LPWSTR) szText, 40);//���ַ���ת��Ϊ���ַ�
	
	DWORD ERR = GetLastError();
	
	int y_new_width = 0, y_last_width = 0, y_width = 0;
	double count_char = 0.0;
	//ÿ���������д�ĸ��֣������Ӣ�ľ���8��
	DWORD BufferLen, Result;
	for (int i = 0; i < nLen-1; i++)	
	{
		if (m_save_bmp == true)	//λͼ��ʽ
		{
			BYTE temp;
			UINT chartemp;
			temp = m_Input_Word.GetAt(0);
			if(temp>=128)
			{
				chartemp = ((UINT)temp) << 8;
				temp = m_Input_Word.GetAt(1);
				chartemp += temp;
			}
			else
			{
				chartemp=temp;
			}
			BufferLen = ::GetGlyphOutline(pDC->m_hDC,chartemp,m_intBits,&gm,0,NULL,&mat2);

			if((BufferLen > 0) && (BufferLen != GDI_ERROR)) // 0xFFFFFFFFL  ��������
			{
				if (pBuffer!=NULL)
				{
					delete[] pBuffer;
					pBuffer = NULL;
				}
				pBuffer = new BYTE[BufferLen];	//ʵ�ʵ��ַ��ռ�
				Result = ::GetGlyphOutline(pDC->m_hDC,chartemp,m_intBits,&gm,BufferLen,pBuffer,&mat2);

				charLineW = (gm.gmBlackBoxX/32 + (gm.gmBlackBoxX%32==0?0:1)) *4;

				FormBitmapInfo(gm.gmBlackBoxX, gm.gmBlackBoxY, m_intBits);

				m_intPixX = gm.gmBlackBoxX;
				m_intPixY = gm.gmBlackBoxY;

				DrawCurve_bmp(pDC,pBuffer);	//����bmp����


			}

			m_save_bmp = false;

		}
		else
		{
			BufferLen = ::GetGlyphOutlineW(pDC->m_hDC,szText[i],GGO_NATIVE,&gm, 0, NULL, &mat1);
			
			ERR = GetLastError();
			
			if((BufferLen > 0) && (BufferLen != GDI_ERROR)) // 0xFFFFFFFFL  ��������
			{
				if (pBuffer!=NULL)
				{
					delete[] pBuffer;
					pBuffer = NULL;
				}
				pBuffer = new BYTE[BufferLen];	//ʵ�ʵ��ַ��ռ�
				Result = ::GetGlyphOutlineW(pDC->m_hDC, szText[i], GGO_NATIVE, &gm, BufferLen, pBuffer, &mat1);
				//gm�к����������е�������Ϣ
				DrawCurve(pDC, pBuffer, BufferLen, gm, Origin, theChar);
				if (szText[i] > 127)//��ʾ����
				{
					count_char++; //����ַ�����
				}
				else	//��ʾӢ��aasd
				{
					count_char += 0.5;
				}
				
				if (count_char > 4.0)	//д���ĸ��ַ�������
				{
					y_width +=  y_new_width;
					Origin.x = 0;
					Origin.y = y_width;
					count_char = 0.0;
				}
				else
				{
					Origin.x += gm.gmCellIncX;
					Origin.y += gm.gmCellIncY;
					y_last_width = gm.gmBlackBoxY + 10;
					if (y_last_width > y_new_width)
					{
						y_new_width = y_last_width;
					}
				}
			}
		}
			
	}

}


void CFont_drawDlg::DrawCurve_bmp(CDC *pDC, BYTE * pBuf)	// ����bmpͼƬ
{

	CRect rect;
	this->GetDlgItem(IDC_Draw_BMP)->GetWindowRect(&rect);

	CDC memdc;
	memdc.CreateCompatibleDC(pDC);

	CBitmap nbitmap,*poldbitmap;

	nbitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());

	poldbitmap=memdc.SelectObject(&nbitmap);

	memdc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	::StretchDIBits(memdc.m_hDC, 0, 0, m_intPixX, m_intPixY, 0, 0, m_intPixX, m_intPixY,  pBuf, pbmpinfo,DIB_RGB_COLORS,SRCCOPY);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);

	memdc.DeleteDC();

}
//��������
void CFont_drawDlg::DrawCurve(CDC *pDC, BYTE *pBuf, int BufferLength, GLYPHMETRICS gm, POINT Origin,char* theChar)
{
	TEXTMETRIC TextMetric;
	pDC->GetTextMetrics(&TextMetric);//GetTextMetrics�ѳ���ǰ��������Ϣ����ŵ�TEXTMETRIC����MSDNԭ���е�specified buffer���С�
 
	int point_num = 0;
	

	while(BufferLength>0)			//���Ѿ�ȡ��������Ϣ
	{
		TTPOLYGONHEADER* Header = (TTPOLYGONHEADER*)pBuf;	//ָ���ַ�������Ϣ�����
		int Remain				= Header->cb - sizeof(TTPOLYGONHEADER);		//cb�����ַ��ֽ�����1��TTPOLYGONHEADER ������TTPOLYCURVE�ֽںͣ�,ȥ��ͷ��ʣ�������ֽ���
		BYTE *Start				= pBuf + sizeof(TTPOLYGONHEADER);		//ָ����������㣬ָ��ͷ+header��С
		POINTFX StartPoint		= Header->pfxStart;							//pfxStartָ���ַ��������λ����Ϣ
		POINTFX InitPoint		= StartPoint;
		
		while (Remain) //һ������������ֽ���
		{
			TTPOLYCURVE* Curve = (TTPOLYCURVE*)Start;//ָ�����������
			switch(Curve->wType)	//wType��ʾ�洢����������
			{
			case TT_PRIM_LINE://1.ֱ�ߣ�һ�α���������
				{
					int PointCount = Curve->cpfx + 1;
					POINT* Points = new POINT[PointCount]; //����pointfx����
					vector<POINT> point_vector;

					Points[0] = GetPoint(StartPoint, TextMetric, Origin);//���λ����Ϣ��������Ϣ����ǰ���壬����ԭ��
					point_vector.push_back(Points[0]);
					for(int i = 0; i< Curve->cpfx; i++)
					{
						Points[i + 1] = GetPoint(Curve->apfx[i], TextMetric, Origin);	//��ȡ���Ƶ������

						point_vector.push_back(Points[i + 1]);
					}
					point_num +=  PointCount;
	
					pDC->SelectObject(&m_Pen_Line);		// red����	
					
					//�����߶�
					pDC->Polyline(Points,PointCount);//�õ�ǰ�������һϵ���߶Ρ�ʹ��PolylineTo����ʱ����ǰλ�û���Ϊ���һ���߶ε��յ�
					
					save_file_txt1(point_vector,"1");	//̧��
					//save_file_txt(theChar,point_vector,point_num);

					StartPoint = Curve->apfx[Curve->cpfx - 1];

					delete[] Points;
					vector <POINT>().swap(point_vector);  //������������տռ�

					break;
				}
			case TT_PRIM_QSPLINE://2.���α���������
				{				
#ifdef Debug
	POINT* Points;

	int PointCount = MakeQuadratic(&Points, StartPoint, Curve, TextMetric, Origin);		//����������������

	pDC->SelectObject(&m_Pen_Bezier);// blue

	second_Bezier(pDC,Points,PointCount);

	point_num +=  PointCount;
	for (int i = 0; i < PointCount; i++)
	{
		point_vector.push_back(Points[i]);
	}
	temp_point.x = 20000;
	temp_point.y = PointCount;
	point_vector.push_back(temp_point);
	delete[] Points;

	pDC->SelectObject(&m_Pen_Bezier);// blue
	three_para(pDC, StartPoint, Curve, TextMetric, Origin);
#endif 
					pDC->SelectObject(&m_Pen_Bezier);// blue
					second_Bezier_1(pDC, StartPoint, Curve, TextMetric, Origin);
					StartPoint = Curve->apfx[Curve->cpfx - 1];
					break;
				}
				
			case TT_PRIM_CSPLINE://3.���α���������
				{
					int PointCount = Curve->cpfx + 1;
					POINT* Points = new POINT[PointCount];
					Points[0]=GetPoint(StartPoint, TextMetric, Origin);
					
					for(int i = 0; i< Curve->cpfx; i++)
					{
						Points[i + 1] = GetPoint(Curve->apfx[i], TextMetric, Origin);
					}
					//
					pDC->SelectObject(&m_Pen_Line);// blue
					pDC->Polyline(Points, PointCount);


					delete[] Points;
					break;
				}
			}// end switch(Curve->wType)
			
			Start  += sizeof(TTPOLYCURVE) + (Curve->cpfx-1)*sizeof(POINTFX);
			Remain -= sizeof(TTPOLYCURVE) + (Curve->cpfx-1)*sizeof(POINTFX);
		}// end while(Remain>0)
		

		if( (StartPoint.x.value != InitPoint.x.value) || 
			(StartPoint.x.fract != InitPoint.x.fract) || 
			(StartPoint.y.value != InitPoint.y.value) || 
			(StartPoint.y.fract != InitPoint.y.fract) )
		{
			POINT P1=GetPoint(StartPoint, TextMetric, Origin);
			POINT P2=GetPoint(InitPoint, TextMetric, Origin);
			//
			pDC->SelectObject(&m_Pen_Line);// green
			pDC->MoveTo(P1.x,P1.y);
			pDC->LineTo(P2.x,P2.y);
			vector<POINT> point_vector;
			point_vector.push_back(P1);
			point_vector.push_back(P2);

			save_file_txt1(point_vector,"2");//̧��
			vector <POINT>().swap(point_vector);  //������������տռ�

		}
		InitPoint=StartPoint;
		pBuf += Header->cb;
		BufferLength -= Header->cb;
	}
		
	//̧��

}

//TEXTMETRIC�洢װ������ṹ��Ϣ��ȡ��gm�е��ַ���Ϣ����Ҫ��λ����Ϣ
POINT CFont_drawDlg::GetPoint(POINTFX fx, TEXTMETRIC &TextMetric, POINT Origin)
{
	// Y is 'Ascent' higher than highest-point, i.e the distance btw. 'Top' and 'Baseline'
	POINT Result;
	
	Result.x = (int)Fixed2Double(fx.x) + Origin.x;
	Result.y = (int)Fixed2Double(fx.y) + Origin.y + TextMetric.tmAscent;//tmAscent �ַ��ϲ��߶�(��������)
	
	
	return Result;
}

//���������������Σ�ʹ�ö��α��������߻���
int CFont_drawDlg::MakeQuadratic(POINT **lpPoints,POINTFX StartPoint,TTPOLYCURVE *Curve,TEXTMETRIC &TextMetric,POINT Origin) 
{
	int point_count = 2 * Curve->cpfx - 1; //�������������Σ�����ÿ������֮����Ҫ����һ���м��ԭ����Ҫ 2 * n - 1    �� ��n- 1��*2 + 1
	
	POINT *bezier_point = new POINT[point_count];	//�����洢��������
	
	//�洢��һ����StartPoint
	POINT temp_p = GetPoint(StartPoint, TextMetric, Origin);
	
	bezier_point[0] = temp_p;
	
	POINT A, M, B;	//M = A + (B - A) / 2	��MΪ�м��
	int current_point = 1;
	
	for(int i = 0; i < Curve->cpfx;)
	{
		A = GetPoint(Curve->apfx[i++], TextMetric, Origin);
		// i==1
		if(i == (Curve->cpfx - 1))
		{// last
			B = GetPoint(Curve->apfx[i++], TextMetric, Origin);
			
			bezier_point[current_point+0]=A;
			
			bezier_point[current_point+1]=B;
		}
		else
		{//
			B=GetPoint(Curve->apfx[i], TextMetric, Origin);
			// insert M = A + (B �C A)/2
			bezier_point[current_point+0]=A;
			
			M.x=A.x+(B.x-A.x)/2;
			
			M.y=A.y+(B.y-A.y)/2;
			
			bezier_point[current_point+1]=M;
		}
		current_point += 2;// 1,4,...
		
	}
	
	
	//��������
	*lpPoints = bezier_point;
	
	//���ر��������ߵ���
	return point_count;
}


//һ�ױ��������ߣ���ֱ�߻���
BOOL  CFont_drawDlg::one_Bezier(CDC *pDC, const POINT* lpPoints, int nCount)
{
	double  t;
	double  dt = (double)(1) / POINTS_ON_CURVE;	//40�ȷ�
	CPoint  pt;

	//һ�ױ�������ʽ�� B(t) = (1-t)*P0 + t*P1		0 < t < 1
	for(int i = 0 ; i < nCount - 2 ; i += 2)
	{
		if(i == 0)
		{
			// �������	
			pDC->MoveTo(lpPoints[0]);
		}
		for(t = 0.0 ; t < 1.0 + dt; t += dt)
		{
			// 3 points each,cubic Bezier curve.
			pt.x = (long)(((1-t) * lpPoints[0+i].x) + (t * lpPoints[1 + i].x));

			pt.y = (long)(((1-t) * lpPoints[0+i].y) + (t * lpPoints[1 + i].y));

			pDC->LineTo(pt);

		}
	}

	return TRUE;
}

//���ױ��������߻���
BOOL  CFont_drawDlg::second_Bezier(CDC *pDC, const POINT* lpPoints, int nCount)
{
	double  t;
	double  dt = (double)(1) / POINTS_ON_CURVE;	//40�ȷ�
	CPoint  pt;
	int     i;

	//���ױ�������ʽ�� B(t) = P0*(1-t)^2 + 2*P1*t*(1-t) + P2*t^2		0 < t < 1
	for(i = 0 ; i < nCount - 2 ; i += 2)
	{
		if(i == 0)
		{
			// �������	
			pDC->MoveTo(lpPoints[0]);
		}
		for(t = 0.0 ;t < 1.0 + dt ;t += dt)
		{
			// 3 points each,cubic Bezier curve.
			pt.x = (long)((1 - t) * (1 - t) * lpPoints[0 + i].x  + 2 * t * (1-t) * lpPoints[1 + i].x + t * t * lpPoints[2 + i].x);

			pt.y = (long)((1 - t) * (1 - t) * lpPoints[0 + i].y  + 2 * t * (1-t) * lpPoints[1 + i].y + t * t * lpPoints[2 + i].y );

			pDC->LineTo(pt);

		}
	}
	
	return TRUE;
}


//���ױ��������߻���
BOOL  CFont_drawDlg::second_Bezier_1(CDC *pDC,POINTFX StartPoint,TTPOLYCURVE *Curve,TEXTMETRIC &TextMetric,POINT Origin)
{
	int point_count = Curve->cpfx ; 
	
	vector<POINT> bezier_point;//�����洢��������
	
	POINT temp_p = GetPoint(StartPoint, TextMetric, Origin);	//��һ����
	POINT A,B,C;

	bezier_point.push_back(temp_p);
	A = temp_p;

	pDC->MoveTo(bezier_point.at(0));
	for(int j = 0; j < point_count - 1; j++)
	{
		B = GetPoint(Curve->apfx[j], TextMetric, Origin);
		//��B����ֻ��1���㣬����C������ȡ�����յ�
		if((point_count - j) == 2)
		{
			C = GetPoint(Curve->apfx[j+1], TextMetric, Origin);
		}
		else
		{
			temp_p = GetPoint(Curve->apfx[j+1], TextMetric, Origin);
			C.x =	(B.x + temp_p.x)/2;
			C.y =	(B.y + temp_p.y)/2;
		}
		//A.B.C����ȷ��һ��������
		double t =0.0;
		const float Chord = 0.5;//�趨����
		while (t < 1)
		{
			temp_p.x = (A.x-2*B.x+C.x)*t*t + 2*(B.x-A.x)*t +A.x;	
			temp_p.y = (A.y-2*B.y+C.y)*t*t + 2*(B.y-A.y)*t +A.y;
			
			t += 0.5*Chord/( 	sqrt(pow(t*(A.x-2*B.x+C.x)+(B.x-A.x),2) + 
								pow(t*(A.y-2*B.y+C.y)+(B.y-A.y),2))
							);
			
			pDC->LineTo(temp_p);

			bezier_point.push_back(temp_p);			
		}
		
		A = C;
	}
	
	save_file_txt1(bezier_point,"3");
	//save_file_txt("",bezier_point,bezier_point.size());

	vector <POINT>().swap(bezier_point);  //������������տռ�

	return TRUE;
}
//���ױ��������߻���
BOOL  CFont_drawDlg::three_Bezier(CDC *pDC,const POINT* lpPoints, int nCount)
{
	// lpPoints contains all points. each 4 points make a cubic Bezier curve.
	double  t;
	double  dt = (double)(1) / POINTS_ON_CURVE;
	CPoint  pt;
	
	//���ױ�������ʽ�� B(t) = P0*(1-t)^3 + 3*P1*T*(1-t)^2 + 3*P2*t^2*(1-t)+ P3*t^3		0 < t < 1
	for(int i=0 ; i < nCount - 3 ; i += 3)
	{
		if(i == 0)
		{
			// only 1 start point need to be set !	
			pDC->MoveTo(lpPoints[0]);
		}
		for(t = 0.0; t < 1.0 + dt; t += dt)
		{
			// 4 points each,cubic Bezier curve.
			pt.x = (long)((1 - t) * (1 - t) * (1 - t) * lpPoints[0 + i].x +3 * t * (1-t) * (1-t) * lpPoints[1+i].x + 3 * t * t * (1 - t) * lpPoints[2 + i].x + t * t * t * lpPoints[3 + i].x);
			
			pt.y = (long)((1 - t) * (1 - t) * (1 - t) * lpPoints[0 + i].y +3 * t * (1-t) * (1-t) * lpPoints[1+i].y + 3 * t * t * (1 - t) * lpPoints[2 + i].y + t * t * t * lpPoints[3 + i].y);
			
			pDC->LineTo(pt);
			
		}
	}
	return TRUE;
}


//������������߷���
void CFont_drawDlg::three_para(CDC *pDC,POINTFX StartPoint,TTPOLYCURVE *Curve,TEXTMETRIC &TextMetric,POINT Origin)
{
	int point_count = Curve->cpfx ; 
	
	POINT *bezier_point = new POINT[point_count];	//�����洢��������

	double  dt = (double)(1) / POINTS_ON_CURVE;

	CPoint  pt;

	POINT temp_p = GetPoint(StartPoint, TextMetric, Origin);
	
	bezier_point[0] = temp_p;

	for (int i = 1; i < point_count; i++)	//������
	{
		bezier_point[i]	= GetPoint(Curve->apfx[i], TextMetric, Origin);
	}

	if (point_count == 3)	//2�α�����
	{		
		pDC->MoveTo(bezier_point[0]);
		
		for (double t = 0.0; t < 1 + dt; t= t + dt)
		{
			pt.x = (long)((1 -3*t + 2*t*t) * bezier_point[0].x + (4*t -4*t*t) * bezier_point[1].x + (2*t*t - t)* bezier_point[2].x);
			pt.y = (long)((1 -3*t + 2*t*t) * bezier_point[0].y + (4*t -4*t*t) * bezier_point[1].y + (2*t*t - t)* bezier_point[2].y);
			pDC->LineTo(pt);
		}
	}
	else if (point_count == 4)	//���α�����
	{		
		pDC->MoveTo(bezier_point[0]);
		
		for (double t = 0.0; t < 1 + dt; t= t + dt)
		{
			pt.x = (long)((1 -3*t + 2*t*t) * bezier_point[0].x + (4*t -4*t*t) * bezier_point[1].x + (2*t*t - t)* bezier_point[2].x);
			pt.y = (long)((1 -3*t + 2*t*t) * bezier_point[0].y + (4*t -4*t*t) * bezier_point[1].y + (2*t*t - t)* bezier_point[2].y);
			pDC->LineTo(pt);
		}
	}


	

	
}


void CFont_drawDlg::FormBitmapInfo(int nWidth, int nHeight, int nBits)
{
	if(pbmpinfo != NULL)
		delete []pbmpinfo;
	pbmpinfo = (LPBITMAPINFO)(new BYTE[sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*BITSTABLE[nBits-1]]);
	pbmpinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmpinfo->bmiHeader.biWidth = nWidth;
	pbmpinfo->bmiHeader.biHeight = -nHeight;
	pbmpinfo->bmiHeader.biPlanes = 1;
	pbmpinfo->bmiHeader.biBitCount = (nBits==1?1:8);
	pbmpinfo->bmiHeader.biCompression = BI_RGB;
	pbmpinfo->bmiHeader.biSizeImage = 0;
	pbmpinfo->bmiHeader.biXPelsPerMeter = 0;
	pbmpinfo->bmiHeader.biYPelsPerMeter = 0;
	pbmpinfo->bmiHeader.biClrUsed = BITSTABLE[nBits-1];
	pbmpinfo->bmiHeader.biClrImportant = BITSTABLE[nBits-1];
	RGBQUAD* pquad = (new RGBQUAD[BITSTABLE[nBits-1]]);
	if(nBits == 1)
	{
		(*pquad).rgbRed=0;
		(*pquad).rgbGreen=0;
		(*pquad).rgbBlue=0;
		(*pquad).rgbReserved=0;
		(*(pquad+1)).rgbRed=255;
		(*(pquad+1)).rgbGreen=255;
		(*(pquad+1)).rgbBlue=255;
		(*(pquad+1)).rgbReserved=0;		
	}
	else
	{  
		for(int i=0;i<BITSTABLE[nBits-1];i++)
		{
			(*(pquad+i)).rgbRed=(*(pquad+i)).rgbGreen=(*(pquad+i)).rgbBlue=255*i/(BITSTABLE[nBits-1]-1);
			
			(*(pquad+i)).rgbReserved=0;				
		}			

	}
	memcpy(&pbmpinfo->bmiColors,pquad,sizeof(RGBQUAD)*BITSTABLE[nBits-1]);
	delete []pquad;
}

void CFont_drawDlg::FormFileHeader(int nWidth, int nHeight,int nBits)
{	
	
	if(pfileinfo!=NULL)
		delete []pfileinfo;

	pfileinfo = (LPBITMAPFILEHEADER)new BYTE[sizeof(BITMAPFILEHEADER)];

	pfileinfo->bfType = *(WORD*)(&"BM");

	pfileinfo->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * BITSTABLE[nBits-1];

	pfileinfo->bfSize = pfileinfo->bfOffBits + charLineW * nHeight;
	
	
}

//������ת��Ϊ������
FIXED CFont_drawDlg::Double2Fixed(double Dbl)
{
	int ll;
	ll=(int)(Dbl * 65536L);
	return *(FIXED *)&ll;
}
//������ת��Ϊ������
double CFont_drawDlg::Fixed2Double(FIXED Fxd)
{
	return Fxd.value+(double)Fxd.fract/65536;
}

void CFont_drawDlg::OnChangeEdSize() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

//int ת��Ϊstring
string CFont_drawDlg::int_to_string(int n)
{
	ostringstream stream;
	stream << n;  //nΪint����
	return stream.str();
}

//������¼�ı�����������ص�λ
void CFont_drawDlg::save_file_txt(char* szText,vector<POINT>lpPoints, int nCount)
{
	GetLocalTime(&st);	//��ȡϵͳʱ��
	//printf("%d-%02d-%02d %02d:%02d:%02d\n", st.wYear,st.wMonth,	st.wDay,t.wHour,st.wMinute,st.wSecond)
	string time_txt_name;
	
	time_txt_name = int_to_string(st.wYear) + "��" +  int_to_string(st.wMonth) + "��" + int_to_string(st.wDay) + "��" + int_to_string(st.wHour) + "ʱ" + int_to_string(st.wMinute) + "��";
	//time_txt_name = "C:\\" + time_txt_name + "_point.txt" + "\0";
	
	//file_name = time_txt_name.c_str();
	
	file_name = "c:\\point_font.txt";
	
    ofstream outfile;      
    outfile.open(file_name, ios::out | ios::app);	//��׷�ӵķ�ʽ��
	if (!outfile)
	{
		MessageBox("�½�TXTʧ��", "����ֹͣ", MB_OK+MB_ICONEXCLAMATION);
		return;
	}
	if (!save_once)
	{
		//�����ʽ
		outfile << "========================================================================";
		outfile	<< "\n";
		outfile << time_txt_name; 
		outfile	<< "\n";
		outfile << "========================================================================";
		outfile	<< "\n";
		save_once = true;
	}
	
	static  int next_word = 0;
	
	//�������
	if (next_word != save_num)//��һ��
	{
		next_word = save_num;
		outfile << next_word << ":" << szText << "\n";			//1.
	}

	for (int i = 0 ; i < nCount; i++)
	{
		char buf1[10];
		char buf2[10];
		sprintf(buf1, "%3d", lpPoints[i].x);
		sprintf(buf2, "%3d", lpPoints[i].y);	//��ʽ�����
		outfile << "[" << buf1 << "," << buf2 << "]" << "\t" ;
		if (lpPoints[i].x == 10000 || lpPoints[i].x == 20000)
		{
			outfile << "\n";
		}
	}
	
	outfile << "\n" ;
	
	outfile.close();
	
}

void CFont_drawDlg::save_file_txt1(vector<POINT>&lpPoints,string str)
{
	file_name = "d:\\pline_MATLAB.txt";

	ofstream outfile;      
	outfile.open(file_name, ios::out | ios::app);	//��׷�ӵķ�ʽ��
	if (!outfile)
	{
		MessageBox("�½�TXTʧ��", "����ֹͣ", MB_OK+MB_ICONEXCLAMATION);
		return;
	}
	static int num = 0;
	
	outfile << "Point_X = " << "\n";
	for (int i = 0; i <= lpPoints.size()-2; i++)
	{
		outfile << lpPoints[i].x <<" ";
	}
	outfile << lpPoints[lpPoints.size()-1].x <<"\n";
	
	for (int i = 0; i <= lpPoints.size()-2; i++)
	{
		outfile << lpPoints[i].y <<" ";
	}
	outfile << lpPoints[lpPoints.size()-1].y << "\n";

// 	for (int i = 0; i <= lpPoints.size()-1; i++)
// 	{
// 		outfile << 2 << " ";
// 	}
/*	outfile << "\n";*/

	outfile.close();
}
void CFont_drawDlg::OnChangeInput() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_Input_Word.GetLength() >  0)
	{
		m_Input_Word =  m_Input_Word.GetAt(0);
	}
	else
	{
		m_Input_Word =  "T";
	}
	UpdateData(TRUE);
	
}

void CFont_drawDlg::OnCreatFont() 
{
	// TODO: Add your control notification handler code here
	display_draw();
}

void CFont_drawDlg::OnDeltaposSpinSize(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown-> iDelta == 1) // �����ֵΪ1 , ˵�������Spin�����ϼ�ͷ 
	{  
		//���ӱ༭���е�����ֵ 
		if (change_font_size >= 235)
		{
			change_font_size = 235;
		}
		else
		{
			++change_font_size;
		}
	} 
	else if(pNMUpDown-> iDelta == -1) // �����ֵΪ-1 , ˵�������Spin�����¼�ͷ 
	{ 
		//���ٱ༭���е�����ֵ 
		if (change_font_size <= 0)
		{
			change_font_size = 0;
		}
		else
		{
			--change_font_size;
		}
    }
	
	CString Str;
	Str.Format( "%lf", change_font_size );
	m_edSize.SetWindowText(Str);
	
	ChangeFontSize(change_font_size);
	
	*pResult = 0;
	
	*pResult = 0;
}


//�ı������С
int CFont_drawDlg::ChangeFontSize(int newsize)
{
	//
	if(newsize >=0 && newsize <=300)
	{
		font_size = newsize * 10;
		
		// 		DeleteObject(m_Font);
		// 		m_Font.Detach();
		// 		
		// 		if(!m_Font.CreatePointFont(font_size,m_strFontName))
		// 		{
		// 			AfxMessageBox("Create new font failed!");
		// 			return 0;
		// 		}
		Invalidate();
	}
	return 1;
} 

BOOL CFont_drawDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
    {// process 'CR' 
		if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == m_edSize.m_hWnd)
			{
				if (change_font_size >= 235)
				{
					change_font_size = 235;
				}
				else if (change_font_size <= 20)
				{
					change_font_size = 20;
				}
				
				CString Str;
				Str.Format( "%d", change_font_size );
				m_edSize.SetWindowText(Str);
				ChangeFontSize(change_font_size);
				//afxDump << newSize << "\n";
			}
			return 1;
		}
    }
	//
	return CDialog::PreTranslateMessage(pMsg);
}

void CFont_drawDlg::OnSelchangeLfonts() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//������ʾ����
	m_edFace.Clear();
	m_edFace.SetWindowText(m_strFontName);
}


//�����λͼ
void CFont_drawDlg::OnSaveBmp() 
{
	// TODO: Add your control notification handler code here

	m_save_bmp	= true;
	display_draw_bmp();
	CString strfile; 
	CFileDialog cfd(FALSE,".bmp","δ����.bmp",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"BMP files(*.bmp)|*.bmp|All files(*.*)|*.*||",this);
	if(cfd.DoModal()==IDOK)
	{
		strfile=cfd.GetPathName();		
	}
	if(strfile.IsEmpty())
	{
		::AfxMessageBox("��������Ҫ������ļ�����");
		return ;
	}

	CFile cf;

	cf.Open(strfile,CFile::modeCreate|CFile::modeWrite);

	FormFileHeader(m_intPixX,m_intPixY,m_intBits);

	cf.Write(pfileinfo,sizeof(BITMAPFILEHEADER));

	cf.Write(pbmpinfo,sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*BITSTABLE[m_intBits-1]);

	cf.Write(pBuffer,charLineW*m_intPixY);

    cf.Close();


	if(pbmpinfo!=NULL)	
	{
		delete []pbmpinfo;
		pbmpinfo = NULL;
	}
	if(pfileinfo!=NULL)	
	{
		delete []pfileinfo;
		pfileinfo = NULL;
	}
}
