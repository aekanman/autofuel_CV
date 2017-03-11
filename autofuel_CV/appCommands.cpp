#define WIN32_LEAN_AND_MEAN
#include "appCommands.h"

using namespace std;

bool getTextFromWeb() {

	TCHAR url[] = TEXT("http://atakanefekanman.com/bool.txt");

	TCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);

	wsprintf(path, TEXT("%s\\bool.txt"), path);

	DeleteUrlCacheEntry(url);
	HRESULT res = URLDownloadToFile(NULL, url, path, 0, NULL);

	if (res == S_OK) {
		return txtFromFileToBool();
	}
	else {
		return 0;
	}	
}

bool txtFromFileToBool() {
	string line;
	ifstream myfile ("bool.txt");
	bool appInput = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			appInput = toBool(line);
		}
		myfile.close();
		remove("bool.txt");
	}

	else cout << "Unable to open file";

	return appInput;
}

bool toBool(std::string const& s) {
	return s != "0";
}