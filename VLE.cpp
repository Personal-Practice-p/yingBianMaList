#include "pch.h"
#include"VLE.h"


int VLE::findOpcode(const CString& str)//��������str
{
	return 0;
}
int VLE::readOpcode(CString can_str)//��������str
{
	int onlyone=0;
	str = can_str;
	while (str!="")
	{

		unsigned int Code = 0;
		int prefixFlag = 0;
		CString strCode;

		ָ�����type disb;


		while (prefixFlag != 3)
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
					Handling_prefix(disb, Code);
					disb.allCode = disb.allCode + strCode;
					TRACE("ǰ׺:" + strCode + "\n");
					deleteStr(1);

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
		int find = 0;
		//����opcode
		//2���ֽڵ�
		if (Code == 0x0f)
		{
			strCode.Format("%02x", Code);
			strCode += str.Mid(2,2);
			Code= strtol(strCode, NULL, 16);
		}

		for (int i = 0; i < vָ�.size(); i++)
		{
			if (vָ�[i].opcode == Code)
			{
				find = 1;
				onlyone = 1;
				//�ҵ�
				TRACE("opcode:" + strCode + vָ�[i].mnemonic + "\n");
				Handle_Opcode(disb, i);
				disb.allCode = disb.allCode + strCode+" ";
				if (Code>0xff)//�ж����Ƿ���˫�ֽڴ���
				{
					deleteStr(2);
				}
				else
				{
					deleteStr(1);
				}
				
			}
		}
		//��Ҫ����δ���ִֻ��һ��
		if (find == 0 && onlyone==0)//û�ҵ�
		{
			onlyone = 1;
			eorr_Opcode(disb, Code);
			
			
			if (Code > 0xff)//�ж����Ƿ���˫�ֽڴ���
			{
				disb.allCode += str.Mid(0, 4);
				disb.length = 2;
				deleteStr(2);
			}
			else
			{
				disb.allCode += str.Mid(0, 2);
				disb.length = 1;
				deleteStr(1);
			}
			v����ָ�.push_back(disb);//ruku
			continue;
		}
		//����modrm
		if (�ж�modrm(disb))
		{
			//Ϊtrue ��modrm
			if (str.IsEmpty())
			{
				disb.assembly = "db 00";
				v����ָ�.push_back(disb);//ruku
				continue;
			}

			disb.modrm = strtol(str.Mid(0, 2), NULL, 16);
			disb.allCode += str.Mid(0, 2)+" ";
			deleteStr(1);
			if (�ж�Sib(disb))
			{
				disb.sib = strtol(str.Mid(0, 2), NULL, 16);
				disb.allCode += str.Mid(0, 2)+ " ";
				deleteStr(1);
			}
		}
		����modrm��sib(disb);

		Process_operands(disb);
		v����ָ�.push_back(disb);//ruku
		onlyone = 0;
	}

	

	return 0;
}

void VLE::Handle_Opcode(ָ�����type& disb, int index)
{
	disb.opcode = vָ�[index].opcode;
	disb.mnemonic = vָ�[index].mnemonic;

	disb.operand[0] = vָ�[index].operand1;
	disb.operand[1] = vָ�[index].operand2;
	disb.operand[2] = vָ�[index].operand3;
	

}
void VLE::eorr_Opcode(ָ�����type& disb, int code)
{
	CString temp;
	temp.Format("%x", code);
	//disb.allCode = temp;
	disb.assembly = "eorr no find opcode";
}
void VLE::Process_operands(ָ�����type& disb)
{
	
	for (int i = 0; i < 3; i++)
	{
		//������Ϊ�Ĵ���
		if (disb.operand[i] >= 0x10 && disb.operand[i] < 0x20 && disb.Operand_Size == false)
		{	//eax - edi  && 66==0
			disb.stroperand[i] = reg32[disb.operand[i] & 0x7];
		}
		else if (disb.operand[i] >= 0x20 && disb.operand[i] < 0x30 )
		{
			disb.stroperand[i] = reg8[disb.operand[i] & 0x7];
		}
		else if (disb.operand[i] >= 0x30 && disb.operand[i] < 0x40 )
		{
			disb.stroperand[i] = reg16[disb.operand[i] & 0x7];
		}
		else if (disb.operand[i] >= 0x10 && disb.operand[i] < 0x20 && disb.Operand_Size == true)
		{
			disb.stroperand[i] = reg16[disb.operand[i] & 0x7];//66 = true reg32->reg16
		}

		//������Ϊ������
		if (disb.operand[i] == Ib)
		{
			disb.stroperand[i] = "0x" + str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0, 2);
			deleteStr(1);
		}
		else if ((disb.operand[i] == Iz || disb.operand[i] == Iv) && disb.Operand_Size == false)
		{
			disb.stroperand[i] = "0x" + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0, 8);
			deleteStr(4);
		}
		else if ((disb.operand[i] == Iz || disb.operand[i] == Iv) && disb.Operand_Size == true)
		{
			disb.stroperand[i] = "0x" + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0,4);
			deleteStr(2);
		}
		else if (disb.operand[i] == iw)
		{
			disb.stroperand[i] = "0x" + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0, 4);
			deleteStr(2);
		}
		//����jb��jz
		if (disb.operand[i] == jb)
		{
			disb.stroperand[i] = str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0, 2);
			deleteStr(1);
		}
		else if (disb.operand[i] == jz && disb.Operand_Size == false)
		{
			disb.stroperand[i] = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0, 8);
			deleteStr(4);
		}
		else if (disb.operand[i] == jz && disb.Operand_Size == true)
		{
			disb.stroperand[i] = str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode = disb.allCode + str.Mid(0, 4);
			deleteStr(2);
		}

		//����Gb Gv
		if (disb.operand[i] == Gb )
		{
			disb.stroperand[i] = reg8[disb.reg];
		}
		else if (disb.operand[i] == Gv && disb.Operand_Size == false)
		{
			disb.stroperand[i] = reg32[disb.reg];
		}
		else if (disb.operand[i] == Gv && disb.Operand_Size == true)
		{
			disb.stroperand[i] = reg16[disb.reg];
		}

		//�е�ַ��Сǰ׺
		if (disb.Address_Size)
		{
			//67����eb
			if (disb.operand[i] == Eb)
			{
				if (disb.mod==0 )
				{
					if (disb.rm == 6)//16λ��ַ
					{
						CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
						disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
					else
					{
						disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
					}
					
				}
				else if(disb.mod == 1)
				{
					disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] +"+0x"+str.Mid(0,2) + "]";
					disb.allCode += str.Mid(0, 2);
					disb.allCode += str.Mid(0, 2);
					deleteStr(1);
				}
				else if(disb.mod == 2)
				{
					disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
					disb.allCode += str.Mid(0, 2);
					deleteStr(2);
				}
				
			}
			//67����ev
			if (disb.operand[i] == Ev)
			{
				if (disb.Operand_Size == true)//66��� ,��������Ż����ַ����滻
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16λ��ַ
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				else //û66���
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16λ��ַ
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				
			}
			//67����m
			if (disb.operand[i] == m)
			{
				if (disb.Operand_Size == true)//66��� ,��������Ż����ַ����滻
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16λ��ַ
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				else //û66���
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16λ��ַ
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}

			}
			//67����mp
			if (disb.operand[i] == mp)
			{
				if (disb.Operand_Size == true)//66��� ,��������Ż����ַ����滻
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16λ��ַ
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				else //û66���
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16λ��ַ
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}

			}
			//67����Ew
			if (disb.operand[i] == Ew)
			{
				
				if (disb.mod == 0)
				{
					if (disb.rm == 6)//16λ��ַ
					{
						CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
						disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
					else
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "]";
					}

				}
				else if (disb.mod == 1)
				{
					disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
					disb.allCode += str.Mid(0, 2);
					deleteStr(1);
				}
				else if (disb.mod == 2)
				{
					disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
					disb.allCode += str.Mid(0, 4);
					deleteStr(2);
				}
			}

		}
		//eb
		else if (disb.operand[i] == Eb)
		{
			if (disb.mod == 3)//r  r
			{
				disb.stroperand[i] = reg8[disb.rm];
			}
			else if (disb.mod == 0 && disb.rm == 5)//r  r   rm=[dis32]
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
				
			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] +"+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] +"+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if(disb.rm == 4 && disb.mod !=3)//��sib����
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + Sib�����ַƫ��(disb)+ "]";
			}
		}
		//ev
		else if (disb.operand[i] == Ev)
		{
			if (disb.mod == 3)//r  r
			{
				disb.stroperand[i] = reg32[disb.rm];
			}
			else if (disb.mod == 0 && disb.rm == 5)//r  r   rm=[dis32]
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//��sib����
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + Sib�����ַƫ��(disb) + "]";
			}
			//�����������С
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("dword", "word");
			}
		}

		//fd
		if (disb.operand[i]==fd)
		{
			if (disb.Operand_Size)
			{
				disb.stroperand[i] = "fw";
			}
			else
			{
				disb.stroperand[i] = "fd";
			}
		}

		//yb
		if (disb.operand[i]==yb)
		{
			if (disb.Address_Size)
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "di" + "]";
			}
			else
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "edi" + "]";
			}
		}
		//xb
		if (disb.operand[i]==xb)
		{
			if (disb.Address_Size)
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "si" + "]";
			}
			else
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "esi" + "]";
			}
		}
		//yz
		if (disb.operand[i]==yz)
		{
			if (disb.Address_Size)
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "di" + "]";
			}
			else
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "edi" + "]";
			}
			//�����������С
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("dword", "word");
			}

		}
		//xz
		if (disb.operand[i]==xz)
		{
			if (disb.Address_Size)
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "si" + "]";
			}
			else
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "esi" + "]";
			}
			//�����������С
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("dword", "word");
			}

		}

		//ob
		if (disb.operand[i]==ob)
		{
			if (disb.Address_Size)
			{
				CString  strtemp =  str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "["  + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 4);
				deleteStr(2);
			}
			else
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
		}
		//ov
		if (disb.operand[i]==ov)
		{
			if (disb.Address_Size)
			{
				CString  strtemp =  str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "["  + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 4);
				deleteStr(2);
			}
			else
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			//�����������С
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("dword", "word");
			}
		}
		
		//sw
		if (disb.operand[i]==Sw)
		{
			disb.stroperand[i] = swList[disb.reg];
		}

		//m   ֻ�����ڴ� dword ptr ds:[]
		if (disb.operand[i] == m && disb.Address_Size == false)
		{
			if (disb.mod == 3)//r  r
			{
			//	disb.stroperand[i] = reg8[disb.rm];
				disb.stroperand[i] = "eorr:only m";
			}
			else if (disb.mod == 0 && disb.rm == 5)//r  r   rm=[dis32]
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//��sib����
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.��ǰ׺] + "[" + Sib�����ַƫ��(disb) + "]";
			}
			//�����������С
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("dword", "word");
			}
		}

		//mp  fword ptr ds:[]
		if (disb.operand[i] == mp && disb.Address_Size==false)
		{
			if (disb.mod == 3)//r  r
			{
				//	disb.stroperand[i] = reg8[disb.rm];
				disb.stroperand[i] = "eorr:only m";
			}
			else if (disb.mod == 0 && disb.rm == 5)//r  r   rm=[dis32]
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//��sib����
			{
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.��ǰ׺] + "[" + Sib�����ַƫ��(disb) + "]";
			}
			//�����������С
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("fword", "dword");
			}
		}

		//num1 ����1
		if (disb.operand[i]==num1)
		{
			disb.stroperand[i] = "1";
		}

		//Ew
		if (disb.operand[i] == Ew)
		{
			if (disb.mod == 3)//r  r
			{
				disb.stroperand[i] = reg8[disb.rm];
			}
			else if (disb.mod == 0 && disb.rm == 5)//r  r   rm=[dis32]
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//��sib����
			{
				disb.stroperand[i] = "word ptr " + Strprefix[disb.��ǰ׺] + "[" + Sib�����ַƫ��(disb) + "]";
			}
	
		}

		//Gw
		if (disb.operand[i]==Gw)
		{
			disb.stroperand[i] = adds16[disb.reg];
		}

		//ad
		if (disb.operand[i]==ad)
		{
			if (disb.Operand_Size)
			{
				disb.stroperand[i] = "aw";
			}
			else
			{
				disb.stroperand[i] = "ad";
			}
		}

		//ap
		if (disb.operand[i]==ap)
		{
			if (disb.Operand_Size)
			{
				CString  strtemp = "0000" + str.Mid(2, 2) + str.Mid(0, 2);
				CString  strtemp2 = str.Mid(6, 2) + str.Mid(4, 2);
				disb.stroperand[i] = "far " + '0' + strtemp2 + ":" + strtemp;
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				CString  strtemp2 = str.Mid(10, 2) + str.Mid(8, 2);
				disb.stroperand[i] = "far " + '0' + strtemp2 + ":" + strtemp;
				disb.allCode += str.Mid(0, 12);
				deleteStr(6);
			}
		}
	}


	//�鴦��
	if (disb.mnemonic=="Grp")
	{
		if (disb.opcode==0x80 || disb.opcode == 0x81|| disb.opcode == 0x82 || disb.opcode == 0x83)
		{
			disb.mnemonic = Grp1[disb.reg];
		}
		else if (disb.opcode == 0x8f)
		{
			disb.mnemonic = "pop";
		}
		else if (disb.opcode == 0xc0 || disb.opcode == 0xc1 || disb.opcode == 0xd0|| disb.opcode == 0xd1 || disb.opcode == 0xd2 || disb.opcode == 0xd3)
		{
			disb.mnemonic = Grp2[disb.reg];
		}
		else if (disb.opcode == 0xc6 || disb.opcode == 0xc7 )
		{
			disb.mnemonic = "mov";
		}
	}

	disb.assembly = disb.mnemonic + " " + disb.stroperand[0] + "," + disb.stroperand[1] + "," + disb.stroperand[2];
	
	//ɾ��β��,��,,
	for (int i = 0; i < 3; i++)
	{
		if (disb.assembly[disb.assembly.GetLength()-1] == ',')
		{
			disb.assembly.Delete(disb.assembly.GetLength()-1, 1);
		}
	}
	disb.length = disb.allCode.GetLength() / 2;

	//67Ӱ�������ָ�� cdq  xlatb  jrcxz
	if (disb.Operand_Size)
	{
		//cdq����
		if (disb.mnemonic=="cdq")
		{
			disb.assembly.Replace("cdq", "cwd");
		}
		//xlatb����
		if (disb.mnemonic == "xlatb")
		{
			disb.assembly.Replace("ebx", "bx");
		}
		//jrcxz����
		if (disb.mnemonic == "jrcxz")
		{
			disb.assembly.Replace("jrcxz", "jcxz");
		}
		
	}
	//0x8c mov ���� ��word �������滻
	if (disb.opcode == 0x8c)
	{
		disb.assembly.Replace("dword", "word");
	}

	TRACE(disb.allCode + "--" + disb.assembly + "\n");
}

bool VLE::deleteStr(int num)//num���ֽ���
{
	str = str.Mid(num*2);
	return true;
}
void VLE::Handling_prefix(ָ�����type& disb,int refix)
{
	switch (refix)
	{
	case 0x26:
		disb.��ǰ׺ = es;
		break;
	case 0x2e:
		disb.��ǰ׺ = cs;
		break;
	case 0x36:
		disb.��ǰ׺ = ss;
		break;
	case 0x3e:
		disb.��ǰ׺ = ds;
		break;
	case 0x64:
		disb.��ǰ׺ = fs;
		break;
	case 0x65:
		disb.��ǰ׺ = gs;
		break;
	case 0x66:
		disb.Operand_Size = true;
		break;
	case 0x67:
		disb.Address_Size = true;
		break;
	case 0xf0:
		disb.lock = true;
		break;
	case 0xf2:
		disb.rep = repne;
		break;
	case 0xf3:
		disb.rep = rep;
		break;
	default:
		break;
	}
}
bool VLE::�ж�modrm(const ָ�����type& disb)
{
	if (disb.operand[0] >= 0x60 && disb.operand[0] < 0x70)
	{
		return true;
	}
	if (disb.operand[1] >= 0x60 && disb.operand[1] < 0x70)
	{
		return true;
	}
	return false;
}
void VLE::����_����operands(mnemonicType& operand, CString& stroperand)
{
	
}

bool VLE::�ж�Sib(const ָ�����type& disb)
{
	
	int imodrm = disb.modrm;
	if ((imodrm & 0xc0) != 0xc0)//�ж���00 01 10 ���Һ���λ��100
	{
		if ((imodrm & 0x07) == 0x4)
		{
			return true;
		}
	}

	return false;
	
}
void VLE::����modrm��sib(ָ�����type& disb)
{
	if (disb.modrm!=0)
	{
		disb.reg = disb.modrm >> 3 & 0x7;
		disb.mod = disb.modrm >> 6;
		disb.rm = disb.modrm & 0x7;
	}
	if (disb.sib != 0)
	{
		disb.scale = disb.sib>>6;
		disb.index = disb.sib >> 3 & 0x7;
		disb.base = disb.sib  & 0x7;
	}
}
CString VLE::Sib�����ַƫ��(ָ�����type& disb)
{
	CString retStr;
	if (disb.mod==0 && disb.rm == 4 && disb.base == 5)   //base = dis32
	{
		if (disb.mod !=3 && disb.rm==4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100
		{
			retStr="0x"+ str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode += str.Mid(0, 8);
			deleteStr(4);
		}
		else
		{
			CString temp;
			temp.Format("%d", 1 << disb.scale);
			retStr = reg32[disb.index] + "*" + temp + "+0x" + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);	
			disb.allCode += str.Mid(0, 8);
			deleteStr(4);
		}
	}
	else if (disb.mod == 0)
	{
		if (disb.mod != 3 && disb.rm == 4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100 û��index ��scale
		{
			retStr = reg32[disb.base];
		}
		else
		{
			CString temp;
			temp.Format("%d", 1 << disb.scale);
			retStr = reg32[disb.base] + "+" + reg32[disb.index] + "*" + temp;
		}
	}
	else if (disb.mod == 1)
	{
		if (disb.mod != 3 && disb.rm == 4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100 û��index ��scale
		{
			retStr = reg32[disb.base]+"+" + "0x" + str.Mid(0, 2);
			disb.allCode += str.Mid(0, 2);
			deleteStr(1);
		}
		else
		{
			CString temp;
			temp.Format("%d", 1 << disb.scale);
			retStr = reg32[disb.base] + "+" + reg32[disb.index] + "*" + temp+"+" + "0x" + str.Mid(0, 2);
			disb.allCode += str.Mid(0, 2);
			deleteStr(1);
		}
	}	
	else if (disb.mod == 2)
	{
		if (disb.mod != 3 && disb.rm == 4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100 û��index ��scale
		{
			retStr = reg32[disb.base]+"+" + "0x" + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode += str.Mid(0, 8);
			deleteStr(4);
		}
		else
		{
			CString temp;
			temp.Format("%d", 1 << disb.scale);
			retStr = reg32[disb.base] + "+" + reg32[disb.index] + "*" + temp+"+" + "0x" + str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
			disb.allCode += str.Mid(0, 8);
			deleteStr(4);
		}
	}
	return retStr;
}