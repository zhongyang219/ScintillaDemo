
// ScintillaTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ScintillaTest.h"
#include "ScintillaTestDlg.h"
#include "afxdialogex.h"
#include "../scintilla/include/Scintilla.h"
#include "../scintilla/include/SciLexer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CScintillaTestDlg 对话框



CScintillaTestDlg::CScintillaTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SCINTILLATEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScintillaTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScintillaTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CScintillaTestDlg 消息处理程序

BOOL CScintillaTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_view = (CScintillaEditView*)RUNTIME_CLASS(CScintillaEditView)->CreateObject();
    CRect rect;
    GetClientRect(rect);
    m_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, rect, this, 3000);
    m_view->OnInitialUpdate();
    m_view->ShowWindow(SW_SHOW);

    const char* g_szKeywords =
        "asm auto bool break case catch char class const "
        "const_cast continue default delete do double "
        "dynamic_cast else enum explicit extern false finally "
        "float for friend goto if inline int long mutable "
        "namespace new operator private protected public "
        "register reinterpret_cast register return short signed "
        "sizeof static static_cast struct switch template "
        "this throw true try typedef typeid typename "
        "union unsigned using virtual void volatile "
        "wchar_t while";
    m_view->SendMessage(SCI_SETLEXER, SCLEX_CPP); //C++语法解析
    m_view->SendMessage(SCI_SETKEYWORDS, 0, (sptr_t)g_szKeywords);//设置关键字
    // 下面设置各种语法元素前景色
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_WORD, 0x00FF0000);   //关键字
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_STRING, 0x001515A3); //字符串
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_CHARACTER, 0x001515A3); //字符
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_PREPROCESSOR, 0x00808080);//预编译开关
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_COMMENT, 0x00008000);//块注释
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_COMMENTLINE, 0x00008000);//行注释
    m_view->SendMessage(SCI_STYLESETFORE, SCE_C_COMMENTDOC, 0x00008000);//文档注释（/**开头）

    m_view->SendMessage(SCI_SETCODEPAGE, SC_CP_UTF8);       //支持UTF8
    m_view->SendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, (sptr_t)u8"微软雅黑");
    m_view->SendMessage(SCI_STYLESETSIZE, STYLE_DEFAULT, 10);

    m_view->SendMessage(SCI_SETTEXT, 0, (LPARAM)u8"测试文本");
    
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScintillaTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScintillaTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScintillaTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScintillaTestDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (m_view != nullptr && m_view->m_hWnd != NULL && nType != SIZE_MINIMIZED)
        m_view->SetWindowPos(nullptr, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
}


BOOL CScintillaTestDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    // TODO: 在此添加专用代码和/或调用基类
    SCNotification *pSCNotification = (SCNotification*)lParam;

    //switch (pSCNotification->nmhdr.code)
    //{
    //}
    return CDialog::OnNotify(wParam, lParam, pResult);
}
