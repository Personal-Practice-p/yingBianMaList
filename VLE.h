#pragma once
#include "config.h"
#include"GlobalCommands.h"
class VLE
{
private:
	CString str;//待处理的字符串
public:
	std::vector<指令解码type> v解码指令集;

	
	static int findOpcode(const CString & str);//传入整个str,,返回找到的索引,找不到返回-1
	int readOpcode(CString can_str);//传入整个str,,返回找到的索引,找不到返回-1

	//用来处理字符串,处理的编码,就删除掉
	bool deleteStr(int num);

	//处理前缀
	void VLE::Handling_prefix(指令解码type& disb, int refix);
	void VLE::Handle_Opcode(指令解码type& disb, int index);
	bool VLE::判断modrm(const 指令解码type& disb);
	bool VLE::判断Sib(const 指令解码type& disb);
	void VLE::处理modrm和sib(指令解码type& disb);
	void VLE::Process_operands(指令解码type& disb);
	void VLE::功能_处理operands(mnemonicType& operand, CString& stroperand);

	//返回sib处理 []里面的字符串
	CString VLE::Sib处理地址偏移(指令解码type& disb);
	void VLE::eorr_Opcode(指令解码type& disb, int code);
};

