#include "CompressFolder.h"
void CompressFolder::NenFolder(string inputfolder,string output)
{
	clock_t start = clock();
	
	vector<string> filepath, folderpath,inputpath;
	filepath = GetFilePath(inputfolder);
	folderpath = GetFolderPath(inputfolder);
	string name = "\\" + getName(inputfolder)+".hf";
	FILE* fo = fopen((output+name).c_str(), "wb");
	int pathsize = 0;
	string pathkey="";
	for (int i = 0; i < folderpath.size(); i++)
	{
		pathkey += folderpath[i];
		pathkey += '?';
	}
	pathsize = pathkey.size();
	fwrite(&pathsize, sizeof(pathsize), 1, fo);
	for (int i = 0; i < pathkey.size(); i++)
		fwrite(&pathkey[i], sizeof(pathkey[i]), 1, fo);

	int NOFile = filepath.size();
	fwrite(&NOFile, sizeof(NOFile), 1, fo);
	inputpath = GetFiles(inputfolder);
	for (int i = 0; i < NOFile; i++)
	{
		int size = filepath[i].size();
		fwrite(&size, sizeof(size), 1, fo);
		for (int j = 0; j < filepath[i].size(); j++)
			fwrite(&filepath[i][j], sizeof(filepath[i][j]), 1, fo);
		NenHuffman(inputpath[i], fo);
	}
	fclose(fo);
	clock_t finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n  Thoi gian giai nen la: %.2lf", duration);
	cout << "\n  Folder ban dau co dung luong: " << GetFolderSize(inputfolder) << " byte";
	cout << "\n  Folder sau khi nen co dung luong: " << GetFileSize(output + name) << " byte";
	cout << endl << output  + name;
	
}