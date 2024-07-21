#pragma once
#include<unordered_map>
#include <vector>
#include<string>

struct modrm
{
	int mod;
	int reg;
	int rm;
};

struct sib
{

	int scale;
	int index;
	int base;
};

enum mnemonicType
{
	//m_none,
	eax = 0x10,
	ecx,
	edx,
	ebx,
	esp,
	ebp,
	esi,
	edi,
	al = 0x20,//ȡ�ұ�֪���Ĵ����ı��,ȡ���֪���Ĵ���������
	cl,
	dl,
	bl,
	ah,
	ch,
	dh,
	bh,
	ax = 0x30,
	cx,
	dx,
	bx,
	sp,
	bp,
	si,
	di,

	jb=0x40,//��ibͬһ�ֲ���,��д��,�����Ժ���
	jz,//��izͬһ�ֲ���,��д��,�����Ժ���

	fd,//eflage�Ĵ��� fw�Ǹı��������
	yb,//byte ptr ds:[esi]
	yz,
	xb,//byte ptr ds:[edi]
	xz,

	ov,
	ob,
	iw,	//imm16
	Sw,	// �μĴ�����ѡ����  es - gs
	m,	//ֻ���ڴ�
	mp,	//fword ptr ds:[]
	num1,	//ֻ����1

	none,
	Ib,
	Iz,
	Iv,

	Eb=0x60,
	Gb,
	Ev,
	Gv,
	Ma,//qword ptr ds:[]
	Ew,//16λ�ڴ�word
	Gw,//16λ�Ĵ���

	ad=0x70,
	ap

};
struct InstructionDescriptor
{
	unsigned int opcode;                 // ������
	CString mnemonic;           // ���Ƿ�
	mnemonicType operand1;           // ������1����
	mnemonicType operand2;           // ������2����
	mnemonicType operand3;           // ������3����
};

struct prefixtype
{
	uint8_t opcode;
	std::string mnemonic;
};



enum ��ǰ׺enum
{
	p_none,
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
	��ǰ׺enum ��ǰ׺= p_none;
	bool Operand_Size=false;
	bool Address_Size = false;
	repType rep=rep_none;
	bool lock=false;
	unsigned int opcode=0;
	CString mnemonic;           // ���Ƿ�
	mnemonicType operand[3] = {none,none,none};           // ������  

	unsigned int modrm=0;
	unsigned int sib=0;
	uint8_t mod=0;
	uint8_t reg=0;  
	uint8_t rm=0;
	uint8_t scale=0;
	uint8_t index=0;												
	uint8_t base=0;

	//���Ӧ���Ǽ�������
	CString stroperand[3];           // ������ֵ
	
	int length=0;
	CString assembly;//����õ����������ָ��
	CString allCode;//����ָ�������Ӳ����
};


