
// 硬编码超级列表框Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "硬编码超级列表框.h"
#include "硬编码超级列表框Dlg.h"
#include "afxdialogex.h"


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


// C硬编码超级列表框Dlg 对话框



C硬编码超级列表框Dlg::C硬编码超级列表框Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C硬编码超级列表框Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list1);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	//  DDX_Control(pDX, IDC_FENSHU, 分数标签);
	DDX_Control(pDX, IDC_FENSHU, biaoqian1);
}

BEGIN_MESSAGE_MAP(C硬编码超级列表框Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C硬编码超级列表框Dlg::OnBnClickedOk)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON2, &C硬编码超级列表框Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &C硬编码超级列表框Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C硬编码超级列表框Dlg 消息处理程序

BOOL C硬编码超级列表框Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	当前答案 = "";
	分数 = 0;
	srand(time(0));
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	list1.InsertColumn(0,"地址", 0,80);
	list1.InsertColumn(1, "硬编码", 0, 80);
	list1.InsertColumn(2, "反汇编", 0, 290);
	地址=0;
	初始化硬编码map();
	//将CListCtrl添加复选框check控件
	list1.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C硬编码超级列表框Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C硬编码超级列表框Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C硬编码超级列表框Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C硬编码超级列表框Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int 找到 = 0;
	
	int index = list1.GetItemCount();
	CString str地址;
	
	edit1.GetWindowText(str);
	
	
	if (str.IsEmpty())
	{
		MessageBox("请输入硬编码");
		return;
	}

	str地址.Format("%08X", 地址);
	//判断单字节硬编码
	for (auto it = yingbianma.begin(); it != yingbianma.end(); ++it) {
		if (str== it->first)
		{
			地址 += 1;
			list1.InsertItem(index, str地址);
			list1.SetItemText(index, 1, it->first);
			list1.SetItemText(index, 2, it->second);
			找到 = 1;
		}
		TRACE(it->first, it->second,"\n");
	}
	//判断多字节硬编码
	for (auto it = yingbianma2.begin(); it != yingbianma2.end(); ++it) {
		if ((*it).Hardcoding==str.Mid(0,2))
		{
			//判断代码长度是否正确
			if ((*it).Byt > str.GetLength()/2)
			{
				MessageBox("错误:字节长度不正确!");
				return;
			}
			
			list1.InsertItem(index, str地址);
			
			if ((*it).Byt > 2)
			{
				//多字节的立即数,要颠倒一下顺序
				CString 多字节立即数;
				list1.SetItemText(index, 1, (*it).Hardcoding + str.Mid(2,8));
				多字节立即数 = str.Mid(8, 2) + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2);
				list1.SetItemText(index, 2, (*it).Assembly +"0x" + 多字节立即数);
			}
			else
			{
				list1.SetItemText(index, 1, (*it).Hardcoding + str.Mid(2, 2));
				list1.SetItemText(index, 2, (*it).Assembly + "0x" + str.Mid(2, ((*it).Byt - 1) * 2));
			}
			地址 += (*it).Byt;
			找到 = 1;
		}
	}
	if (找到==0)
	{
		MessageBox("没有找到的编码!");
	}
	
	edit1.SetWindowText("");
	
//	CDialogEx::OnOK();
}



int C硬编码超级列表框Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	

	return 0;
}


int C硬编码超级列表框Dlg::初始化硬编码map()
{
	// TODO: 在此处添加实现代码.
	//40-47 inc eax-edi
	yingbianma.insert({ "40","inc eax" });
	yingbianma.insert({ "41","inc ecx" });
	yingbianma.insert({ "42","inc edx" });
	yingbianma.insert({ "43","inc ebx" });
	yingbianma.insert({ "44","inc esp" });
	yingbianma.insert({ "45","inc ebp" });
	yingbianma.insert({ "46","inc esi" });
	yingbianma.insert({ "47","inc edi" });

	//48-4f  dec eax-edi
	yingbianma.insert({ "48","dec eax" });
	yingbianma.insert({ "49","dec ecx" });
	yingbianma.insert({ "4a","dec edx" });
	yingbianma.insert({ "4b","dec ebx" });
	yingbianma.insert({ "4c","dec esp" });
	yingbianma.insert({ "4d","dec ebp" });
	yingbianma.insert({ "4e","dec esi" });
	yingbianma.insert({ "4f","dec edi" });

	//50 - 57  push eax - edi
	yingbianma.insert({ "50","push eax" });
	yingbianma.insert({ "51","push ecx" });
	yingbianma.insert({ "52","push edx" });
	yingbianma.insert({ "53","push ebx" });
	yingbianma.insert({ "54","push esp" });
	yingbianma.insert({ "55","push ebp" });
	yingbianma.insert({ "56","push esi" });
	yingbianma.insert({ "57","push edi" });

	//58 - 5f  pop eax - edi
	yingbianma.insert({ "58","pop eax" });
	yingbianma.insert({ "59","pop ecx" });
	yingbianma.insert({ "5a","pop edx" });
	yingbianma.insert({ "5b","pop ebx" });
	yingbianma.insert({ "5c","pop esp" });
	yingbianma.insert({ "5d","pop ebp" });
	yingbianma.insert({ "5e","pop esi" });
	yingbianma.insert({ "5f","pop edi" });

	//
	//XCHG
	yingbianma.insert({ "90","nop" });
	yingbianma.insert({ "91","xchg eax,ecx" });
	yingbianma.insert({ "92","xchg eax,edx" });
	yingbianma.insert({ "93","xchg eax,ebx" });
	yingbianma.insert({ "94","xchg eax,esp" });
	yingbianma.insert({ "95","xchg eax,ebp" });
	yingbianma.insert({ "96","xchg eax,esi" });
	yingbianma.insert({ "97","xchg eax,edi" });

	//多字节硬编码
	//b0 - b7  mov al-bh  占2字节
	yingbianma2.push_back(DuozijieBianMa("b0","mov al,",2));
	yingbianma2.push_back(DuozijieBianMa("b1", "mov cl,",2));
	yingbianma2.push_back(DuozijieBianMa("b2", "mov dl,", 2));
	yingbianma2.push_back(DuozijieBianMa("b3", "mov bl,", 2));
	yingbianma2.push_back(DuozijieBianMa("b4", "mov ah,", 2));
	yingbianma2.push_back(DuozijieBianMa("b5", "mov ch,", 2));
	yingbianma2.push_back(DuozijieBianMa("b6", "mov dh,", 2));
	yingbianma2.push_back(DuozijieBianMa("b7", "mov bh,", 2));

	//b8 - bf mov eax-edi 占5个字节
	yingbianma2.push_back(DuozijieBianMa("b8", "mov eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("b9", "mov ecx,", 5));
	yingbianma2.push_back(DuozijieBianMa("ba", "mov edx,", 5));
	yingbianma2.push_back(DuozijieBianMa("bb", "mov ebx,", 5));
	yingbianma2.push_back(DuozijieBianMa("bc", "mov esp,", 5));
	yingbianma2.push_back(DuozijieBianMa("bd", "mov ebp,", 5));
	yingbianma2.push_back(DuozijieBianMa("be", "mov esi,", 5));
	yingbianma2.push_back(DuozijieBianMa("bf", "mov edi,", 5));

	//第二天
	//单字节
	yingbianma.insert({ "06","push es" });
	yingbianma.insert({ "07","pop es" });
	yingbianma.insert({ "0e","push cs" });
	yingbianma.insert({ "0f","两个字节编码表 保留" });
	yingbianma.insert({ "16","push ss" });
	yingbianma.insert({ "17","pop ss" });
	yingbianma.insert({ "1e","push ds" });
	yingbianma.insert({ "1f","pop ds" });
	yingbianma.insert({ "26","ec(前缀)" });
	yingbianma.insert({ "27","daa" });
	yingbianma.insert({ "2e","cs(前缀)" });
	yingbianma.insert({ "2f","das" });
	yingbianma.insert({ "36","ss(前缀)" });
	yingbianma.insert({ "37","aaa" });
	yingbianma.insert({ "3e","ds(前缀)" });
	yingbianma.insert({ "3f","aas" });

	//多字节
	yingbianma2.push_back(DuozijieBianMa("04", "add al,", 2));
	yingbianma2.push_back(DuozijieBianMa("05", "add eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("0c", "or al,", 2));
	yingbianma2.push_back(DuozijieBianMa("0d", "or eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("14", "adc al,", 2));
	yingbianma2.push_back(DuozijieBianMa("15", "adc eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("1c", "sbb al,", 2));
	yingbianma2.push_back(DuozijieBianMa("1d", "sbb eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("24", "and al,", 2));
	yingbianma2.push_back(DuozijieBianMa("25", "and eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("2c", "sub al,", 2));
	yingbianma2.push_back(DuozijieBianMa("2d", "sub eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("34", "xor al,", 2));
	yingbianma2.push_back(DuozijieBianMa("35", "xor eax,", 5));
	yingbianma2.push_back(DuozijieBianMa("3c", "cmp al,", 2));
	yingbianma2.push_back(DuozijieBianMa("3d", "cmp eax,", 5));
	return 0;
}


void C硬编码超级列表框Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	
	CButton* kaishi = (CButton*)GetDlgItem(IDC_BUTTON2);
	kaishi->SetWindowText("下一题");
	CEdit* edit1 = (CEdit*)GetDlgItem(IDC_EDIT2);
	while (true)
	{
		int num = rand() % 255;
		CString str;
		str.Format("%02X", num);
		for (auto it = yingbianma.begin(); it != yingbianma.end(); ++it) {
			if (str == it->first)
			{
				
				edit1->SetWindowText(str);
				当前答案 = (*it).second;
				return;
			}
		}
		//判断多字节硬编码
		for (auto it = yingbianma2.begin(); it != yingbianma2.end(); ++it) {
			if ((*it).Hardcoding == str)
			{
				if ((*it).Byt == 2)
				{
					str = str + " 12";
					edit1->SetWindowText(str);
					当前答案 = (*it).Assembly + "12";
					return;
				}
				else if((*it).Byt == 5)
				{
					str = str + " 78563412";
					edit1->SetWindowText(str);
					当前答案 = (*it).Assembly + "12345678";
					return;
				}
				
			}
		}
	}
	


}


void C硬编码超级列表框Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* edit1 = (CEdit*)GetDlgItem(IDC_EDIT3);
	CString str;
	CString 分数str;
	edit1->GetWindowTextA(str);
	if (str==当前答案)
	{
		分数 += 10;
		CEdit* edit1 = (CEdit*)GetDlgItem(IDC_EDIT3);
		分数str.Format("%d", 分数);
		分数str = "分数:" + 分数str;
	
		biaoqian1.SetWindowText(分数str);
		edit1->SetWindowText("");
		OnBnClickedButton2();

	}
	else
	{
		MessageBox("错误:正确答案为:" + 当前答案);
	}
}
