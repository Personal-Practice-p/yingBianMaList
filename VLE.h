#pragma once
#include "config.h"
#include"GlobalCommands.h"
class VLE
{
private:
	std::vector<指令解码type> v解码指令集;
public:
	static int findOpcode(const CString & str);//传入整个str,,返回找到的索引,找不到返回-1
	int readOpcode(CString& str);//传入整个str,,返回找到的索引,找不到返回-1

	//用来处理字符串,处理的编码,就删除掉
	bool deleteStr(CString& str, int num);

	//处理前缀
	void VLE::Handling_prefix(指令解码type& new指令, int refix);
};

