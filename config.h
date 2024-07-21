#pragma once
#include<unordered_map>
#include <vector>
#include<string>

struct modrm
{
	int mod;
	int reg;
	int rm;
};

struct sib
{

	int scale;
	int index;
	int base;
};

enum mnemonicType
{
	//m_none,
	eax = 0x10,
	ecx,
	edx,
	ebx,
	esp,
	ebp,
	esi,
	edi,
	al = 0x20,//取右边知道寄存器的编号,取左边知道寄存器的类型
	cl,
	dl,
	bl,
	ah,
	ch,
	dh,
	bh,
	ax = 0x30,
	cx,
	dx,
	bx,
	sp,
	bp,
	si,
	di,

	jb=0x40,//和ib同一种操作,先写开,方便以后处理
	jz,//和iz同一种操作,先写开,方便以后处理

	fd,//eflage寄存器 fw是改变操作数后
	yb,//byte ptr ds:[esi]
	yz,
	xb,//byte ptr ds:[edi]
	xz,

	ov,
	ob,
	iw,	//imm16
	Sw,	// 段寄存器的选择子  es - gs
	m,	//只能内存
	mp,	//fword ptr ds:[]
	num1,	//只能是1

	none,
	Ib,
	Iz,
	Iv,

	Eb=0x60,
	Gb,
	Ev,
	Gv,
	Ma,//qword ptr ds:[]
	Ew,//16位内存word
	Gw,//16位寄存器

	ad=0x70,
	ap

};
struct InstructionDescriptor
{
	unsigned int opcode;                 // 操作码
	CString mnemonic;           // 助记符
	mnemonicType operand1;           // 操作数1类型
	mnemonicType operand2;           // 操作数2类型
	mnemonicType operand3;           // 操作数3类型
};

struct prefixtype
{
	uint8_t opcode;
	std::string mnemonic;
};



enum 段前缀enum
{
	p_none,
	es,
	cs,
	ss,
	ds,
	fs,
	gs
};
enum repType
{
	rep_none,
	rep,
	repne
};
struct 指令解码type
{
	段前缀enum 段前缀= p_none;
	bool Operand_Size=false;
	bool Address_Size = false;
	repType rep=rep_none;
	bool lock=false;
	unsigned int opcode=0;
	CString mnemonic;           // 助记符
	mnemonicType operand[3] = {none,none,none};           // 操作数  

	unsigned int modrm=0;
	unsigned int sib=0;
	uint8_t mod=0;
	uint8_t reg=0;  
	uint8_t rm=0;
	uint8_t scale=0;
	uint8_t index=0;												
	uint8_t base=0;

	//这个应该是计算过后的
	CString stroperand[3];           // 操作数值
	
	int length=0;
	CString assembly;//处理好的整条反汇编指令
	CString allCode;//这条指令的所有硬编码
};


