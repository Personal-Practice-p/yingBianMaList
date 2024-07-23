#include "pch.h"
#include"VLE.h"


int VLE::findOpcode(const CString& str)//传入整个str
{
	return 0;
}
int VLE::readOpcode(CString can_str)//传入整个str
{
	int onlyone=0;
	str = can_str;
	while (str!="")
	{

		unsigned int Code = 0;
		int prefixFlag = 0;
		CString strCode;

		指令解码type disb;


		while (prefixFlag != 3)
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
					Handling_prefix(disb, Code);
					disb.allCode = disb.allCode + strCode;
					TRACE("前缀:" + strCode + "\n");
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
		//处理opcode
		//2个字节的
		if (Code == 0x0f)
		{
			strCode.Format("%02x", Code);
			strCode += str.Mid(2,2);
			Code= strtol(strCode, NULL, 16);
		}

		for (int i = 0; i < v指令集.size(); i++)
		{
			if (v指令集[i].opcode == Code)
			{
				find = 1;
				onlyone = 1;
				//找到
				TRACE("opcode:" + strCode + v指令集[i].mnemonic + "\n");
				Handle_Opcode(disb, i);
				disb.allCode = disb.allCode + strCode+" ";
				if (Code>0xff)//判断下是否是双字节代码
				{
					deleteStr(2);
				}
				else
				{
					deleteStr(1);
				}
				
			}
		}
		//需要让这段代码只执行一次
		if (find == 0 && onlyone==0)//没找到
		{
			onlyone = 1;
			eorr_Opcode(disb, Code);
			
			
			if (Code > 0xff)//判断下是否是双字节代码
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
			v解码指令集.push_back(disb);//ruku
			continue;
		}
		//处理modrm
		if (判断modrm(disb))
		{
			//为true 有modrm
			if (str.IsEmpty())
			{
				disb.assembly = "db 00";
				v解码指令集.push_back(disb);//ruku
				continue;
			}

			disb.modrm = strtol(str.Mid(0, 2), NULL, 16);
			disb.allCode += str.Mid(0, 2)+" ";
			deleteStr(1);
			if (判断Sib(disb))
			{
				disb.sib = strtol(str.Mid(0, 2), NULL, 16);
				disb.allCode += str.Mid(0, 2)+ " ";
				deleteStr(1);
			}
		}
		处理modrm和sib(disb);

		Process_operands(disb);
		v解码指令集.push_back(disb);//ruku
		onlyone = 0;
	}

	

	return 0;
}

void VLE::Handle_Opcode(指令解码type& disb, int index)
{
	disb.opcode = v指令集[index].opcode;
	disb.mnemonic = v指令集[index].mnemonic;

	disb.operand[0] = v指令集[index].operand1;
	disb.operand[1] = v指令集[index].operand2;
	disb.operand[2] = v指令集[index].operand3;
	

}
void VLE::eorr_Opcode(指令解码type& disb, int code)
{
	CString temp;
	temp.Format("%x", code);
	//disb.allCode = temp;
	disb.assembly = "eorr no find opcode";
}
void VLE::Process_operands(指令解码type& disb)
{
	
	for (int i = 0; i < 3; i++)
	{
		//操作数为寄存器
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

		//操作数为立即数
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
		//处理jb和jz
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

		//处理Gb Gv
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

		//有地址大小前缀
		if (disb.Address_Size)
		{
			//67处理eb
			if (disb.operand[i] == Eb)
			{
				if (disb.mod==0 )
				{
					if (disb.rm == 6)//16位地址
					{
						CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
						disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
					else
					{
						disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
					}
					
				}
				else if(disb.mod == 1)
				{
					disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] +"+0x"+str.Mid(0,2) + "]";
					disb.allCode += str.Mid(0, 2);
					disb.allCode += str.Mid(0, 2);
					deleteStr(1);
				}
				else if(disb.mod == 2)
				{
					disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
					disb.allCode += str.Mid(0, 2);
					deleteStr(2);
				}
				
			}
			//67处理ev
			if (disb.operand[i] == Ev)
			{
				if (disb.Operand_Size == true)//66情况 ,这个可以优化成字符串替换
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16位地址
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				else //没66情况
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16位地址
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				
			}
			//67处理m
			if (disb.operand[i] == m)
			{
				if (disb.Operand_Size == true)//66情况 ,这个可以优化成字符串替换
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16位地址
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				else //没66情况
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16位地址
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}

			}
			//67处理mp
			if (disb.operand[i] == mp)
			{
				if (disb.Operand_Size == true)//66情况 ,这个可以优化成字符串替换
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16位地址
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}
				else //没66情况
				{
					if (disb.mod == 0)
					{
						if (disb.rm == 6)//16位地址
						{
							CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
							disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
							disb.allCode += str.Mid(0, 4);
							deleteStr(2);
						}
						else
						{
							disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
						}

					}
					else if (disb.mod == 1)
					{
						disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 2);
						deleteStr(1);
					}
					else if (disb.mod == 2)
					{
						disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
				}

			}
			//67处理Ew
			if (disb.operand[i] == Ew)
			{
				
				if (disb.mod == 0)
				{
					if (disb.rm == 6)//16位地址
					{
						CString  strtemp = str.Mid(2, 2) + str.Mid(0, 2);
						disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
						disb.allCode += str.Mid(0, 4);
						deleteStr(2);
					}
					else
					{
						disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "]";
					}

				}
				else if (disb.mod == 1)
				{
					disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(0, 2) + "]";
					disb.allCode += str.Mid(0, 2);
					deleteStr(1);
				}
				else if (disb.mod == 2)
				{
					disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + adds16[disb.rm] + "+0x" + str.Mid(2, 2) + str.Mid(0, 2) + "]";
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
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
				
			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] +"+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] +"+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if(disb.rm == 4 && disb.mod !=3)//有sib处理
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + Sib处理地址偏移(disb)+ "]";
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
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//有sib处理
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + Sib处理地址偏移(disb) + "]";
			}
			//处理操作数大小
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
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "di" + "]";
			}
			else
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "edi" + "]";
			}
		}
		//xb
		if (disb.operand[i]==xb)
		{
			if (disb.Address_Size)
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "si" + "]";
			}
			else
			{
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "esi" + "]";
			}
		}
		//yz
		if (disb.operand[i]==yz)
		{
			if (disb.Address_Size)
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "di" + "]";
			}
			else
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "edi" + "]";
			}
			//处理操作数大小
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
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "si" + "]";
			}
			else
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "esi" + "]";
			}
			//处理操作数大小
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
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "["  + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 4);
				deleteStr(2);
			}
			else
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "byte ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
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
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "["  + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 4);
				deleteStr(2);
			}
			else
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			//处理操作数大小
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

		//m   只能是内存 dword ptr ds:[]
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
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//有sib处理
			{
				disb.stroperand[i] = "dword ptr " + Strprefix[disb.段前缀] + "[" + Sib处理地址偏移(disb) + "]";
			}
			//处理操作数大小
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
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//有sib处理
			{
				disb.stroperand[i] = "fword ptr " + Strprefix[disb.段前缀] + "[" + Sib处理地址偏移(disb) + "]";
			}
			//处理操作数大小
			if (disb.Operand_Size)
			{
				disb.stroperand[i].Replace("fword", "dword");
			}
		}

		//num1 数字1
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
				disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);

			}
			else if (disb.mod == 0 && disb.rm != 4)//r  r   rm=[eax-edi]
			{
				disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "]";
			}
			else if (disb.mod == 1 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(0, 2);
				disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 2);
				deleteStr(1);
			}
			else if (disb.mod == 2 && disb.rm != 4)
			{
				CString  strtemp = str.Mid(6, 2) + str.Mid(4, 2) + str.Mid(2, 2) + str.Mid(0, 2);
				disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + reg32[disb.rm] + "+" + "0x" + strtemp + "]";
				disb.allCode += str.Mid(0, 8);
				deleteStr(4);
			}
			else if (disb.rm == 4 && disb.mod != 3)//有sib处理
			{
				disb.stroperand[i] = "word ptr " + Strprefix[disb.段前缀] + "[" + Sib处理地址偏移(disb) + "]";
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


	//组处理
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
	
	//删除尾部,和,,
	for (int i = 0; i < 3; i++)
	{
		if (disb.assembly[disb.assembly.GetLength()-1] == ',')
		{
			disb.assembly.Delete(disb.assembly.GetLength()-1, 1);
		}
	}
	disb.length = disb.allCode.GetLength() / 2;

	//67影响的特殊指令 cdq  xlatb  jrcxz
	if (disb.Operand_Size)
	{
		//cdq处理
		if (disb.mnemonic=="cdq")
		{
			disb.assembly.Replace("cdq", "cwd");
		}
		//xlatb处理
		if (disb.mnemonic == "xlatb")
		{
			disb.assembly.Replace("ebx", "bx");
		}
		//jrcxz处理
		if (disb.mnemonic == "jrcxz")
		{
			disb.assembly.Replace("jrcxz", "jcxz");
		}
		
	}
	//0x8c mov 特殊 是word 这里做替换
	if (disb.opcode == 0x8c)
	{
		disb.assembly.Replace("dword", "word");
	}

	TRACE(disb.allCode + "--" + disb.assembly + "\n");
}

bool VLE::deleteStr(int num)//num是字节数
{
	str = str.Mid(num*2);
	return true;
}
void VLE::Handling_prefix(指令解码type& disb,int refix)
{
	switch (refix)
	{
	case 0x26:
		disb.段前缀 = es;
		break;
	case 0x2e:
		disb.段前缀 = cs;
		break;
	case 0x36:
		disb.段前缀 = ss;
		break;
	case 0x3e:
		disb.段前缀 = ds;
		break;
	case 0x64:
		disb.段前缀 = fs;
		break;
	case 0x65:
		disb.段前缀 = gs;
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
bool VLE::判断modrm(const 指令解码type& disb)
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
void VLE::功能_处理operands(mnemonicType& operand, CString& stroperand)
{
	
}

bool VLE::判断Sib(const 指令解码type& disb)
{
	
	int imodrm = disb.modrm;
	if ((imodrm & 0xc0) != 0xc0)//判断是00 01 10 并且后三位是100
	{
		if ((imodrm & 0x07) == 0x4)
		{
			return true;
		}
	}

	return false;
	
}
void VLE::处理modrm和sib(指令解码type& disb)
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
CString VLE::Sib处理地址偏移(指令解码type& disb)
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
		if (disb.mod != 3 && disb.rm == 4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100 没有index 和scale
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
		if (disb.mod != 3 && disb.rm == 4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100 没有index 和scale
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
		if (disb.mod != 3 && disb.rm == 4 && disb.index == 4)//mod == 00   01  10   rm == 100   index == 100 没有index 和scale
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