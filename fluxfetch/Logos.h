#ifndef LOGOS_H
#define LOGOS_H
#include <map>
#include <string>
using namespace std;
class Logos
{
private:
  map<string, map<string, string>> logos;
public:
  void setLogo(string main_, string sub_, string value_);
  string getLogo(string main_, string sub_);
};
#endif // LOGOS_H
