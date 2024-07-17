#include "pch.h"
#include "VLE.h"


int VLE::findOpcode(const CString& str)//传入整个str
{
	CString strOpcode = str.Mid(0, 5);
	int count;
	count = sizeof(bianchang) / sizeof(bianChangType);
	for (int i = 0; i < count; i++)
	{
		if (bianchang[i].opcode == strOpcode)
		{
			return i;
		}
	}
		
	return -1;
}