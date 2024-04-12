#pragma once
#include <iostream>
#ifdef _WIN32
#include <windows.h>

static bool isDarkMode() {
    DWORD useLightTheme;
    DWORD dataSize = sizeof(useLightTheme);
    if (ERROR_SUCCESS == RegGetValueA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", "AppsUseLightTheme", RRF_RT_DWORD, nullptr, &useLightTheme, &dataSize)) {
      return useLightTheme==0;
    }
    else {
      printf("Could not determin if dark mode is set in windows settings, assuming light mode.\n");
      return 0;
    }
}
#else
// if not windows, assume light mode
static bool isDarkMode() {
    return 0;
}
#endif