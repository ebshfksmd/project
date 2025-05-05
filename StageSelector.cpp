// StageSelector.cpp
#include "StageSelector.h"
#include "SetCursor.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

StageSelector::StageSelector(int totalStages)
    : currentStage_(0)
    , totalStages_(totalStages)
    , exitFlag_(false)
{
    system("cls");
}

void StageSelector::ProcessInput() {
    if (!_kbhit()) return;
    char key = _getch();
    switch (key) {
    case 'a': case 'A':
        if (currentStage_ > 0) --currentStage_;
        break;
    case 'd': case 'D':
        if (currentStage_ < totalStages_ - 1) ++currentStage_;
        break;
    case '\r':
        exitFlag_ = true;
        break;
    default:
        break;
    }
}

void StageSelector::DrawMenu() {
    SetCursorxy(0, 0);
    cout << "     Select a stage" << "\n\n\n";
    for (int i = 0; i < totalStages_; ++i) {
        if (i == currentStage_)
            cout << "      > Stage " << i + 1 << " <" << "\n";
        else
            cout << "        Stage " << i + 1 << "  " << "\n";
    }
}

void StageSelector::Run() {
    while (_kbhit()) _getch();
    while (!exitFlag_) {
        DrawMenu();
        ProcessInput();
    }

}
