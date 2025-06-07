#pragma once
#include <string>

class SplashScreen {
public:
    SplashScreen();
    void Run();
private:
    int x_, y_;
    constexpr static double BLINK_INTERVAL = 0.7;
    const std::string prompt_ = "                 Press Enter to start the game";

    void initConsole();
    void drawSplash();

    void blinkLoop();
    
};
