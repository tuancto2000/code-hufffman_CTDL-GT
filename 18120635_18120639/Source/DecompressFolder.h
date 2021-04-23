#pragma once
#include"DecompressFile.h"
#include"Dir_Ultility.h"
class DecompressFolder: public DecompressFile
{
public:
	void GiaiNenFolder(string input, string output);
};
