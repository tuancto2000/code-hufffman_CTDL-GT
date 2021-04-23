#pragma once
#include"Huffman.h"
class DecompressFile:public Huffman
{
public:
	void decode(int& node, char c, int root, FILE*& fo);
	void GiaiNen(FILE* fi, string outputFile);
	void GiaiNen_file(string inputFile, string outputFile);

};