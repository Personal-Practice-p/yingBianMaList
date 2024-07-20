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
	none,
	Ib,
	Iz,
	Iv,
	Eb,
	Gb,
	Ev,
	Gv,
	ad,

	jb,//和ib同一种操作,先写开,方便以后处理
	jz,//和iz同一种操作,先写开,方便以后处理

	yb,
	yz,
	xb,
	xz,

	eax=0x10,
	ecx,
	edx,
	ebx,
	esp,
	ebp,
	esi,
	edi,
	al=0x20,//取右边知道寄存器的编号,取左边知道寄存器的类型
	cl,
	dl,
	bl,
	ah,
	ch,
	dh,
	bh,
	ax=30,
	cx,
	dx,
	bx,
	sp,
	bp,
	si,
	di
};
struct InstructionDescriptor
{
	uint8_t opcode;                 // 操作码
	std::string mnemonic;           // 助记符
	mnemonicType operand1;           // 操作数1类型
	mnemonicType operand2;           // 操作数2类型
	mnemonicType operand3;           // 操作数3类型
};

struct prefixtype
{
	uint8_t opcode;
	std::string mnemonic;
};

InstructionDescriptor v指令集[] =
{
	{0x40,"inc",eax,none,none},
	{0x41,"inc",ecx,none,none},
	{0x42,"inc",edx,none,none},
	{0x43,"inc",ebx,none,none},
	{0x44,"inc",esp,none,none},
	{0x45,"inc",ebp,none,none},
	{0x46,"inc",esi,none,none},
	{0x47,"inc",edi,none,none},

	{0x48,"dec",eax,none,none},
	{0x49,"dec",ecx,none,none},
	{0x4a,"dec",edx,none,none},
	{0x4b,"dec",ebx,none,none},
	{0x4c,"dec",esp,none,none},
	{0x4d,"dec",ebp,none,none},
	{0x4e,"dec",esi,none,none},
	{0x4f,"dec",edi,none,none},

	{0x50,"push",eax,none,none},
	{0x51,"push",ecx,none,none},
	{0x52,"push",edx,none,none},
	{0x53,"push",ebx,none,none},
	{0x54,"push",esp,none,none},
	{0x55,"push",ebp,none,none},
	{0x56,"push",esi,none,none},
	{0x57,"push",edi,none,none},

	{0x58,"pop",eax,none,none},
	{0x59,"pop",ecx,none,none},
	{0x5a,"pop",edx,none,none},
	{0x5b,"pop",ebx,none,none},
	{0x5c,"pop",esp,none,none},
	{0x5d,"pop",ebp,none,none},
	{0x5e,"pop",esi,none,none},
	{0x5f,"pop",edi,none,none},

	{0xb0,"mov",al,Ib,none},
	{0xb1,"mov",cl,Ib,none},
	{0xb2,"mov",dl,Ib,none},
	{0xb3,"mov",bl,Ib,none},
	{0xb4,"mov",ah,Ib,none},
	{0xb5,"mov",ch,Ib,none},
	{0xb6,"mov",dh,Ib,none},
	{0xb7,"mov",bh,Ib,none},

	{0xb8,"mov",eax,Iv,none},
	{0xb9,"mov",ecx,Iv,none},
	{0xba,"mov",edx,Iv,none},
	{0xbb,"mov",ebx,Iv,none},
	{0xbc,"mov",esp,Iv,none},
	{0xbd,"mov",ebp,Iv,none},
	{0xbe,"mov",esi,Iv,none},
	{0xbf,"mov",edi,Iv,none},


	{0x90,"nop",none,none,none},
	{0x91,"xchg",eax,ecx,none},
	{0x92,"xchg",eax,edx,none},
	{0x93,"xchg",eax,ebx,none},
	{0x94,"xchg",eax,esp,none},
	{0x95,"xchg",eax,ebp,none},
	{0x96,"xchg",eax,esi,none},
	{0x97,"xchg",eax,edi,none},

	{0x04,"add",al,Ib,none},
	{0x05,"add",eax,Iz,none},
	{0x06,"push es",none,none,none},//不受前缀影响
	{0x07,"pop es",none,none,none},//不受前缀影响
	
	{0x0c,"or",al,Ib,none},
	{0x0d,"or",eax,Iz,none},
	{0x0e,"push cs",none,none,none},//不受前缀影响
	{0x0f,"两个字节编码表",none,none,none},

	{0x14,"adc",al,Ib,none},
	{0x15,"adc",eax,Iz,none},
	{0x16,"push ss",none,none,none},//不受前缀影响
	{0x17,"pop ss",none,none,none},//不受前缀影响

	{0x1c,"sbb",al,Ib,none},
	{0x1d,"sbb",eax,Iz,none},
	{0x1e,"push ds",none,none,none},//不受前缀影响
	{0x1f,"pop ds",none,none,none},//不受前缀影响

	{0x24,"and",al,Ib,none},
	{0x25,"and",eax,Iz,none},
	{0x27,"daa",none,none,none},

	{0x2c,"sub",al,Ib,none},
	{0x2d,"sub",eax,Iz,none},
	{0x2f,"das",none,none,none},

	{0x34,"xor",al,Ib,none},
	{0x35,"xor",eax,Iz,none},
	{0x37,"aaa",none,none,none},

	{0x3c,"cmp",al,Ib,none},
	{0x3d,"cmp",eax,Iz,none},
	{0x3f,"aas",none,none,none},

	{0x60,"push",ad,none,none},
	{0x61,"pop",ad,none,none},

	{0x68,"push",Iz,none,none},
	{0x6a,"push",Ib,none,none},

	{0x6c,"insb",yb,dx,none},
	{0x6d,"insd",yz,dx,none},
	{0x6e,"outsb",dx,xb,none},
	{0x6f,"outsd",dx,xz,none},

	{0x70,"jo",jb,none,none},
	{0x71,"jno",jb,none,none},
	{0x72,"jb",jb,none,none},
	{0x73,"jnb",jb,none,none},
	{0x74,"je",jb,none,none},
	{0x75,"jnz",jb,none,none},
	{0x76,"jbe",jb,none,none},
	{0x77,"ja",jb,none,none},
	{0x78,"js",jb,none,none},
	{0x79,"jns",jb,none,none},
	{0x7a,"jpe",jb,none,none},
	{0x7b,"jpo",jb,none,none},
	{0x7c,"jl",jb,none,none},
	{0x7d,"jge",jb,none,none},
	{0x7e,"jle",jb,none,none},
	{0x7f,"jg",jb,none,none},

	{0x0f80,"jo",jz,none,none},
	{0x0f81,"jno",jz,none,none},
	{0x0f82,"jb",jz,none,none},
	{0x0f83,"jnb",jz,none,none},
	{0x0f84,"je",jz,none,none},
	{0x0f85,"jnz",jz,none,none},
	{0x0f86,"jbe",jz,none,none},
	{0x0f87,"ja",jz,none,none},
	{0x0f88,"js",jz,none,none},
	{0x0f89,"jns",jz,none,none},
	{0x0f8a,"jpe",jz,none,none},
	{0x0f8b,"jpo",jz,none,none},
	{0x0f8c,"jl",jz,none,none},
	{0x0f8d,"jge",jz,none,none},
	{0x0f8e,"jle",jz,none,none},
	{0x0f8f,"jg",jz,none,none},





	{0x8b,"mov",Gv,Ev,none}
};
InstructionDescriptor prefixList[]
{
	{0x26,"es:",none,none,none},
	{0x2e,"cs:",none,none,none},
	{0x36,"ss:",none,none,none},
	{0x3e,"ds:",none,none,none},
	{0x64,"fs:",none,none,none},
	{0x65,"gs:",none,none,none},
	{0x66,"operandSize:",none,none,none},
	{0x67,"addressSize:",none,none,none},
	{0x67,"addressSize:",none,none,none},
	{0xf0,"lock",none,none,none},
	{0xf2,"rep",none,none,none},
	{0xf3,"repnz",none,none,none},

};
/*
// TODO: 在此处添加实现代码.
//40-47 inc eax-edi
yingbianma2.push_back({ "40","inc eax",1 });
yingbianma2.push_back({ "41","inc ecx",1 });
yingbianma2.push_back({ "42","inc edx",1 });
yingbianma2.push_back({ "43","inc ebx",1 });
yingbianma2.push_back({ "44","inc esp",1 });
yingbianma2.push_back({ "45","inc ebp",1 });
yingbianma2.push_back({ "46","inc esi",1 });
yingbianma2.push_back({ "47","inc edi",1 });

//48-4f  dec eax-edi
yingbianma2.push_back({ "48","dec eax",1 });
yingbianma2.push_back({ "49","dec ecx",1 });
yingbianma2.push_back({ "4a","dec edx",1 });
yingbianma2.push_back({ "4b","dec ebx",1 });
yingbianma2.push_back({ "4c","dec esp",1 });
yingbianma2.push_back({ "4d","dec ebp",1 });
yingbianma2.push_back({ "4e","dec esi" ,1 });
yingbianma2.push_back({ "4f","dec edi",1 });

//50 - 57  push eax - edi
yingbianma2.push_back({ "50","push eax",1 });
yingbianma2.push_back({ "51","push ecx",1 });
yingbianma2.push_back({ "52","push edx",1 });
yingbianma2.push_back({ "53","push ebx",1 });
yingbianma2.push_back({ "54","push esp",1 });
yingbianma2.push_back({ "55","push ebp",1 });
yingbianma2.push_back({ "56","push esi",1 });
yingbianma2.push_back({ "57","push edi",1 });

//58 - 5f  pop eax - edi
yingbianma2.push_back({ "58","pop eax",1 });
yingbianma2.push_back({ "59","pop ecx",1 });
yingbianma2.push_back({ "5a","pop edx",1 });
yingbianma2.push_back({ "5b","pop ebx",1 });
yingbianma2.push_back({ "5c","pop esp",1 });
yingbianma2.push_back({ "5d","pop ebp" ,1 });
yingbianma2.push_back({ "5e","pop esi",1 });
yingbianma2.push_back({ "5f","pop edi",1 });

//
//XCHG
yingbianma2.push_back({ "90","nop",1 });
yingbianma2.push_back({ "91","xchg eax,ecx",1 });
yingbianma2.push_back({ "92","xchg eax,edx",1 });
yingbianma2.push_back({ "93","xchg eax,ebx",1 });
yingbianma2.push_back({ "94","xchg eax,esp",1 });
yingbianma2.push_back({ "95","xchg eax,ebp",1 });
yingbianma2.push_back({ "96","xchg eax,esi",1 });
yingbianma2.push_back({ "97","xchg eax,edi" ,1 });

//多字节硬编码
//b0 - b7  mov al-bh  占2字节
yingbianma2.push_back(DuozijieBianMa("b0", "mov al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b1", "mov cl,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b2", "mov dl,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b3", "mov bl,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b4", "mov ah,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b5", "mov ch,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b6", "mov dh,ib", 2));
yingbianma2.push_back(DuozijieBianMa("b7", "mov bh,ib", 2));

//b8 - bf mov eax-edi 占5个字节
yingbianma2.push_back(DuozijieBianMa("b8", "mov eax,iv", 5));
yingbianma2.push_back(DuozijieBianMa("b9", "mov ecx,iv", 5));
yingbianma2.push_back(DuozijieBianMa("ba", "mov edx,iv", 5));
yingbianma2.push_back(DuozijieBianMa("bb", "mov ebx,iv", 5));
yingbianma2.push_back(DuozijieBianMa("bc", "mov esp,iv", 5));
yingbianma2.push_back(DuozijieBianMa("bd", "mov ebp,iv", 5));
yingbianma2.push_back(DuozijieBianMa("be", "mov esi,iv", 5));
yingbianma2.push_back(DuozijieBianMa("bf", "mov edi,iv", 5));

//第二天
//单字节
yingbianma2.push_back({ "06","push es",1 });
yingbianma2.push_back({ "07","pop es",1 });
yingbianma2.push_back({ "0e","push cs",1 });
yingbianma2.push_back({ "0f","两个字节编码表 保留",1 });
yingbianma2.push_back({ "16","push ss",1 });
yingbianma2.push_back({ "17","pop ss",1 });
yingbianma2.push_back({ "1e","push ds" ,1 });
yingbianma2.push_back({ "1f","pop ds",1 });
yingbianma2.push_back({ "26","ec(前缀)",1 });
yingbianma2.push_back({ "27","daa",1 });
yingbianma2.push_back({ "2e","cs(前缀)",1 });
yingbianma2.push_back({ "2f","das" ,1 });
yingbianma2.push_back({ "36","ss(前缀)",1 });
yingbianma2.push_back({ "37","aaa" ,1 });
yingbianma2.push_back({ "3e","ds(前缀)",1 });
yingbianma2.push_back({ "3f","aas",1 });

//多字节
yingbianma2.push_back(DuozijieBianMa("04", "add al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("05", "add eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("0c", "or al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("0d", "or eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("14", "adc al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("15", "adc eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("1c", "sbb al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("1d", "sbb eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("24", "and al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("25", "and eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("2c", "sub al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("2d", "sub eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("34", "xor al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("35", "xor eax,iz", 5));
yingbianma2.push_back(DuozijieBianMa("3c", "cmp al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("3d", "cmp eax,iz", 5));

//第三天继续添加
//单字节
yingbianma2.push_back({ "60","pushad" ,1 });
yingbianma2.push_back({ "61","popad" ,1 });

yingbianma2.push_back({ "64","fs(前缀)",1 });
yingbianma2.push_back({ "65","gs(前缀)" ,1 });
yingbianma2.push_back({ "66","操作数大小(前缀)",1 });
yingbianma2.push_back({ "67","地址大小(前缀)",1 });

yingbianma2.push_back({ "6c","insb" ,1 });
yingbianma2.push_back({ "6d","insd" ,1 });
yingbianma2.push_back({ "6e","outsb" ,1 });
yingbianma2.push_back({ "6f","outsd",1 });

yingbianma2.push_back({ "98","cwde",1 });
yingbianma2.push_back({ "99","cdq" ,1 });
yingbianma2.push_back({ "9b","fwait",1 });

yingbianma2.push_back({ "9c","pushfd" ,1 });
yingbianma2.push_back({ "9d","popfd",1 });
yingbianma2.push_back({ "9e","sahf",1 });
yingbianma2.push_back({ "9f","lahf",1 });

yingbianma2.push_back({ "a4","movsb" ,1 });
yingbianma2.push_back({ "a5","movsd",1 });
yingbianma2.push_back({ "a6","cmpsb",1 });
yingbianma2.push_back({ "a7","cmpsd" ,1 });

yingbianma2.push_back({ "aa","stosb",1 });
yingbianma2.push_back({ "ab","stosd" ,1 });

yingbianma2.push_back({ "ac","lodsb",1 });
yingbianma2.push_back({ "ad","lodsd" ,1 });
yingbianma2.push_back({ "ae","scasb" ,1 });
yingbianma2.push_back({ "af","scasd" ,1 });

yingbianma2.push_back({ "c3","ret",1 });
yingbianma2.push_back({ "c9","leave",1 });

yingbianma2.push_back({ "cb","retf",1 });
yingbianma2.push_back({ "cc","int0x3",1 });
yingbianma2.push_back({ "ce","into" ,1 });
yingbianma2.push_back({ "cf","iretd" ,1 });

//多字节
yingbianma2.push_back(DuozijieBianMa("68", "push iz", 5));
yingbianma2.push_back(DuozijieBianMa("6a", "push ib", 2));

yingbianma2.push_back(DuozijieBianMa("70", "jo ib", 2));
yingbianma2.push_back(DuozijieBianMa("71", "jno ib", 2));
yingbianma2.push_back(DuozijieBianMa("72", "jb ib", 2));
yingbianma2.push_back(DuozijieBianMa("73", "jnb ib", 2));
yingbianma2.push_back(DuozijieBianMa("74", "je ib", 2));
yingbianma2.push_back(DuozijieBianMa("75", "jnz ib", 2));
yingbianma2.push_back(DuozijieBianMa("76", "jbe ib", 2));
yingbianma2.push_back(DuozijieBianMa("77", "ja ib", 2));
yingbianma2.push_back(DuozijieBianMa("78", "js ib", 2));
yingbianma2.push_back(DuozijieBianMa("79", "jns ib", 2));
yingbianma2.push_back(DuozijieBianMa("7a", "jpe ib", 2));
yingbianma2.push_back(DuozijieBianMa("7b", "jpo ib", 2));
yingbianma2.push_back(DuozijieBianMa("7c", "jl ib", 2));
yingbianma2.push_back(DuozijieBianMa("7d", "jge ib", 2));
yingbianma2.push_back(DuozijieBianMa("7e", "jle ib", 2));
yingbianma2.push_back(DuozijieBianMa("7f", "jg ib", 2));

//长跳
yingbianma2.push_back(DuozijieBianMa("0f80", "jo iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f81", "jno iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f82", "jb iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f83", "jnb iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f84", "je iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f85", "jnz iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f86", "jbe iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f87", "ja iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f88", "js iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f89", "jns iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f8a", "jpe iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f8b", "jpo iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f8c", "jl iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f8d", "jge iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f8e", "jle iz", 6));
yingbianma2.push_back(DuozijieBianMa("0f8f", "jg iz", 6));


yingbianma2.push_back(DuozijieBianMa("9a", "call  ap", 7));

yingbianma2.push_back(DuozijieBianMa("a0", "mov al,ob", 5));
yingbianma2.push_back(DuozijieBianMa("a1", "mov eax,ov", 5));
//需要优化
yingbianma2.push_back(DuozijieBianMa("a3", "mov ob,al", 5));
yingbianma2.push_back(DuozijieBianMa("a4", "mov ov,eax", 5));

yingbianma2.push_back(DuozijieBianMa("a8", "test al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("a9", "test eax,iz", 5));

yingbianma2.push_back(DuozijieBianMa("c2", "ret iw", 3));
yingbianma2.push_back(DuozijieBianMa("c8", "enter iw ib", 4));

yingbianma2.push_back(DuozijieBianMa("ca", "retf  iw", 3));
yingbianma2.push_back(DuozijieBianMa("cd", "int ib", 2));


//第四天学的硬编码
yingbianma2.push_back(DuozijieBianMa("d4", "aam ib", 2));
yingbianma2.push_back(DuozijieBianMa("d5", "aad ib", 2));

yingbianma2.push_back(DuozijieBianMa("e0", "loopnz Jb", 2));
yingbianma2.push_back(DuozijieBianMa("e1", "loopz Jb", 2));
yingbianma2.push_back(DuozijieBianMa("e2", "loop Jb", 2));
yingbianma2.push_back(DuozijieBianMa("e3", "jrcxz Jb", 2));
yingbianma2.push_back(DuozijieBianMa("e4", "in al,ib", 2));
yingbianma2.push_back(DuozijieBianMa("e5", "in eax,ib", 2));
yingbianma2.push_back(DuozijieBianMa("e6", "out ib,al", 2));
yingbianma2.push_back(DuozijieBianMa("e7", "out ib,eax", 2));
yingbianma2.push_back(DuozijieBianMa("e8", "call jz", 5));
yingbianma2.push_back(DuozijieBianMa("e9", "jmp jz", 5));
yingbianma2.push_back(DuozijieBianMa("ea", "jmp ap", 7));
yingbianma2.push_back(DuozijieBianMa("eb", "jmp Jb", 2));
yingbianma2.push_back(DuozijieBianMa("ec", "in al,dx", 1));
yingbianma2.push_back(DuozijieBianMa("ed", "in eax,dx", 1));
yingbianma2.push_back(DuozijieBianMa("ee", "out dx,al", 1));
yingbianma2.push_back(DuozijieBianMa("ef", "out dx,eax", 1));
yingbianma2.push_back(DuozijieBianMa("f0", "lock", 1));
yingbianma2.push_back(DuozijieBianMa("f2", "repnz", 1));
yingbianma2.push_back(DuozijieBianMa("f3", "repe", 1));
yingbianma2.push_back(DuozijieBianMa("f4", "hlt", 1));
yingbianma2.push_back(DuozijieBianMa("f5", "cmc", 1));
yingbianma2.push_back(DuozijieBianMa("f8", "clc", 1));
yingbianma2.push_back(DuozijieBianMa("f9", "stc", 1));
yingbianma2.push_back(DuozijieBianMa("fa", "cli", 1));
yingbianma2.push_back(DuozijieBianMa("fb", "sti", 1));
yingbianma2.push_back(DuozijieBianMa("fc", "cld", 1));
yingbianma2.push_back(DuozijieBianMa("fd", "std", 1));



//变长编码
yingbianma2.push_back(DuozijieBianMa("88", "mov eb,gb", 0x11));
yingbianma2.push_back(DuozijieBianMa("89", "mov ev,gv", 0x11));
yingbianma2.push_back(DuozijieBianMa("8a", "mov gb,eb", 0x11));
yingbianma2.push_back(DuozijieBianMa("8b", "mov gv,ev", 0x11));
*/