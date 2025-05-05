#pragma once
#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <iostream>

using namespace std;

class GameBase {
public:
	virtual void Init() = 0;
	virtual void Play() = 0;
	virtual void End() = 0;
};

#endif