#pragma once
#include"Huffman.h"
class CompressFile:public Huffman
{
public:
	void MaHoa1KyTu(unsigned char c, unsigned char& out, unsigned char& viTriBit, FILE*& fo);
	void NenHuffman(string inputFile, FILE*& fo);
	void NenHuffman_file(string inputFile, string outputFile);
};
