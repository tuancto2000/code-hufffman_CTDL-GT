#pragma once
#ifndef __DIR_H__
#define __DIR_H__
#include<vector>
#include"dirent.h"
#include<string>
#include<direct.h>
using namespace std;
vector<string> read_directory(const string& name);

vector<string> GetFiles(const string& name);
vector<string> GetFilePath(const string& name);

vector<string> Getfolders(const string& name);
vector<string> GetFolderPath(const string& name);

void CreateDir(const string& dir,vector<string> foldertree);
long GetFileSize(string filename);
long long GetFolderSize(string foldername);
#endif