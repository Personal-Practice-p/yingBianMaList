#pragma once
#include "config.h"
#include"GlobalCommands.h"
class VLE
{
private:
	std::vector<ָ�����type> v����ָ�;
public:
	static int findOpcode(const CString & str);//��������str,,�����ҵ�������,�Ҳ�������-1
	int readOpcode(CString& str);//��������str,,�����ҵ�������,�Ҳ�������-1

	//���������ַ���,����ı���,��ɾ����
	bool deleteStr(CString& str, int num);

	//����ǰ׺
	void VLE::Handling_prefix(ָ�����type& newָ��, int refix);
};

