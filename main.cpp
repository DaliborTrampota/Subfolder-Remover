#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <string>
#include <iomanip>

namespace fs = std::experimental::filesystem;
using namespace std;


void main() {

	bool containDirectory = false;
	char opt;

	cout << "Subfolder Remover v2.1!\nAre you sure you want to proceed to remove all subfolders in current directory? <Y/N> --> ";
	cin >> opt;
	if(opt == 'Y' || opt == 'y') {


		fs::path path = fs::current_path();
		string defaultPath = path.u8string();
		//string defaultPath = "C:\\Users\\Dalibor Trampota\\GitHub\\C++\\Subfolder Remover\\Subfolder Remover\\test";
		string shortPath = defaultPath.substr(/*defaultPath.find_last_of("\\",*/ defaultPath.find_last_of("\\")/*-1)*/, defaultPath.size());
		string curPath = defaultPath;

		for(const auto & entry : fs::recursive_directory_iterator(curPath)) {//Moves all the files found into the default Directory
			if(fs::is_regular_file(entry)) {
				string fileName = entry.path().filename().u8string();
				fs::rename(entry.path(), defaultPath + "\\" + fileName);
				cout << fileName << " moved to" << setw(60 - fileName.size() - 9) << shortPath << endl;
			}
		}
		do {//removes all empty folders afterward
			for(const auto & entry : fs::recursive_directory_iterator(curPath)) {
				if(fs::is_directory(entry)) {
					containDirectory = true;
					if(fs::is_empty(entry)) {
						string fileName = entry.path().filename().u8string();
						fs::remove(entry);
						cout << fileName << setw(60 - fileName.size()) << "was removed" << endl;
					}
				}
			}
		} while(containDirectory);
		cout << "\nEnd";
	} else {
		cout << "Exiting";
		Sleep(1000);
		exit(0);
	}
}
