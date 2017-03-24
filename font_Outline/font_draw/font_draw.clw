; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFont_drawDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "font_draw.h"

ClassCount=3
Class1=CFont_drawApp
Class2=CFont_drawDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FONT_DRAW_DIALOG

[CLS:CFont_drawApp]
Type=0
HeaderFile=font_draw.h
ImplementationFile=font_draw.cpp
Filter=N

[CLS:CFont_drawDlg]
Type=0
HeaderFile=font_drawDlg.h
ImplementationFile=font_drawDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_Input

[CLS:CAboutDlg]
Type=0
HeaderFile=font_drawDlg.h
ImplementationFile=font_drawDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FONT_DRAW_DIALOG]
Type=1
Class=CFont_drawDlg
ControlCount=17
Control1=IDC_STATIC,static,1342308352
Control2=IDC_Input,edit,1352728580
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LFONTS,listbox,1352728835
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ED_FACE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ED_SIZE,edit,1350631552
Control9=IDC_SPIN_SIZE,msctls_updown32,1342177312
Control10=IDC_STATIC,button,1342178055
Control11=IDC_Save_Bmp,button,1342242816
Control12=IDC_STATIC,button,1342178055
Control13=IDC_Draw_Picture,static,1342177287
Control14=IDC_CREAT_FONT,button,1342242816
Control15=IDC_Draw_BMP,static,1342177287
Control16=IDC_STATIC,button,1342178055
Control17=IDC_STATIC,button,1342178055

