#pragma once
#include "config.h"
enum 段前缀enum
{
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
	段前缀enum 段前缀;
	bool Operand_Size;
	bool Address_Size;
	repType rep;
	uint8_t opcode;
	std::string mnemonic;           // 助记符
	mnemonicType operand1;           // 操作数1类型
	mnemonicType operand2;           // 操作数2类型
	mnemonicType operand3;           // 操作数3类型

	uint8_t modrm;
	uint8_t sib;
	uint8_t mod;
	uint8_t reg;
	uint8_t rm;
	uint8_t scale;
	uint8_t index;
	uint8_t base;

	std::string stroperand1;           // 操作数1值
	std::string stroperand2;           // 操作数2值
	std::string stroperand3;           // 操作数3值
	int length;
	CString assembly;//处理好的整条反汇编指令
	CString allcode;//这条指令的所有硬编码
};

class VLE
{
private:
	std::vector<指令解码type> v解码指令集;
public:
	static int findOpcode(const CString & str);//传入整个str,,返回找到的索引,找不到返回-1
	int readOpcode(CString& str);//传入整个str,,返回找到的索引,找不到返回-1
};

