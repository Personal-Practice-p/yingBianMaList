#include "pch.h"
#include"VLE.h"


int VLE::findOpcode(const CString& str)//传入整个str
{
	return 0;
}
int VLE::readOpcode(CString can_str)//传入整个str
{
	str = can_str;
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
				deleteStr( 1);
				
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
			deleteStr( 1);
		}
	}

	//处理modrm
	if (判断modrm(new指令))
	{
		//为true 有modrm
		new指令.modrm= strtol(str.Mid(0, 2), NULL, 16);
		deleteStr( 1);
		if (判断Sib(new指令))
		{
			new指令.sib = strtol(str.Mid(0, 2), NULL, 16);
			deleteStr( 1);
		}
	}
	处理modrm和sib(new指令);
	Process_operands(new指令);




	

	return 0;
}

void VLE::Handle_Opcode(指令解码type& new指令, int index)
{
	new指令.opcode = v指令集[index].opcode;
	new指令.mnemonic = v指令集[index].mnemonic;

	new指令.operand[0] = v指令集[index].operand1;
	new指令.operand[1] = v指令集[index].operand2;
	new指令.operand[2] = v指令集[index].operand3;
	

}
void VLE::Process_operands(指令解码type& new指令)
{
	
	for (int i = 0; i < 3; i++)
	{
		//操作数为寄存器
		if (new指令.operand[i] >= 0x10 && new指令.operand[i] < 0x20 && new指令.Operand_Size == false)
		{	//eax - edi  && 66==0
			new指令.stroperand[i] = reg32[new指令.operand[i] & 0x7];
		}
		else if (new指令.operand[i] >= 0x20 && new指令.operand[i] < 0x30 && new指令.Operand_Size == false)
		{
			new指令.stroperand[i] = reg8[new指令.operand[i] & 0x7];
		}
		else if (new指令.operand[i] >= 0x30 && new指令.operand[i] < 0x40 && new指令.Operand_Size == false)
		{
			new指令.stroperand[i] = reg16[new指令.operand[i] & 0x7];
		}
		else if (new指令.operand[i] >= 0x10 && new指令.operand[i] < 0x20 && new指令.Operand_Size == true)
		{
			new指令.stroperand[i] = reg16[new指令.operand[i] & 0x7];//66 = true reg32->reg16
		}

		//操作数为立即数
		if (new指令.operand[i] == Ib)
		{
			new指令.stroperand[i] = "0x" + str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0, 2);
			deleteStr(1);
		}
		else if ((new指令.operand[i] == Iz || new指令.operand[i] == Iv) && new指令.Operand_Size == false)
		{
			new指令.stroperand[i] = "0x" + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0, 8);
			deleteStr(4);
		}
		else if ((new指令.operand[i] == Iz || new指令.operand[i] == Iv) && new指令.Operand_Size == true)
		{
			new指令.stroperand[i] = "0x" + str.Mid(2, 2) + str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0,4);
			deleteStr(2);
		}
		else if (new指令.operand[i] == iw)
		{
			new指令.stroperand[i] = "0x" + str.Mid(2, 2) + str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0, 4);
			deleteStr(2);
		}
		//处理jb和jz
		if (new指令.operand[i] == jb)
		{
			new指令.stroperand[i] = str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0, 2);
			deleteStr(1);
		}
		else if (new指令.operand[i] == jz && new指令.Operand_Size == false)
		{
			new指令.stroperand[i] = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0, 8);
			deleteStr(4);
		}
		else if (new指令.operand[i] == jz && new指令.Operand_Size == true)
		{
			new指令.stroperand[i] = str.Mid(2, 2) + str.Mid(0, 2);
			new指令.allCode = new指令.allCode + str.Mid(0, 4);
			deleteStr(2);
		}

		

	}
	TRACE(new指令.mnemonic + " " + new指令.stroperand[0]+"," + new指令.stroperand[1] + ","+ new指令.stroperand[2] + "\n");
	
}

bool VLE::deleteStr(int num)//num是字节数
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
bool VLE::判断modrm(const 指令解码type& new指令)
{
	if (new指令.operand[0] >= 0x60 && new指令.operand[0] < 0x70)
	{
		return true;
	}
	if (new指令.operand[1] >= 0x60 && new指令.operand[1] < 0x70)
	{
		return true;
	}
	return false;
}
void VLE::功能_处理operands(mnemonicType& operand, CString& stroperand)
{
	
}

bool VLE::判断Sib(const 指令解码type& new指令)
{
	
	int imodrm = new指令.modrm;
	if ((imodrm & 0xe0) != 0xe0)//判断是00 01 10 并且后三位是100
	{
		if ((imodrm & 0x07) == 0x4)
		{
			return true;
		}
	}

	return false;
	
}
void VLE::处理modrm和sib(指令解码type& new指令)
{
	if (new指令.modrm!=0)
	{
		new指令.reg = new指令.modrm >> 3 & 0x7;
		new指令.mod = new指令.modrm >> 6;
		new指令.rm = new指令.modrm & 0x7;
	}
	if (new指令.sib != 0)
	{
		new指令.scale = new指令.sib>>6;
		new指令.index = new指令.sib >> 3 & 0x7;
		new指令.base = new指令.sib  & 0x7;
	}
}