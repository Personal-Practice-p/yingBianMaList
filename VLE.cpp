#include "pch.h"
#include"VLE.h"


int VLE::findOpcode(const CString& str)//传入整个str
{
	return 0;
}
int VLE::readOpcode(CString& str)//传入整个str
{
	unsigned int Code = 0;
	int prefixFlag=0;
	CString strCode;
	
	指令解码type new指令;
	
	
	while (prefixFlag!=3)
	{
		if (str == "")
		{
			TRACE("无字符串:\n");
			/*MessageBox(NULL, "over", NULL, NULL);*/
		}
		//先读取第一个字节
		strCode = str.Mid(0, 2);
		Code = strtol(strCode, NULL, 16);
		prefixFlag = 0;
		for (int i = 0; i < prefixList.size(); i++)
		{
			if (prefixList[i].opcode == Code)
			{
				Handling_prefix(new指令, Code);
				new指令.allCode = new指令.allCode + strCode;
				TRACE("前缀:" + strCode+"\n");
				deleteStr(str, 1);
				
				prefixFlag = 1;
				break;
			}
			//TRACE("_itoa(i)\n");
		}
		if (prefixFlag == 0)
		{
			prefixFlag = 3;
		}
	}

	//处理opcode
	for (int i = 0; i < v指令集.size(); i++)
	{
		if (v指令集[i].opcode == Code)
		{
			//找到
			TRACE("opcode:"+ strCode + v指令集[i].mnemonic +"\n");
			Handle_Opcode(new指令, i);
			new指令.allCode = new指令.allCode + strCode;
			deleteStr(str, 1);
		}
	}
	//处理modrm
	new指令.operand1 == 
	

	return 0;
}

void VLE::Handle_Opcode(指令解码type& new指令, int index)
{
	new指令.opcode = v指令集[index].opcode;
	new指令.mnemonic = v指令集[index].mnemonic;

	new指令.operand1 = v指令集[index].operand1;
	new指令.operand2 = v指令集[index].operand2;
	new指令.operand3 = v指令集[index].operand3;
	

}

bool VLE::deleteStr(CString& str, int num)//num是字节数
{
	str = str.Mid(num*2);
	return true;
}
void VLE::Handling_prefix(指令解码type& new指令,int refix)
{
	switch (refix)
	{
	case 0x26:
		new指令.段前缀 = es;
		break;
	case 0x2e:
		new指令.段前缀 = cs;
		break;
	case 0x36:
		new指令.段前缀 = ss;
		break;
	case 0x3e:
		new指令.段前缀 = ds;
		break;
	case 0x64:
		new指令.段前缀 = fs;
		break;
	case 0x65:
		new指令.段前缀 = gs;
		break;
	case 0x66:
		new指令.Operand_Size = true;
		break;
	case 0x67:
		new指令.Address_Size = true;
		break;
	case 0xf0:
		new指令.lock = true;
		break;
	case 0xf2:
		new指令.rep = repne;
		break;
	case 0xf3:
		new指令.rep = rep;
		break;
	default:
		break;
	}
}