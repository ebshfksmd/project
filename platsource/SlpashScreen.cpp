#include "SplashScreen.h"
#include "SetCursor.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

SplashScreen::SplashScreen() {
	initConsole();
}

void SplashScreen::initConsole() {
	CursorUnvisible();
	UnuseQuickEdit();
	system("cls");
}

void SplashScreen::Run() {
	drawSplash();
	blinkLoop();
}

void SplashScreen::drawSplash() {
    system("cls");
    std::cout << " _   _                                            _ " << std::endl;
    std::cout << "| | | |                                          | |" << std::endl;
    std::cout << "| | | | _ __   _ __    __ _  _ __ ___    ___   __| |" << std::endl;
    std::cout << "| | | || '_ \\ | '_ \\  / _` || '_ ` _ \\  / _ \\ / _` |" << std::endl;
    std::cout << "| |_| || | | || | | || (_| || | | | | | | __/| (_| |" << std::endl;
    std::cout << " \\___/ |_| |_||_| |_| \\__,_||_| |_| |_| \\___| \\__,_|" << std::endl;
    std::cout << "		                          _              _   " << std::endl;
    std::cout << "		                         (_)            | |  " << std::endl;
    std::cout << "		    _ __   _ __   ___     _   ___   ___ | |_ " << std::endl;
    std::cout << "		   | '_ \\ | '__| / _ \\   | | / _ \\ / __|| __|" << std::endl;
    std::cout << "		   | |_) || |   | (_) |  | ||  __/| (__ | |_ " << std::endl;
    std::cout << "		   | .__/ |_|    \\___/   | | \\___| \\___| \\__|" << std::endl;
    std::cout << "		   | |                   / |                " << std::endl;
    std::cout << "		   |_|                  |__/                " << std::endl;
}

void SplashScreen::blinkLoop() {
    x_ = getcursorx();
    y_ = getcursory() + 2;
    using clock = std::chrono::steady_clock;
    auto last = clock::now();
    bool visible = true;
    while (true) {
        auto now = clock::now();
        if (std::chrono::duration<double>(now - last).count() >= BLINK_INTERVAL) {
            last = now;
            SetCursorxy(x_, y_);
            if (visible) {
                std::cout << std::string(prompt_.size(), ' ');
            }
            else {
                std::cout << prompt_;
            }
            visible = !visible;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}