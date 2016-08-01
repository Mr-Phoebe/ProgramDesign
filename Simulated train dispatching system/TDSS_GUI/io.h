#ifndef IO_H
#define IO_H

#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include "structs.h"
#include "mainWindow.h"

#define MAX_INPUT_LEN (1 << 8)

extern char input[MAX_INPUT_LEN];

void loadFromConfig();
void init();
//void saveToConfig();
//void init();
void printState();
//void enableCmd();
//void disableCmd();
//DWORD WINAPI getCmd(LPVOID pParameter);

#endif // IO_H
