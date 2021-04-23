#include "DecompressFolder.h"
void DecompressFolder::GiaiNenFolder(string input, string output)
{
	clock_t start = clock();
	FILE* fi = fopen(input.c_str(), "rb");
	int pathsize = 0;
	fread(&pathsize, sizeof(pathsize), 1, fi);
	vector<string> filepath, folderpath;
	string temp = "";
	for (int i = 0; i < pathsize; i++)
	{
		unsigned char c;
		fread(&c, sizeof(c), 1, fi);
		if (c == '?')
		{
			folderpath.push_back(temp);
			temp = "";
		}
		else temp.push_back(c);
	}
	CreateDir(output, folderpath);
	int NOFile = 0;
	fread(&NOFile, sizeof(NOFile), 1, fi);
	for (int i = 0; i < NOFile; i++)
	{
		int size;
		fread(&size, sizeof(size), 1, fi);
		string decompress_dir = output;
		for (int j = 0; j < size; j++)
		{
			unsigned char c;
			fread(&c, sizeof(c), 1, fi);
			decompress_dir += c;
		}
		GiaiNen(fi, decompress_dir);
	}
	fclose(fi);
	clock_t finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	string name = "\\" + getName(input);
	printf("\n  Thoi gian giai nen la: %.2lf", duration);
	cout << "\n  File ban dau co dung luong: " << GetFileSize(input) << " byte";
	cout << "\n  Folder sau khi giai nen co dung luong: " << GetFolderSize(output + name) << " byte";
}
