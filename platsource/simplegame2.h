#pragma once
#ifndef SIMPLEGAME2_H
#define SIMPLEGAME2_H

#include "GameBase.h"

using namespace std;

class SimpleGame2 : public GameBase {
public:

	void Init() override {
		cout << "SimpleGame2 Init" << endl;
		Play();
	}

	void Play() override {
		int b;
		cout << "SimpleGame2 Play" << endl;
		cin >> b;
	}

	void End() override {
		cout << "SimpleGame2 End" << endl;
	}
};

#endif