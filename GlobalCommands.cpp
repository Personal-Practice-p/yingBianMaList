#include "pch.h"
#include "GlobalCommands.h"
std::vector<InstructionDescriptor>v指令集 =
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

	{0x98,"cwde",none,none,none},
	{0x99,"cdq",none,none,none},

	{0x9a,"call",ap,none,none},
	{0x9b,"fwait",none,none,none},
	{0x9c,"push",fd,none,none},
	{0x9d,"pop",fd,none,none},

	{0x9e,"sahf",none,none,none},
	{0x9f,"lahf",none,none,none},

	{0xa0,"mov",al,ob,none},//ov和ob都会收到66 67影响
	{0xa1,"mov",eax,ov,none},
	{0xa2,"mov",ob,al,none},
	{0xa3,"mov",ov,eax,none},

	{0xa4,"movs",xb,yb,none},
	{0xa5,"movs",xz,yz,none},
	{0xa6,"cmps",xb,yb,none},
	{0xa7,"cmps",xz,yz,none},

	{0xa8,"test",al,Ib,none},
	{0xa9,"test",eax,Iz,none},

	{0xaa,"stos",xb,none,none},
	{0xab,"stos",xz,none,none},

	{0xac,"lods",xb,none,none},
	{0xad,"lods",xz,none,none},
	{0xae,"scas",xb,none,none},
	{0xaf,"scas",xz,none,none},

	{0xc2,"ret",iw,none,none},
	{0xc3,"ret",none,none,none},

	{0xc8,"enter",iw,Ib,none},//不受66 67影响
	{0xc9,"leave",none,none,none},//不受66 67影响

	{0xca,"retf",iw,none,none},
	{0xcb,"retf",none,none,none},

	{0xcc,"int3",none,none,none},
	{0xcd,"int",Ib,none,none},
	{0xce,"into",none,none,none},
	{0xcf,"iretd",none,none,none},//受66影响 iretw

	{0xd4,"aam",Ib,none,none },
	{0xd5,"aad",Ib,none,none },
	{0xd6,"???",none,none,none },
	{0xd7,"xlatb",none,none,none },//受到67影响 固定ebx

	{0xe0,"loopnz",jb,none,none },
	{0xe1,"loopz",jb,none,none },
	{0xe2,"loop",jb,none,none },
	{0xe3,"jrcxz",jb,none,none },//受67影响

	{0xe4,"in",al,Ib,none },
	{0xe5,"in",eax,Ib,none },
	{0xe6,"out",Ib,al,none },
	{0xe7,"out",Ib,eax,none },

	{0xe8,"call",jz,none,none },
	{0xe9,"jmp",jz,none,none },
	{0xea,"jmp",ap,none,none },
	{0xeb,"jmp",jb,none,none },

	{0xec,"in",al,dx,none },
	{0xed,"in",eax,dx,none },
	{0xee,"out",dx,al,none },
	{0xef,"out",dx,eax,none },

	{0xf1,"???",none,none,none },
	{0xf4,"hlt",none,none,none },
	{0xf5,"cmc",none,none,none },
	{0xf8,"clc",none,none,none },
	{0xf9,"stc",none,none,none },
	{0xfa,"cli",none,none,none },
	{0xfb,"sti",none,none,none },
	{0xfc,"cld",none,none,none },
	{0xfd,"std",none,none,none },

	//变长
	{0x62,"bound",Gv,Ma,none },
	{0x63,"arpl",Ew,Gw,none },
	{0x69,"imul",Gv,Ev,Iz },
	{0x6b,"imul",Gv,Ev,Ib },
	{0x6b,"imul",Gv,Ev,Ib },

	{0x00,"add",Eb,Gb,none },
	{0x01,"add",Ev,Gv,none },
	{0x02,"add",Gb,Eb,none },
	{0x03,"add",Gv,Ev,none },

	{ 0x08,"or",Eb,Gb,none },
	{ 0x09,"or",Ev,Gv,none },
	{ 0x0a,"or",Gb,Eb,none },
	{ 0x0b,"or",Gv,Ev,none },

	{ 0x10,"adc",Eb,Gb,none },
	{ 0x11,"adc",Ev,Gv,none },
	{ 0x12,"adc",Gb,Eb,none },
	{ 0x13,"adc",Gv,Ev,none },

	{ 0x18,"sbb",Eb,Gb,none },
	{ 0x19,"sbb",Ev,Gv,none },
	{ 0x1a,"sbb",Gb,Eb,none },
	{ 0x1b,"sbb",Gv,Ev,none },

	{ 0x20,"and",Eb,Gb,none },
	{ 0x21,"and",Ev,Gv,none },
	{ 0x22,"and",Gb,Eb,none },
	{ 0x23,"and",Gv,Ev,none },

	{ 0x28,"sub",Eb,Gb,none },
	{ 0x29,"sub",Ev,Gv,none },
	{ 0x2a,"sub",Gb,Eb,none },
	{ 0x2b,"sub",Gv,Ev,none },

	{ 0x30,"xor",Eb,Gb,none },
	{ 0x31,"xor",Ev,Gv,none },
	{ 0x32,"xor",Gb,Eb,none },
	{ 0x33,"xor",Gv,Ev,none },

	{ 0x38,"cmp",Eb,Gb,none },
	{ 0x39,"cmp",Ev,Gv,none },
	{ 0x3a,"cmp",Gb,Eb,none },
	{ 0x3b,"cmp",Gv,Ev,none },


	{ 0x88,"mov",Eb,Gb,none },
	{ 0x89,"mov",Ev,Gv,none },
	{ 0x8a,"mov",Gb,Eb,none },
	{ 0x8b,"mov",Gv,Ev,none },

	{ 0x84,"test",Eb,Gb,none },
	{ 0x85,"test",Ev,Gv,none },
	{ 0x86,"xchg",Eb,Gb,none },
	{ 0x87,"xchg",Ev,Gv,none },

	{ 0x8c,"mov",Ev,Sw,none },
	{ 0x8d,"lea",Gv,m,none },
	{ 0xc4,"lea",Gv,mp,none },
	{ 0xc5,"lds",Gv,mp,none },


	//组编码
	{ 0x80,"Grp",Eb,Ib,none },
	{ 0x81,"Grp",Ev,Iz,none },
	{ 0x82,"Grp",Eb,Ib,none },
	{ 0x83,"Grp",Ev,Ib,none },

	{ 0x8f,"Grp",Ev,none,none },

	{ 0xc0,"Grp",Eb,Ib,none },
	{ 0xc1,"Grp",Ev,Ib,none },

	{ 0xc6,"Grp",Eb,Ib,none },
	{ 0xc7,"Grp",Ev,Iz,none },

	{ 0xd0,"Grp",Eb,num1,none },
	{ 0xd1,"Grp",Ev,num1,none },
	{ 0xd2,"Grp",Eb,cl,none },
	{ 0xd3,"Grp",Ev,cl,none }
	//还剩下4个组编码  f 写完再研究下

	//{0x8b,"mov",Gv,Ev,none}
};
std::vector<InstructionDescriptor> prefixList =
{
	{0x26,"es:",none,none,none},
	{0x2e,"cs:",none,none,none},
	{0x36,"ss:",none,none,none},
	{0x3e,"ds:",none,none,none},
	{0x64,"fs:",none,none,none},
	{0x65,"gs:",none,none,none},

	{0x66,"operandSize:",none,none,none},
	{0x67,"addressSize:",none,none,none},
	//	{0x67,"addressSize:",none,none,none},

	{0xf0,"lock",none,none,none},

	{0xf2,"repnz",none,none,none},
	{0xf3,"repe",none,none,none},
};
