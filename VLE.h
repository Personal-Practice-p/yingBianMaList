#pragma once
#include "config.h"
#include"GlobalCommands.h"
class VLE
{
private:
	std::vector<指令解码type> v解码指令集;

	CString str;//待处理的字符串
public:
	static int findOpcode(const CString & str);//传入整个str,,返回找到的索引,找不到返回-1
	int readOpcode(CString can_str);//传入整个str,,返回找到的索引,找不到返回-1

	//用来处理字符串,处理的编码,就删除掉
	bool deleteStr(int num);

	//处理前缀
	void VLE::Handling_prefix(指令解码type& new指令, int refix);
	void VLE::Handle_Opcode(指令解码type& new指令, int index);
	bool VLE::判断modrm(const 指令解码type& new指令);
	bool VLE::判断Sib(const 指令解码type& new指令);
	void VLE::处理modrm和sib(指令解码type& new指令);
	void VLE::Process_operands(指令解码type& new指令);
	void VLE::功能_处理operands(mnemonicType& operand, CString& stroperand);
};

