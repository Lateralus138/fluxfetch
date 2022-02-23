#include "functions.h"
bool IsOwnWindow()
{
  HWND hwndConsole = GetConsoleWindow();
  DWORD dwProcessId;
  GetWindowThreadProcessId(hwndConsole, &dwProcessId);
  return (GetCurrentProcessId() == dwProcessId);
}
BOOL WINAPI SignalControlCHandler(DWORD ctrlEvent)
{
  switch (ctrlEvent)
  {
    case CTRL_C_EVENT: exit(127);
    default: exit(0);
  }
}
//void ReplaceAllINString(std::string& string_, const std::string& find_, const std::string& replace_)
//{
//  if (find_.empty()) return;
//  size_t start_pos = 0;
//  while ((start_pos = string_.find(find_, start_pos)) != std::string::npos)
//  {
//    string_.replace(start_pos, find_.length(), replace_);
//    start_pos += replace_.length();
//  }
//}