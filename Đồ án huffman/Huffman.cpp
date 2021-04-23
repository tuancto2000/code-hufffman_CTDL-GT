#include "Huffman.h"
void Huffman::KhoiTao()
{
	for (int i = 0; i < MAX_NODE; i++) {
		huffTree[i].c = i;
		huffTree[i].freq = 0;
		huffTree[i].used = false;
		huffTree[i].nLeft = -1;
		huffTree[i].nRight = -1;
	}
}

bool Huffman::Tim2PhanTuMin(int& i, int& j, int nNode) {
	i = -1;
	j = -1;

	// tim 2 phan tu co trong so nho nhat
	for (int k = 0; k < nNode; k++)
		if (huffTree[k].used == false && huffTree[k].freq > 0) {
			if (i == -1) {
				i = k;
			}
			else if (j == -1) {
				j = k;
			}
			else {
				if (huffTree[i].freq > huffTree[j].freq) {
					if (huffTree[k].freq < huffTree[i].freq) {
						i = k;
					}
				}
				else {
					if (huffTree[k].freq < huffTree[j].freq) {
						j = k;
					}
				}
			}
		}
	// sap xep lai 2 phan tu de co i: phan tu co trong so nho nhat, j: phan tu co trong so nho nhi	
	// co 2 truong hop can doi i,j:
			// huffTree[i].freq > huffTree[j].freq
			// huffTree[i].freq == huffTree[j].freq va (huffTree[i].c > huffTree[j].c)
	if (i != -1 && j != -1) {
		if ((huffTree[i].freq > huffTree[j].freq) || ((huffTree[i].freq > huffTree[j].freq) && (huffTree[i].c > huffTree[j].c))) {
			int t = i;
			i = j;
			j = t;
		}
		return true;
	}
	else {
		return false;
	}
}
void Huffman::ThongKeTanSoXuatHien(string tenFile)
{
	FILE* fi = fopen(tenFile.c_str(), "rb");
	unsigned char c;

	while (1) {
		fread(&c, 1, 1, fi);
		if (feof(fi)) {
			break;
		}
		huffTree[c].freq++;
	}
	fclose(fi);
}
int Huffman::TaoCayHuffman() {
	int nNode = 256;
	int i, j;
	bool timThay = false;
	while (true) {

		timThay = Tim2PhanTuMin(i, j, nNode);
		if (!timThay) {
			break;
		}

		huffTree[nNode].c = (huffTree[i].c < huffTree[j].c) ? huffTree[i].c : huffTree[j].c;
		huffTree[nNode].freq = huffTree[i].freq + huffTree[j].freq;
		huffTree[nNode].nLeft = i;
		huffTree[nNode].nRight = j;

		huffTree[i].used = true;
		huffTree[j].used = true;

		huffTree[nNode].used = false;
		nNode++;

	}
	return nNode - 1;
}
void Huffman::DuyetCayHuffman(int node, char maBit[], int nMaBit) {
	if (node == -1) {
		return;
	}
	if (huffTree[node].nLeft == -1 && huffTree[node].nRight == -1) {
		bangMaBit[node].soBit = nMaBit;
		bangMaBit[node].bits = new char[nMaBit];
		for (int i = 0; i < nMaBit; i++) {
			bangMaBit[node].bits[i] = maBit[i];
		}
		return;
	}
	else {
		maBit[nMaBit] = 0;
		DuyetCayHuffman(huffTree[node].nLeft, maBit, nMaBit + 1);

		maBit[nMaBit] = 1;
		DuyetCayHuffman(huffTree[node].nRight, maBit, nMaBit + 1);
	}
}
void Huffman::PhatSinhMaBit(int nRoot) {
	for (int i = 0; i < 256; i++) {
		bangMaBit[i].soBit = 0;
		bangMaBit[i].bits = NULL;
	};
	char maBit[MAX_BIT_LEN / 8];
	int nMaBit = 0;

	DuyetCayHuffman(nRoot, maBit, nMaBit);
}
string getName(string in)
{
	int index1, index2=in.length();
	for (int i = in.length(); i >= 0; i--)
	{
		if (in[i] == '.') {
			index2 = i;
			break;
		}
	}
	for (int i = index2; i >= 0; i--)
	{
		if (in[i] == '\\')
		{
			index1 = i;
			break;
		}
	}
	string name = in.substr(index1 + 1, index2 - index1 - 1);
	return name;
}
string getTail(string in)
{
	int index;
	for (int i = in.length(); i >= 0; i--)
	{
		if (in[i] == '.') {
			index = i;
			break;
		}
	}
	string tail = in.substr(index, in.length() - index);
	return tail;
}


