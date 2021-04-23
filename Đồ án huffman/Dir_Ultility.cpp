
#include"Dir_Ultility.h"
vector<string> read_directory(const string& name)
{
	vector<string> v;
	DIR* dirp = opendir(name.c_str());
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		v.push_back(dp->d_name);
	}
	closedir(dirp);
	return v;
}
vector<string> GetFiles(const string& name)
{
	vector<string> res,v;
	string temp;
	v = read_directory(name);
	for (int i = 2; i < v.size(); i++)
	{
		temp = name;
		temp += "\\";
		temp += v[i];
		DIR* flag = opendir(temp.c_str());
		if (flag == NULL)			
			res.push_back(temp);
		else
		{
			
			vector<string> v2=GetFiles(temp);
			res.insert(res.end(), v2.begin(), v2.end());
		}
	}
	return res;
}
vector<string> GetFilePath(const string& name)
{
	vector<string> path = GetFiles(name);
	size_t found = name.find_last_of("\\");
	for (int i = 0; i < path.size(); i++)
	{
		path[i].erase(0, found);
	}
	return path;
}
vector<string> Getfolders(const string& name)
{
	vector<string> res, v;
	string temp;
	v = read_directory(name);
	for (int i = 2; i < v.size(); i++)
	{
		temp = name;
		temp += "\\";
		temp += v[i];
		DIR* flag = opendir(temp.c_str());
		if (flag != NULL)
		{
			
			res.push_back(temp);
			vector<string> v2 = Getfolders(temp);
			res.insert(res.end(), v2.begin(), v2.end());
		}
	}
	return res;
}

vector<string> GetFolderPath(const string& name)
{
	vector<string> v;
	v.push_back(name);
	vector<string> v2 = Getfolders(name);
	v.insert(v.end(),v2.begin(),v2.end());
	size_t found = name.find_last_of("\\");
	for (int i = 0; i < v.size(); i++)
	{
		v[i].erase(0, found);
	}
	return v;
}

void CreateDir(const string& dir,vector<string> foldertree)
{
	string temp="";
	for (int i = 0; i < foldertree.size(); i++)
	{
		temp = dir;
		temp += foldertree[i];
		mkdir(temp.c_str());
	}
}
long GetFileSize(std::string filename)
{
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}
long long GetFolderSize(string foldername)
{
	long long size = 0;
	vector<string> res = GetFiles(foldername);
	for (int i = 0; i < res.size(); i++)
	{
		size += GetFileSize(res[i]);
	}
	return size;
}