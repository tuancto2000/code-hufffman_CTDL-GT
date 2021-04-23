#include "CompressFile.h"


void CompressFile::MaHoa1KyTu(unsigned char c, unsigned char& out, unsigned char& viTriBit, FILE*& fo) {

	for (int i = 0; i < bangMaBit[c].soBit; i++) {
		if (bangMaBit[c].bits[i] == 1) {
			out = out | (1 << viTriBit);
		}
		if (viTriBit == 0) { // da du 1 byte, ghi byte do ra file
			viTriBit = 7;
			fwrite(&out, sizeof(out), 1, fo);
			out = 0;
		}
		else {
			viTriBit--;
		}
	}
}
void CompressFile::NenHuffman(string inputFile, FILE*& fo) {

	KhoiTao();
	ThongKeTanSoXuatHien(inputFile.c_str());
	//	XuatBangThongKe();
	int nRoot = TaoCayHuffman();
	//	XuatCayHuffman(nRoot, 0);
	PhatSinhMaBit(nRoot);
	//	XuatBangMaBit();
	unsigned char out = 0;
	unsigned char soBitCoNghia = 0;
	unsigned char c;
	unsigned char viTriBit = 7;

	unsigned int count = 0;
	unsigned char bitthem = 0;
	unsigned long long temp = 0;
	for (int i = 0; i < 256; i++) {
		if (huffTree[i].freq > 0) {
			count++;
			temp += huffTree[i].freq * bangMaBit[i].soBit;
		}
	}
	bitthem = 8 - temp % 8;
	fwrite(&bitthem, 1, 1, fo);
	fwrite(&count, sizeof(count), 1, fo);
	for (int j = 0; j < 256; j++) {
		if (huffTree[j].freq > 0) {
			fwrite(&huffTree[j].c, 1, 1, fo);
			fwrite(&huffTree[j].freq, sizeof(huffTree[j].freq), 1, fo);
		}
	}
	unsigned long long length;
	length = temp / 8; 
	if (bitthem > 0) length++;
	fwrite(&length, sizeof(length), 1, fo);
	FILE* fi = fopen(inputFile.c_str(), "rb");
	while (true) {
		fread(&c, 1, 1, fi);
		if (feof(fi)) {
			soBitCoNghia = 7 - viTriBit;
			if (soBitCoNghia == 0) {
				soBitCoNghia = 8;
			}
			else {
				fwrite(&out, 1, 1, fo);
			}
			break;
		}
		MaHoa1KyTu(c, out, viTriBit, fo);
	}
	fclose(fi);

}
void CompressFile::NenHuffman_file(string inputFile, string outputFile) {

	clock_t start = clock();

	string name = getName(inputFile) + getTail(inputFile);
	KhoiTao();
	ThongKeTanSoXuatHien(inputFile.c_str());
	//	XuatBangThongKe();
	int nRoot = TaoCayHuffman();
	//	XuatCayHuffman(nRoot, 0);
	PhatSinhMaBit(nRoot);
	//	XuatBangMaBit();
	FILE* fo = fopen((outputFile+"\\"+getName(inputFile)+".hf").c_str(), "wb");
	unsigned char out = 0;
	unsigned char soBitCoNghia = 0;
	unsigned char c;
	unsigned char viTriBit = 7;
	unsigned int count = 0;
	unsigned char bitthem = 0;
	unsigned long long temp = 0;
	for (int i = 0; i < 256; i++) {
		if (huffTree[i].freq > 0) {
			count++;
			temp += huffTree[i].freq * bangMaBit[i].soBit;
		}
	}
	c = name.length();
	fwrite(&c, 1, 1, fo);
	for (int i = 0; i < name.length(); i++)
	{
		c = name[i];
		fwrite(&c, 1, 1, fo);
	}
	bitthem = 8 - temp % 8;
	fwrite(&bitthem, 1, 1, fo);
	fwrite(&count, sizeof(count), 1, fo);
	for (int j = 0; j < 256; j++) {
		if (huffTree[j].freq > 0) {
			fwrite(&huffTree[j].c, 1, 1, fo);
			fwrite(&huffTree[j].freq, sizeof(huffTree[j].freq), 1, fo);
		}
	}
	unsigned long long length;
	length = temp / 8;
	if (bitthem > 0) length++;
	fwrite(&length, sizeof(length), 1, fo);
	FILE* fi = fopen(inputFile.c_str(), "rb");
	while (true) {
		fread(&c, 1, 1, fi);
		if (feof(fi)) {
			soBitCoNghia = 7 - viTriBit;
			if (soBitCoNghia == 0) {
				soBitCoNghia = 8;
			}
			else {
				fwrite(&out, 1, 1, fo);
			}
			break;
		}
		MaHoa1KyTu(c, out, viTriBit, fo);
	}
	fclose(fi);
	clock_t finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n  Thoi gian nen la: %.2lf", duration);
	cout << "\n  File ban dau co dung luong: " << GetFileSize(inputFile) << " byte";
	cout << "\n  File sau khi nen co dung luong: " << GetFileSize(outputFile +"\\"+ getName(inputFile) + ".hf") << " byte";
	fclose(fo);
}

