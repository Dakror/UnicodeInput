// UnicodeInput.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

#define printf printf2

int __cdecl printf2(const char *format, ...)
{
  char str[1024];

  va_list argptr;
  va_start(argptr, format);
  int ret = vsnprintf(str, sizeof(str), format, argptr);
  va_end(argptr);

  OutputDebugStringA(str);

  return ret;
}

HHOOK hHook;

bool ctrl = false;
bool alt = false;

string evalChar = "";

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  auto obj = ((KBDLLHOOKSTRUCT*)lParam);
  auto keyCode = obj->vkCode;

  if (wParam == WM_KEYDOWN) {
    if (keyCode == 0xA2) ctrl = true;
    else if (keyCode == 0xA4) alt = true;
    else if(ctrl&&alt){
      if ((keyCode >= 0x60 && keyCode <= 0x69) || (keyCode >= 0x41 && keyCode <= 0x46)) // 0 - F
      {
        if (keyCode >= 0x60) evalChar += to_string(keyCode - 0x60);
        else if (keyCode >= 0x40) evalChar += (char)keyCode;
      }
     }
  }
  else if (wParam == WM_KEYUP) {
    if (keyCode == 0xA2 && evalChar.length() > 0) {
      alt = false;
      ctrl = false;
      if (evalChar.length() < 8) {
        auto val = stoi(evalChar.c_str(), 0, 16);

        PostMessage(NULL, WM_USER, val, 0);
      }
      evalChar = "";
    }
  }
  return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    /*TranslateMessage(&msg);
    DispatchMessage(&msg);*/

      int val = (int)msg.wParam;
      INPUT input1 = { 0 };
      INPUT input2 = { 0 };
      int numInput;

      if (val <= 0xFFFF)
      {
        input1.type = INPUT_KEYBOARD;
        input1.ki.wScan = val;
        input1.ki.dwFlags = KEYEVENTF_UNICODE;

        numInput = 1;
      }
      else
      {
        val -= 0x010000;

        input1.type = INPUT_KEYBOARD;
        input1.ki.wScan = (WORD)(((val >> 10) & 0x03FF) + 0xD800);
        input1.ki.dwFlags = KEYEVENTF_UNICODE;

        input2.type = INPUT_KEYBOARD;
        input2.ki.wScan = (WORD)((val & 0x03FF) + 0xDC00);
        input2.ki.dwFlags = KEYEVENTF_UNICODE;

        numInput = 2;
      }

      SendInput(1, &input1, sizeof(INPUT));
      if(numInput == 2)SendInput(1, &input2, sizeof(INPUT));
    
  }
  return msg.wParam;
}