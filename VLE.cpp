#include "pch.h"
#include"VLE.h"


int VLE::findOpcode(const CString& str)//��������str
{
	return 0;
}
int VLE::readOpcode(CString can_str)//��������str
{
	str = can_str;
	unsigned int Code = 0;
	int prefixFlag=0;
	CString strCode;
	
	ָ�����type newָ��;
	
	
	while (prefixFlag!=3)
	{
		if (str == "")
		{
			TRACE("���ַ���:\n");
			/*MessageBox(NULL, "over", NULL, NULL);*/
		}
		//�ȶ�ȡ��һ���ֽ�
		strCode = str.Mid(0, 2);
		Code = strtol(strCode, NULL, 16);
		prefixFlag = 0;
		for (int i = 0; i < prefixList.size(); i++)
		{
			if (prefixList[i].opcode == Code)
			{
				Handling_prefix(newָ��, Code);
				newָ��.allCode = newָ��.allCode + strCode;
				TRACE("ǰ׺:" + strCode+"\n");
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

	//����opcode
	for (int i = 0; i < vָ�.size(); i++)
	{
		if (vָ�[i].opcode == Code)
		{
			//�ҵ�
			TRACE("opcode:"+ strCode + vָ�[i].mnemonic +"\n");
			Handle_Opcode(newָ��, i);
			newָ��.allCode = newָ��.allCode + strCode;
			deleteStr( 1);
		}
	}

	//����modrm
	if (�ж�modrm(newָ��))
	{
		//Ϊtrue ��modrm
		newָ��.modrm= strtol(str.Mid(0, 2), NULL, 16);
		deleteStr( 1);
		if (�ж�Sib(newָ��))
		{
			newָ��.sib = strtol(str.Mid(0, 2), NULL, 16);
			deleteStr( 1);
		}
	}
	����modrm��sib(newָ��);
	Process_operands(newָ��);




	

	return 0;
}

void VLE::Handle_Opcode(ָ�����type& newָ��, int index)
{
	newָ��.opcode = vָ�[index].opcode;
	newָ��.mnemonic = vָ�[index].mnemonic;

	newָ��.operand[0] = vָ�[index].operand1;
	newָ��.operand[1] = vָ�[index].operand2;
	newָ��.operand[2] = vָ�[index].operand3;
	

}
void VLE::Process_operands(ָ�����type& newָ��)
{
	
	for (int i = 0; i < 3; i++)
	{
		//������Ϊ�Ĵ���
		if (newָ��.operand[i] >= 0x10 && newָ��.operand[i] < 0x20 && newָ��.Operand_Size == false)
		{	//eax - edi  && 66==0
			newָ��.stroperand[i] = reg32[newָ��.operand[i] & 0x7];
		}
		else if (newָ��.operand[i] >= 0x20 && newָ��.operand[i] < 0x30 && newָ��.Operand_Size == false)
		{
			newָ��.stroperand[i] = reg8[newָ��.operand[i] & 0x7];
		}
		else if (newָ��.operand[i] >= 0x30 && newָ��.operand[i] < 0x40 && newָ��.Operand_Size == false)
		{
			newָ��.stroperand[i] = reg16[newָ��.operand[i] & 0x7];
		}
		else if (newָ��.operand[i] >= 0x10 && newָ��.operand[i] < 0x20 && newָ��.Operand_Size == true)
		{
			newָ��.stroperand[i] = reg16[newָ��.operand[i] & 0x7];//66 = true reg32->reg16
		}

		//������Ϊ������
		if (newָ��.operand[i] == Ib)
		{
			newָ��.stroperand[i] = "0x" + str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0, 2);
			deleteStr(1);
		}
		else if ((newָ��.operand[i] == Iz || newָ��.operand[i] == Iv) && newָ��.Operand_Size == false)
		{
			newָ��.stroperand[i] = "0x" + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0, 8);
			deleteStr(4);
		}
		else if ((newָ��.operand[i] == Iz || newָ��.operand[i] == Iv) && newָ��.Operand_Size == true)
		{
			newָ��.stroperand[i] = "0x" + str.Mid(2, 2) + str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0,4);
			deleteStr(2);
		}
		else if (newָ��.operand[i] == iw)
		{
			newָ��.stroperand[i] = "0x" + str.Mid(2, 2) + str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0, 4);
			deleteStr(2);
		}
		//����jb��jz
		if (newָ��.operand[i] == jb)
		{
			newָ��.stroperand[i] = str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0, 2);
			deleteStr(1);
		}
		else if (newָ��.operand[i] == jz && newָ��.Operand_Size == false)
		{
			newָ��.stroperand[i] = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0, 8);
			deleteStr(4);
		}
		else if (newָ��.operand[i] == jz && newָ��.Operand_Size == true)
		{
			newָ��.stroperand[i] = str.Mid(2, 2) + str.Mid(0, 2);
			newָ��.allCode = newָ��.allCode + str.Mid(0, 4);
			deleteStr(2);
		}

		

	}
	TRACE(newָ��.mnemonic + " " + newָ��.stroperand[0]+"," + newָ��.stroperand[1] + ","+ newָ��.stroperand[2] + "\n");
	
}

bool VLE::deleteStr(int num)//num���ֽ���
{
	str = str.Mid(num*2);
	return true;
}
void VLE::Handling_prefix(ָ�����type& newָ��,int refix)
{
	switch (refix)
	{
	case 0x26:
		newָ��.��ǰ׺ = es;
		break;
	case 0x2e:
		newָ��.��ǰ׺ = cs;
		break;
	case 0x36:
		newָ��.��ǰ׺ = ss;
		break;
	case 0x3e:
		newָ��.��ǰ׺ = ds;
		break;
	case 0x64:
		newָ��.��ǰ׺ = fs;
		break;
	case 0x65:
		newָ��.��ǰ׺ = gs;
		break;
	case 0x66:
		newָ��.Operand_Size = true;
		break;
	case 0x67:
		newָ��.Address_Size = true;
		break;
	case 0xf0:
		newָ��.lock = true;
		break;
	case 0xf2:
		newָ��.rep = repne;
		break;
	case 0xf3:
		newָ��.rep = rep;
		break;
	default:
		break;
	}
}
bool VLE::�ж�modrm(const ָ�����type& newָ��)
{
	if (newָ��.operand[0] >= 0x60 && newָ��.operand[0] < 0x70)
	{
		return true;
	}
	if (newָ��.operand[1] >= 0x60 && newָ��.operand[1] < 0x70)
	{
		return true;
	}
	return false;
}
void VLE::����_����operands(mnemonicType& operand, CString& stroperand)
{
	
}

bool VLE::�ж�Sib(const ָ�����type& newָ��)
{
	
	int imodrm = newָ��.modrm;
	if ((imodrm & 0xe0) != 0xe0)//�ж���00 01 10 ���Һ���λ��100
	{
		if ((imodrm & 0x07) == 0x4)
		{
			return true;
		}
	}

	return false;
	
}
void VLE::����modrm��sib(ָ�����type& newָ��)
{
	if (newָ��.modrm!=0)
	{
		newָ��.reg = newָ��.modrm >> 3 & 0x7;
		newָ��.mod = newָ��.modrm >> 6;
		newָ��.rm = newָ��.modrm & 0x7;
	}
	if (newָ��.sib != 0)
	{
		newָ��.scale = newָ��.sib>>6;
		newָ��.index = newָ��.sib >> 3 & 0x7;
		newָ��.base = newָ��.sib  & 0x7;
	}
}