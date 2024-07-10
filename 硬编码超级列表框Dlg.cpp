
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
	ON_EN_CHANGE(IDC_EDIT3, &C硬编码超级列表框Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT1, &C硬编码超级列表框Dlg::OnChangeEdit1)
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
	CString str剩余代码;
	int 找到 = 0;
	int i剩余下标 = 0;
	int index;
	
	CString str地址;
	
	edit1.GetWindowText(str);

	RemoveSpaces(str);
	edit1.SetWindowText("");
	i剩余下标 = str.GetLength();
	
	if (str.IsEmpty())
	{
		MessageBox("请输入硬编码");
		return;
	}
	
	//添加循环处理
	while (str!="")
	{
		找到 = 0;
		index = list1.GetItemCount();
		str地址.Format("%08X", 地址);
		
		//判断硬编码
		for (auto it = yingbianma2.begin(); it != yingbianma2.end(); ++it) {
			if ((*it).Hardcoding == str.Mid(0, 2))
			{
				list1.InsertItem(index, str地址);
				//str地址.Format("%08X", 地址);
				
				//判断代码长度是否正确
				if ((*it).Byt > str.GetLength() / 2)
				{
					MessageBox("错误:字节长度不正确!");
					return;
				}
				//单字节
				if ((*it).Byt == 1)
				{
					list1.SetItemText(index, 1, it->Hardcoding);
					list1.SetItemText(index, 2, it->Assembly);
					str = str.Mid((*it).Byt * 2);
					地址 += (*it).Byt;
					找到 = 1;
					break;
				}
				else if ((*it).Byt > 2)
				{
					//大于2个字节的硬编码,立即数要颠倒一下顺序
					CString 立即数;
					list1.SetItemText(index, 1, (*it).Hardcoding + str.Mid(2, 8));
					立即数 = str.Mid(8, 2) + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2);
					list1.SetItemText(index, 2, (*it).Assembly + "0x" + 立即数);
					地址 += (*it).Byt;
					找到 = 1;
					str = str.Mid((*it).Byt * 2);
					break;
				}
				else
				{
					//2个长度的硬编码
					list1.SetItemText(index, 1, (*it).Hardcoding + str.Mid(2, 2));
					list1.SetItemText(index, 2, (*it).Assembly + "0x" + str.Mid(2, ((*it).Byt - 1) * 2));
					地址 += (*it).Byt;
					找到 = 1;
					str = str.Mid((*it).Byt * 2);
					break;
				}
				
			}
		}
		if (找到 == 0)
		{
			MessageBox("错误:没有找到的编码!"+ str.Mid(0,2));
			break;
		}

	}
	
	
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
	yingbianma2.push_back({ "40","inc eax",1 });
	yingbianma2.push_back({ "41","inc ecx",1 });
	yingbianma2.push_back({ "42","inc edx",1 });
	yingbianma2.push_back({ "43","inc ebx",1 });
	yingbianma2.push_back({ "44","inc esp",1 });
	yingbianma2.push_back({ "45","inc ebp",1 });
	yingbianma2.push_back({ "46","inc esi",1 });
	yingbianma2.push_back({ "47","inc edi",1 });

	//48-4f  dec eax-edi
	yingbianma2.push_back({ "48","dec eax",1 });
	yingbianma2.push_back({ "49","dec ecx",1 });
	yingbianma2.push_back({ "4a","dec edx",1 });
	yingbianma2.push_back({ "4b","dec ebx",1 });
	yingbianma2.push_back({ "4c","dec esp",1 });
	yingbianma2.push_back({ "4d","dec ebp",1 });
	yingbianma2.push_back({ "4e","dec esi" ,1 });
	yingbianma2.push_back({ "4f","dec edi",1 });

	//50 - 57  push eax - edi
	yingbianma2.push_back({ "50","push eax",1 });
	yingbianma2.push_back({ "51","push ecx",1 });
	yingbianma2.push_back({ "52","push edx",1 });
	yingbianma2.push_back({ "53","push ebx",1 });
	yingbianma2.push_back({ "54","push esp",1 });
	yingbianma2.push_back({ "55","push ebp",1 });
	yingbianma2.push_back({ "56","push esi",1 });
	yingbianma2.push_back({ "57","push edi",1 });

	//58 - 5f  pop eax - edi
	yingbianma2.push_back({ "58","pop eax",1 });
	yingbianma2.push_back({ "59","pop ecx",1 });
	yingbianma2.push_back({ "5a","pop edx",1 });
	yingbianma2.push_back({ "5b","pop ebx",1 });
	yingbianma2.push_back({ "5c","pop esp",1 });
	yingbianma2.push_back({ "5d","pop ebp" ,1 });
	yingbianma2.push_back({ "5e","pop esi",1 });
	yingbianma2.push_back({ "5f","pop edi",1 });

	//
	//XCHG
	yingbianma2.push_back({ "90","nop",1 });
	yingbianma2.push_back({ "91","xchg eax,ecx",1 });
	yingbianma2.push_back({ "92","xchg eax,edx",1 });
	yingbianma2.push_back({ "93","xchg eax,ebx",1 });
	yingbianma2.push_back({ "94","xchg eax,esp",1 });
	yingbianma2.push_back({ "95","xchg eax,ebp",1 });
	yingbianma2.push_back({ "96","xchg eax,esi",1 });
	yingbianma2.push_back({ "97","xchg eax,edi" ,1 });

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
	yingbianma2.push_back({ "06","push es",1 });
	yingbianma2.push_back({ "07","pop es",1 });
	yingbianma2.push_back({ "0e","push cs",1 });
	yingbianma2.push_back({ "0f","两个字节编码表 保留",1 });
	yingbianma2.push_back({ "16","push ss",1 });
	yingbianma2.push_back({ "17","pop ss",1 });
	yingbianma2.push_back({ "1e","push ds" ,1 });
	yingbianma2.push_back({ "1f","pop ds",1 });
	yingbianma2.push_back({ "26","ec(前缀)",1 });
	yingbianma2.push_back({ "27","daa",1 });
	yingbianma2.push_back({ "2e","cs(前缀)",1 });
	yingbianma2.push_back({ "2f","das" ,1 });
	yingbianma2.push_back({ "36","ss(前缀)",1 });
	yingbianma2.push_back({ "37","aaa" ,1 });
	yingbianma2.push_back({ "3e","ds(前缀)",1 });
	yingbianma2.push_back({ "3f","aas",1 });

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

	//第三天继续添加
	//单字节
	yingbianma2.push_back({ "60","pushad" ,1 });
	yingbianma2.push_back({ "61","popad" ,1 });

	yingbianma2.push_back({ "64","fs(前缀)",1 });
	yingbianma2.push_back({ "65","gs(前缀)" ,1 });
	yingbianma2.push_back({ "66","操作数大小(前缀)",1 });
	yingbianma2.push_back({ "67","地址大小(前缀)",1 });

	yingbianma2.push_back({ "6c","insb" ,1 });
	yingbianma2.push_back({ "6d","insd" ,1 });
	yingbianma2.push_back({ "6e","outsb" ,1 });
	yingbianma2.push_back({ "6f","outsd",1 });

	yingbianma2.push_back({ "98","cwde",1 });
	yingbianma2.push_back({ "99","cdq" ,1 });
	yingbianma2.push_back({ "9b","fwait",1 });

	yingbianma2.push_back({ "9c","pushfd" ,1 });
	yingbianma2.push_back({ "9d","popfd",1 });
	yingbianma2.push_back({ "9e","sahf",1 });
	yingbianma2.push_back({ "9f","lahf",1 });

	yingbianma2.push_back({ "a4","movsb" ,1 });
	yingbianma2.push_back({ "a5","movsd",1 });
	yingbianma2.push_back({ "a6","cmpsb",1 });
	yingbianma2.push_back({ "a7","cmpsd" ,1 });

	yingbianma2.push_back({ "aa","stosb",1 });
	yingbianma2.push_back({ "ab","stosd" ,1 });

	yingbianma2.push_back({ "ac","lodsb",1 });
	yingbianma2.push_back({ "ad","lodsd" ,1 });
	yingbianma2.push_back({ "ae","scasb" ,1 });
	yingbianma2.push_back({ "af","scasd" ,1 });

	yingbianma2.push_back({ "c3","ret",1 });
	yingbianma2.push_back({ "c9","leave",1 });

	yingbianma2.push_back({ "cb","retf",1 });
	yingbianma2.push_back({ "cc","int0x3",1 });
	yingbianma2.push_back({ "ce","into" ,1 });
	yingbianma2.push_back({ "cf","iretd" ,1 });

	//多字节
	yingbianma2.push_back(DuozijieBianMa("68", "push ", 5));
	yingbianma2.push_back(DuozijieBianMa("6a", "push ", 2));

	yingbianma2.push_back(DuozijieBianMa("70", "jo ", 2));
	yingbianma2.push_back(DuozijieBianMa("71", "jno ", 2));
	yingbianma2.push_back(DuozijieBianMa("72", "jb ", 2));
	yingbianma2.push_back(DuozijieBianMa("73", "jnb ", 2));
	yingbianma2.push_back(DuozijieBianMa("74", "je ", 2));
	yingbianma2.push_back(DuozijieBianMa("75", "jnz ", 2));
	yingbianma2.push_back(DuozijieBianMa("76", "jbe ", 2));
	yingbianma2.push_back(DuozijieBianMa("77", "ja ", 2));
	yingbianma2.push_back(DuozijieBianMa("78", "js ", 2));
	yingbianma2.push_back(DuozijieBianMa("79", "jns ", 2));
	yingbianma2.push_back(DuozijieBianMa("7a", "jpe ", 2));
	yingbianma2.push_back(DuozijieBianMa("7b", "jpo ", 2));
	yingbianma2.push_back(DuozijieBianMa("7c", "jl ", 2));
	yingbianma2.push_back(DuozijieBianMa("7d", "jge ", 2));
	yingbianma2.push_back(DuozijieBianMa("7e", "jle ", 2));
	yingbianma2.push_back(DuozijieBianMa("7f", "jg ", 2));

	//长跳
	yingbianma2.push_back(DuozijieBianMa("0f80", "jo ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f81", "jno ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f82", "jb ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f83", "jnb ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f84", "je ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f85", "jnz ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f86", "jbe ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f87", "ja ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f88", "js ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f89", "jns ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f8a", "jpe ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f8b", "jpo ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f8c", "jl ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f8d", "jge ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f8e", "jle ", 6));
	yingbianma2.push_back(DuozijieBianMa("0f8f", "jg ", 6));

	
	yingbianma2.push_back(DuozijieBianMa("9a", "call  ap", 7));

	yingbianma2.push_back(DuozijieBianMa("a0", "mov al,", 5));
	yingbianma2.push_back(DuozijieBianMa("a1", "mov eax,", 5));
	//需要优化
	yingbianma2.push_back(DuozijieBianMa("a3", "mov ob,al", 5));
	yingbianma2.push_back(DuozijieBianMa("a4", "mov ov,eax", 5));

	yingbianma2.push_back(DuozijieBianMa("a8", "test al,", 2));
	yingbianma2.push_back(DuozijieBianMa("a9", "test eax,", 5));

	yingbianma2.push_back(DuozijieBianMa("c2", "ret iw", 3));
	yingbianma2.push_back(DuozijieBianMa("c8", "enter  iw ib", 4));

	yingbianma2.push_back(DuozijieBianMa("ca", "retf  iw", 3));
	yingbianma2.push_back(DuozijieBianMa("cd", "int ib", 2));


	//第四天学的硬编码
	yingbianma2.push_back(DuozijieBianMa("d4", "aam ", 2));
	yingbianma2.push_back(DuozijieBianMa("d5", "aad ", 2));

	yingbianma2.push_back(DuozijieBianMa("e0", "loopnz ", 2));
	yingbianma2.push_back(DuozijieBianMa("e1", "loopz ", 2));
	yingbianma2.push_back(DuozijieBianMa("e2", "loop ", 2));
	yingbianma2.push_back(DuozijieBianMa("e3", "jrcxz ", 2));
	yingbianma2.push_back(DuozijieBianMa("e4", "in al,", 2));
	yingbianma2.push_back(DuozijieBianMa("e5", "in eax,", 2));
	yingbianma2.push_back(DuozijieBianMa("e6", "out ib,al", 2));

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
		int num = rand() % 256;
		//num = 10;
		CString str;
		str.Format("%02x", num);
		
		//判断硬编码
		for (auto it = yingbianma2.begin(); it != yingbianma2.end(); ++it) {
			if ((*it).Hardcoding == str)
			{
				if ((*it).Byt == 1)
				{
					edit1->SetWindowText(str);
					当前答案 = (*it).Assembly;
					return;
				}
				else if ((*it).Byt == 2)
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


void C硬编码超级列表框Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}
void RemoveSpaces(CString& str) {
    CString result;
    for (int i = 0; i < str.GetLength(); ++i) {
        if (str[i] != ' ') {
            result += str[i];
        }
    }
    str = result;
}

void C硬编码超级列表框Dlg::OnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//CString str编辑框1内容;
	//CString str编辑框1内容2;
	//edit1.GetWindowText(str编辑框1内容);
	//str编辑框1内容2 = str编辑框1内容;
	//RemoveSpaces(str编辑框1内容2);
	//if (str编辑框1内容2.GetLength()%2 == 0)
	//{
	//	str编辑框1内容 = str编辑框1内容 + " ";
	//	//edit1.SetWindowText(str编辑框1内容);
	//}
	////edit1.SetWindowText(str编辑框1内容);

	////MessageBox("请输入硬编码");
}
