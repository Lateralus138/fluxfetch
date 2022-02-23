//////////////////////////////////////////////////
// 'Flux Fetch' - 'Fetch' and display           //
// operating system information in a console /  //
// command line.                                //
// © 2022 Ian Pride - New Pride Software /      //
// Services                                     //
//////////////////////////////////////////////////
#include <iostream>
#include "Functions.h"
//#include "Logos.h"
#include "LogoData.h"

#include <iostream>
#include <Windows.h>
#include <signal.h>
#include <vector>
#include <regex>
#include <VersionHelpers.h>

#include <chrono>
#include <thread>

using namespace std;

string GetWindowsVersionF()
{
  string version;
  if (IsWindowsXPOrGreater() || IsWindowsServer())
  {
    if (IsWindowsServer()) version = "Server";
    else
    {
      if (IsWindows10OrGreater()) version = "10";
      else if (IsWindows8Point1OrGreater()) version = "8.1";
      else if (IsWindows8OrGreater()) version = "8";
      else if (IsWindows7SP1OrGreater()) version = "7 SP1";
      else if (IsWindows7OrGreater()) version = "7";
      else if (IsWindowsVistaSP2OrGreater()) version = "Vista SP2";
      else if (IsWindowsVistaSP1OrGreater()) version = "Vista SP1";
      else if (IsWindowsVistaOrGreater()) version = "Vista";
      else if (IsWindowsXPSP3OrGreater()) version = "XP SP3";
      else if (IsWindowsXPSP2OrGreater()) version = "XP SP2";
      else if (IsWindowsXPSP1OrGreater()) version = "XP SP1";
      else version = "XP";
    }
  }
  else
  {
    version = "OLDER";
  }
  return version;
}

int main(int argc, char* argv[])
{
  SetConsoleCtrlHandler(SignalControlCHandler, true);
  DWORD
    dwProcessIdMain,
    dwProcessIdThis = GetCurrentProcessId();
  HWND conHwnd = GetConsoleWindow();
  GetWindowThreadProcessId(conHwnd, &dwProcessIdMain);
  const bool isOwnConWin = (dwProcessIdThis == dwProcessIdMain);
  const string
    TITLE = "Flux Fetch",
    TITLEESC = "\x1b]0;" + TITLE + "\007";
  bool
    isOwnWindow = IsOwnWindow();
  auto wait_continue =
    [isOwnWindow]()
  {
    if (isOwnWindow)
    {
      cout << "Press [Enter] to continue... ";
      cin.get();
      cout << '\n';
    }
  };
  const regex
    RGX_HELP("^/([hH]|[hH][eE][lL][pP]|\\?)$");
  const vector <string> BOX =
  {
    u8"\u250C", u8"\u2500", u8"\u2510", u8"\u2502",
    u8"\u2514", u8"\u2518", u8"\u251C", u8"\u2524"
  };
  const string CR = u8"\u00A9";
  string box_line;
  for (auto i = 0; i < 48; ++i)
  {
    box_line += BOX[1];
  }
  vector<string> infoOperatingSystem
  {
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", ""
  };

  string userName;
  {
    char name[MAX_PATH];
    DWORD size = MAX_PATH;
    auto ret = GetUserNameA(name, &size);
    if (ret == 0)
    {
      cerr << "Could not retrieve User Name.\n";
      wait_continue();
      return 1;
    }
    userName = name;
  }

  string computerName;
  {
    char name[MAX_PATH];
    DWORD size = MAX_PATH;
    auto ret = GetComputerNameA(name, &size);
    if (ret == 0)
    {
      cerr << "Could not retrieve Computer Name.\n";
      wait_continue();
      return 2;
    }
    computerName = name;
  }

  {
    const string pre = "\x1b[38;2;0;173;239m" + BOX[3];
    string splitter;
    for (auto i = 0; i < 57; i++)
    {
      splitter += BOX[1];
    }
    infoOperatingSystem[0] =
      pre +
      "  \x1b[38;2;227;200;0m" + userName +
      "\x1b[38;2;0;173;239m@\x1b[38;2;227;200;0m" +
      computerName + "\x1b[m";
    infoOperatingSystem[1] = pre + "  \x1b[38;2;0;173;239m" + splitter + "\x1b[m";
    infoOperatingSystem[2] = pre + "  \x1b[m";
    infoOperatingSystem[3] = pre + "  \x1b[m";
    infoOperatingSystem[4] = pre + "  \x1b[m";
    infoOperatingSystem[5] = pre + "  \x1b[m";
    infoOperatingSystem[6] = pre + "  \x1b[m";
    infoOperatingSystem[7] = pre + "  \x1b[m";
    infoOperatingSystem[8] = pre + "  \x1b[m";
    infoOperatingSystem[9] = pre + "  \x1b[m";
    infoOperatingSystem[10] = pre + "  \x1b[m";
    infoOperatingSystem[11] = pre + "  \x1b[m";
    infoOperatingSystem[12] = pre + "  \x1b[m";
    infoOperatingSystem[13] = pre + "  \x1b[m";
    infoOperatingSystem[14] = pre + "  \x1b[m";
    infoOperatingSystem[15] = pre + "  \x1b[m";
    infoOperatingSystem[16] = pre + "  \x1b[m";
    infoOperatingSystem[17] = pre + "  \x1b[38;2;0;173;239m" + splitter + "\x1b[m";;
    infoOperatingSystem[18] = pre + "  \x1b[40m    \x1b[41m    \x1b[42m    \x1b[43m    \x1b[44m    \x1b[45m    \x1b[46m    \x1b[47m    \x1b[m";
    infoOperatingSystem[19] = pre + "  \x1b[100m    \x1b[101m    \x1b[102m    \x1b[103m    \x1b[104m    \x1b[105m    \x1b[106m    \x1b[107m    \x1b[m";
  }

  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  SetConsoleTitleA(TITLE.c_str());
  if (isOwnConWin)
  {
    SetWindowTextA(conHwnd, TITLE.c_str());
  }
  if (argc > 1)
  {
    bool skip = false;
    for (auto index = 1; index < argc; index++)
    {
      if (skip)
      {
        skip = false;
        continue;
      }
      string thisArg = argv[index];
      if (regex_match(thisArg, RGX_HELP)) // TODO Finish Help, add stuff.
      {
        string help_message;
        help_message.append
        (
          '\n' +
          BOX[0] + box_line + BOX[2] + '\n' +
          BOX[3] + "                   Flux Fetch                   " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + "Fetch and display operating system information. " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + "  fluxfetch [/H]                                " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + "  /h,/HELP,/?     This help screen.             " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + "" + CR + " 2022 Ian Pride - New Pride Software/Services  " + BOX[3] + '\n' +
          BOX[4] + box_line + BOX[5] + "\n\n"
        );
        cout << help_message;
        wait_continue();
        return 0;
      }
    }
  }
  argc--;

  for (auto i = 0; i < (int)logos["windows"]["11"].size(); i++)
  {
    logos["windows"]["11"][i] = logos["windows"]["11"][i] + infoOperatingSystem[i];
  }

  cout << VectorToString(logos["windows"]["11"], "\n");

  cout << "\n\n" << GetWindowsVersionF() << '\n';

  if (IsWindows10OrGreater()) cout << "This is 10\n";

  wait_continue();
}