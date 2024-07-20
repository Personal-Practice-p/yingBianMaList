#pragma once
#include "config.h"
enum ��ǰ׺enum
{
	es,
	cs,
	ss,
	ds,
	fs,
	gs
};
enum repType
{
	rep_none,
	rep,
	repne
};
struct ָ�����type
{
	��ǰ׺enum ��ǰ׺;
	bool Operand_Size;
	bool Address_Size;
	repType rep;
	uint8_t opcode;
	std::string mnemonic;           // ���Ƿ�
	mnemonicType operand1;           // ������1����
	mnemonicType operand2;           // ������2����
	mnemonicType operand3;           // ������3����

	uint8_t modrm;
	uint8_t sib;
	uint8_t mod;
	uint8_t reg;
	uint8_t rm;
	uint8_t scale;
	uint8_t index;
	uint8_t base;

	std::string stroperand1;           // ������1ֵ
	std::string stroperand2;           // ������2ֵ
	std::string stroperand3;           // ������3ֵ
	int length;
	CString assembly;//����õ����������ָ��
	CString allcode;//����ָ�������Ӳ����
};

class VLE
{
private:
	std::vector<ָ�����type> v����ָ�;
public:
	static int findOpcode(const CString & str);//��������str,,�����ҵ�������,�Ҳ�������-1
	int readOpcode(CString& str);//��������str,,�����ҵ�������,�Ҳ�������-1
};

