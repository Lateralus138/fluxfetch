#include "Logos.h"

void Logos::setLogo(string main_, string sub_, string value_)
{
  logos[main_][sub_] = value_;
}
string Logos::getLogo(string main_, string sub_)
{
  return logos[main_][sub_];
}