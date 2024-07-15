
// 硬编码超级列表框Dlg.h: 头文件
//

#pragma once


// C硬编码超级列表框Dlg 对话框
class C硬编码超级列表框Dlg : public CDialogEx
{
// 构造
public:
	C硬编码超级列表框Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl list1;
	CEdit edit1;
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//硬编码
	std::vector<DuozijieBianMa> yingbianma2;
	CString 当前答案;
	int 分数;
	int 地址;
	int 初始化硬编码map();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
//	CString 分数标签;
	CStatic biaoqian;
	CStatic biaoqian1;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnChangeEdit1();
};
bool 判断modrm是否有sib(CString modrm);
int 无sib计算长度(CString opmod);
int 有sib计算长度(CString strmodrm, CString strSib);
CString 可变长度编码转汇编(CString str, CString Assembly);
CString 计算reg(CString Assembly, CString strmodrm);
CString 无sib计算Rm(CString strmodrm, const CString& Assembly);
//第二次写
int 处理变长编码(CString& str, CString& strassembly, const CString& Assembly);
