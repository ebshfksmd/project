#include "smitegame.h"
#include <windows.h>
#include <iostream>
#include "Sm.h"
#include "GameBase.h"

namespace smite {
    using namespace std;

    class smite : public GameBase {
        Game game;
        void Init() {};
        void Play() {
            game.start();
        }
        void End() {};
    };
}