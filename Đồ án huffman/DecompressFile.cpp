#include "DecompressFile.h"
void DecompressFile::decode(int& node, char c, int root, FILE*& fo)
{

	if (c == '1')
		node = huffTree[node].nRight;
	else
		node = huffTree[node].nLeft;
	if (huffTree[node].nLeft == -1 && huffTree[node].nRight == -1)
	{
		fwrite(&huffTree[node].c, 1, 1, fo);
		node = root;
		return;
	}
	return;
}
void DecompressFile::GiaiNen(FILE* fi, string outputFile)
{

	KhoiTao();

	//FILE* fi=fopen(inputFIle.c_str(), "rb");
	unsigned char bitthem;
	unsigned int soKitu;
	fread(&bitthem, 1, 1, fi);
	fread(&soKitu, sizeof(soKitu), 1, fi);
	unsigned char c;
	unsigned long long fre;
	for (int i = 0; i < soKitu; i++)
	{
		fread(&c, 1, 1, fi);
		fread(&fre, sizeof(fre), 1, fi);
		huffTree[c].freq = fre;
	}
	int nRoot = TaoCayHuffman();

	PhatSinhMaBit(nRoot);
	//XuatBangMaBit();
	unsigned long long length;
	fread(&length, sizeof(length), 1, fi);
	string s = "";
	string out = "";
	unsigned char ch;
	int node = nRoot;
	FILE* fo = fopen(outputFile.c_str(), "wb");
	for (int i = 0; i < length; i++)
	{
		fread(&ch, 1, 1, fi);
		bitset<8> bit(ch);
		s = bit.to_string();
		if (i == length - 1)
			for (int z = 0; z < bitthem; z++)
				s.pop_back();
		for (int j = 0; j < s.size(); j++)
		{
			decode(node, s[j], nRoot, fo);
		}
	}
	fclose(fo);
}
void DecompressFile::GiaiNen_file(string inputFile, string outputFile)
{
	clock_t start = clock();
	KhoiTao();

	FILE* fi=fopen(inputFile.c_str(), "rb");
	unsigned char bitthem;
	unsigned int soKitu;
	unsigned char c;
	fread(&c, 1, 1, fi);
	string name = "";
	for (int i = 0; i < c; i++)
	{
		unsigned char ch;
		fread(&ch, 1, 1, fi);
		name += ch;
	}
	fread(&bitthem, 1, 1, fi);
	fread(&soKitu, sizeof(soKitu), 1, fi);
	unsigned long long fre;
	for (int i = 0; i < soKitu; i++)
	{
		fread(&c, 1, 1, fi);
		fread(&fre, sizeof(fre), 1, fi);
		huffTree[c].freq = fre;
	}
	int nRoot = TaoCayHuffman();

	PhatSinhMaBit(nRoot);
	//XuatBangMaBit();
	unsigned long long length;
	fread(&length, sizeof(length), 1, fi);
	string s = "";
	string out = "";
	unsigned char ch;
	int node = nRoot;
	FILE* fo = fopen((outputFile+"\\"+name).c_str(), "wb");
	for (int i = 0; i < length; i++)
	{
		fread(&ch, 1, 1, fi);
		bitset<8> bit(ch);
		s = bit.to_string();
		if (i == length - 1)
			for (int z = 0; z < bitthem; z++)
				s.pop_back();
		for (int j = 0; j < s.size(); j++)
		{
			decode(node, s[j], nRoot, fo);
		}
	}
	fclose(fo);

	clock_t finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n  Thoi gian giai nen la: %.2lf", duration);
	cout << "\n  File ban dau co dung luong: " << GetFileSize(inputFile) << " byte";
	cout << "\n  File sau khi giai nen co dung luong: " << GetFileSize(outputFile + "\\" + name) << " byte";
}
