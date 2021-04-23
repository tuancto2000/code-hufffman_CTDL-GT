
#include"DecompressFile.h"
#include"CompressFile.h"
#include"CompressFolder.h"
#include"DecompressFolder.h"
#include"Dir_Ultility.h"

void menu()
{
	cout << char(201); for (int i = 0; i < 52; i++) cout << char(205); cout << char(187) << endl;
	cout << char(186) << "  DO AN CTDL-GT: NEN VA GIAI NEN DU LIEU            " << char(186) << endl;
	cout << char(186) << "  Class        : 18CTT5C                            " << char(186) << endl;
	cout << char(186) << "  Made by      : Nguyen Xuan Tuan && Cao Huy Tung   " << char(186) << endl;
	cout << char(186) << "  Student ID   : 18120635 && 18120639               " << char(186) << endl;
	cout << char(186) << "  Mentor       : Nguyen Thanh An                    " << char(186) << endl;
	cout << char(200); for (int i = 0; i < 52; i++) cout << char(205); cout << char(188) << endl;
}

int main()
{
	menu();
	int n = 0;
	cout << "  1. Compress File" << endl;
	cout << "  2. Decompress File" << endl;
	cout << "  3. Compress Folder" << endl;
	cout << "  4. Decompress Folder" << endl;
	cout << "  5. Exit\n";
	do {
		if (n == 5) break;
		cout << "  Enter your selection: ";
		cin >> n;
	} while (n < 1 || n > 4);
	switch (n)
	{
	case 1:
	{
		string in,out;
		cin.ignore();
		cout << "  Enter the input file path: ";
		getline(cin, in);// D:\\test\\giainen.txt
		cout << "  Enter the folder path containing the compressed file: ";
		getline(cin, out);  // D:
		CompressFile file;
		file.NenHuffman_file(in, out);
		
		break;

	}
	case 2: {
	
		string in, out;
		cin.ignore();
		cout << "  Enter the input file path: ";
		getline(cin, in);
		cout << "  Enter the folder path containing the decompressed file: ";
		getline(cin, out);
		DecompressFile file;
		
		file.GiaiNen_file(in, out);
		

		break;
	};
	case 3:
	{
		string in, out;
		cin.ignore();
		cout << "  Enter the input folder path: ";
		getline(cin, in);
		cout << "  Enter the folder path containing the compressed folder: ";
		getline(cin, out);
		CompressFolder folder;
		folder.NenFolder(in, out);
		break;
	}
	case 4:
	{
		string in, out;
		cin.ignore();
		cout << "  Enter the input file path: ";
		getline(cin, in);
		cout << "  Enter the folder path containing the decompressed folder: ";
		getline(cin, out);
		DecompressFolder folder;
		folder.GiaiNenFolder(in, out);
		break;
	}
	default:
		break;
	}
	cout << endl;
	system("pause");
	return 0;
}