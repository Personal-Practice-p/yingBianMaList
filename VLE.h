#pragma once


struct bianChangType
{
	CString opcode;
	CString ass;
	CString operand1;
	CString operand2;
	CString operand3;//这个大部分为NULL
};
const bianChangType bianchang[] =
{
	{"00","add","Eb","Gb",NULL},
	{"01","add","Eb","Gv",NULL},
	{"02","add","Gb","Eb",NULL},
	{"03","add","Gv","Ev",NULL},

	{"08","or","Eb","Gb",NULL},
	{"09","or","Eb","Gv",NULL},
	{"0a","or","Gb","Eb",NULL},
	{"0b","or","Gv","Ev",NULL},

	{"10","adc","Eb","Gb",NULL},
	{"11","adc","Eb","Gv",NULL},
	{"12","adc","Gb","Eb",NULL},
	{"13","adc","Gv","Ev",NULL},

	{"18","sbb","Eb","Gb",NULL},
	{"19","sbb","Eb","Gv",NULL},
	{"1a","sbb","Gb","Eb",NULL},
	{"1b","sbb","Gv","Ev",NULL},

	{"20","and","Eb","Gb",NULL},
	{"21","and","Eb","Gv",NULL},
	{"22","and","Gb","Eb",NULL},
	{"23","and","Gv","Ev",NULL}
};
class VLE
{
public:
	static int findOpcode(const CString & str);//传入整个str,,返回找到的索引,找不到返回-1
};
