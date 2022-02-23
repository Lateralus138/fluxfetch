#ifndef LOGODATA_H
#define LOGODATA_H
#include <map>
#include <string>
#include <vector>
using namespace std;
extern map<string, vector<string>>
	windowsLogos,
	linuxLogos,
	macosLogos;
extern map<string, map<string, vector<string>>> logos;
string VectorToString(vector<string> vector_, string delim_);
#endif // LOGODATA_H
