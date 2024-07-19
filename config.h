#pragma once
#include<unordered_map>
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
	eax,
	ecx
};
struct InstructionDescriptor
{
	uint8_t opcode;                 // 操作码
	std::string mnemonic;           // 助记符
	mnemonicType operand1;           // 操作数1类型
	mnemonicType operand2;           // 操作数2类型
	mnemonicType operand3;           // 操作数3类型
};



InstructionDescriptor v指令集[] =
{
	{0x40,"inc",eax,none,none},
	{0x41,"inc",ecx,none,none},

	{0x90,"nop",none,none,none},
	{0x8b,"mov",Gv,Ev,none}
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