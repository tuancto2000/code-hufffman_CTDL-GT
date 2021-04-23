#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include <stdio.h>
#include<iostream>
#include<fstream>
#include<bitset>
#include<string>
#include<time.h>
#include"Dir_Ultility.h"
#include<time.h>
#include<conio.h>
using namespace std;

struct NODE {
	unsigned char	c;		// ky tu
	unsigned long long	freq;	// so lan xuat hien
	bool	used;	// danh dau node da xu ly chua 
	int		nLeft;	// chi so nut con nam ben trai
	int		nRight;	// chi so nut con nam ben phai
};

struct MABIT {
	char* bits;
	int		soBit;
};

const int MAX_NODE = 256 * 9;
const int MAX_BIT_LEN = 10000;

class Huffman
{
protected:
	NODE	huffTree[MAX_NODE];
	MABIT	bangMaBit[256];
public:
	void KhoiTao();
	void ThongKeTanSoXuatHien(string tenFile);
	bool Tim2PhanTuMin(int& i, int& j, int nNode);
	int TaoCayHuffman();
	void DuyetCayHuffman(int node, char maBit[], int nMaBit);
	void PhatSinhMaBit(int nRoot);
	//virtual void MaHoa1KyTu(unsigned char c, unsigned char& out, unsigned char& viTriBit, FILE*& fo) = 0;
	//virtual void NenHuffman(string inputFile, FILE*& fo) = 0;
	//virtual void decode(int& node, char c, int root, FILE*& fo) = 0;
	//virtual void GiaiNen(FILE* fi, string outputFile) = 0;
};
string getName(string in);
string getTail(string in);
#endif
