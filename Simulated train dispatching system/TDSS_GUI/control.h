#ifndef CONTROL_H
#define CONTROL_H

#include <cstdio>
#include <algorithm>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>

#include "structs.h"
//#include "io.h"
#include "manualCtrlDialog.h"

//calculate the position of trains[i] in next sec
inline double nextPos(int i);

//determine if pos is (publicTracks[i][j].inPoint, publicTracks[i][j].outPoint]
inline bool in(double pos, int i, int j);

//check whether there's conflict between trains[i]
//and trains[j] in the next sec

#define INTEND_DIS 5
#define SAFE_DIS 5

void getIntend();

void dispatch();

void stateTrans();

void control();

#endif // CONTROL_H
