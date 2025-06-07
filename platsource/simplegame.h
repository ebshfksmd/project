#pragma once
#ifndef SIMPLEGAME_H
#define SIMPLEGAME_H

#include "GameBase.h"

using namespace std;

class SimpleGame : public GameBase {
public:

	void Init() override {
		cout << "SimpleGame Init" << endl;
		Play();
	}

	void Play() override {
		int a;
		cout << "SimpleGame Play" << endl;
		cin >> a;
	}

	void End() override {
		cout << "SimpleGame End" << endl;
	}
};

#endif