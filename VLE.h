#pragma once
#include "config.h"
#include"GlobalCommands.h"
class VLE
{
private:
	std::vector<ָ�����type> v����ָ�;

	CString str;//��������ַ���
public:
	static int findOpcode(const CString & str);//��������str,,�����ҵ�������,�Ҳ�������-1
	int readOpcode(CString can_str);//��������str,,�����ҵ�������,�Ҳ�������-1

	//���������ַ���,����ı���,��ɾ����
	bool deleteStr(int num);

	//����ǰ׺
	void VLE::Handling_prefix(ָ�����type& newָ��, int refix);
	void VLE::Handle_Opcode(ָ�����type& newָ��, int index);
	bool VLE::�ж�modrm(const ָ�����type& newָ��);
	bool VLE::�ж�Sib(const ָ�����type& newָ��);
	void VLE::����modrm��sib(ָ�����type& newָ��);
	void VLE::Process_operands(ָ�����type& newָ��);
	void VLE::����_����operands(mnemonicType& operand, CString& stroperand);
};

