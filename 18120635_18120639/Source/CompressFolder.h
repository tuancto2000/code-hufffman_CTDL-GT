#pragma once
#include"CompressFile.h"
#include"Dir_Ultility.h"
class CompressFolder:public CompressFile
{
public:
	void NenFolder(string inputfolder, string output);
};