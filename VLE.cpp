#include "pch.h"
#include"VLE.h"


int VLE::findOpcode(const CString& str)//��������str
{
	return 0;
}
int VLE::readOpcode(CString& str)//��������str
{
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

	//����opcode
	for (int i = 0; i < vָ�.size(); i++)
	{
		if (vָ�[i].opcode == Code)
		{
			//�ҵ�
			TRACE("opcode:"+ strCode + vָ�[i].mnemonic +"\n");
			Handle_Opcode(newָ��, i);
			newָ��.allCode = newָ��.allCode + strCode;
			deleteStr(str, 1);
		}
	}
	//����modrm
	newָ��.operand1 == 
	

	return 0;
}

void VLE::Handle_Opcode(ָ�����type& newָ��, int index)
{
	newָ��.opcode = vָ�[index].opcode;
	newָ��.mnemonic = vָ�[index].mnemonic;

	newָ��.operand1 = vָ�[index].operand1;
	newָ��.operand2 = vָ�[index].operand2;
	newָ��.operand3 = vָ�[index].operand3;
	

}

bool VLE::deleteStr(CString& str, int num)//num���ֽ���
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