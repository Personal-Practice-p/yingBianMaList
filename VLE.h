#pragma once
#include "config.h"
#include"GlobalCommands.h"
class VLE
{
private:
	CString str;//��������ַ���
public:
	std::vector<ָ�����type> v����ָ�;

	
	static int findOpcode(const CString & str);//��������str,,�����ҵ�������,�Ҳ�������-1
	int readOpcode(CString can_str);//��������str,,�����ҵ�������,�Ҳ�������-1

	//���������ַ���,����ı���,��ɾ����
	bool deleteStr(int num);

	//����ǰ׺
	void VLE::Handling_prefix(ָ�����type& disb, int refix);
	void VLE::Handle_Opcode(ָ�����type& disb, int index);
	bool VLE::�ж�modrm(const ָ�����type& disb);
	bool VLE::�ж�Sib(const ָ�����type& disb);
	void VLE::����modrm��sib(ָ�����type& disb);
	void VLE::Process_operands(ָ�����type& disb);
	void VLE::����_����operands(mnemonicType& operand, CString& stroperand);

	//����sib���� []������ַ���
	CString VLE::Sib�����ַƫ��(ָ�����type& disb);
	void VLE::eorr_Opcode(ָ�����type& disb, int code);
};

