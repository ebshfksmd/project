#include <iostream>
#include <windows.h>
#include <vector>

namespace smite {
    using namespace std;

    void gotoxy(int x, int y) {
        COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }


    void Heraldimg() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 13);  // 보라색

        vector<string> art = {
            "################################################################################",
            "################################################################################",
            "################################################################################",
            "#########################################*###**+=+##############################",
            "###########################*==+++#############=--=*#############################",
            "###########################*=--=%%##########+-::-+##############################",
            "#############################*+=:-*++=+++++--+##################################",
            "###########################****+++=:==-===-+=++*===*############################",
            "##########################*##++======-:-===-====++===+===+*#####################",
            "######################***++**++==---+#**#+##===---+##@@@@@%#####################",
            "####################**+=-=*+======++===--===**+=-=++=--=*#######################",
            "################**+=====*#*=---=++++=+--==*+++=:-==-=++++#######################",
            "###############%##***+%@#=--+====*=--=++=+==*-::-++==---+#######################",
            "#################*++*%@@+=====+##*+*=-====+=---=++#%+==+*#######################",
            "#################%%%%##%%%#*+*+-###+=+==+=-=====*%*+*###########################",
            "####################*%%##%%@##*+*%@%#*++++++***%%#**##**########################",
            "##################++******%##+===**%@@%%###%%%##*=*###*****+*###################",
            "#################**+-:===*#%#####*+***#%@@%###***####%#+**#==++*################",
            "#################%#*=---+%%#######+=--+**#*=-=*####%@%%##%*++*#*++*++###########",
            "###################*+----*########*+-=+++*+=-=*######+==++==++=-==--=+##########",
            "#############++###+-=----###########***===**+*#####*++++=-==-:---==+*###########",
            "##############*+----====+##########%%*=---+########%%%%#*=====++*#%#############",
            "###############*++++=---+###########*+=---+#=*##################################",
            "#################**=:---=#########+++**=-+#**==+################################",
            "#################**+-:---+#######*+=***#+#***===+###############################",
            "##################*++---+%######=:-+++==**=##*--*###############################",
            "########################%######+--=+++=--==##%*++###############################",
            "###############################=::+##+===+####*-+###############################",
            "#############################*+*###############+*###############################",
            "################################################################################",
            "################################################################################"

        };

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int startY = csbi.dwCursorPosition.Y;

        for (int i = 0; i < art.size(); ++i) {
            int padX = (consoleWidth - art[i].size()) / 2;
            gotoxy(padX, startY + i);
            cout << art[i];
        }

        SetConsoleTextAttribute(hConsole, 7); // 색 복원
    }

    void Dragonimg() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);  // 어두운 빨강

        vector<string> art = {
            "@@@@@@@@@@@@@@@@@@@@@%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@%#%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%#%@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@##%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#*%@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@%*#%@@@@#%@@@@@@@@@@@@@@@@@@@@@@@@#=#@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@%**#%@@@@*%@@@@@@@@@@@@@@@@@@@@@@%+=*@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@*=+#@@@@*+%@@@@@@@@@*#@@@@@@@@@@#==*%@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@%#%@@@@@@@@%*-=*%@%@#++%@@@@@@@==@@@@@@@@@@%*==*%@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@#*@@@@@@@@%*=-*%@+#@**%@%@@@@=-*@@@@@@@@@%*=-=*%@@@@@@@@@@@@@@%@@@@@",
            "@@@@@@@@@@%*+#@@@@@@@@@#+-+#@+=#@@%*=%@%+--@@@@@@@@#=---=+*#%@@@@@@@@@@@@@#%@@@@",
            "@@@@@@@@#++#%%@@@@@@@@@#=--*%#=+*%+-*%*=--=@@@@@%*=--==--=*#%%@@@@@@@@@@@@*%@@@@",
            "@@@@@%*=+#%@@@@@@@@@@@@#+-=+==*#**##++++=-*%%*=--=++++=--=*#%#%@@@@@@@@@@%*%@@@@",
            "@@@@%#*##%@@@@@@@@@@@@@##**+===+*###%+++**#*=-=+*#%@%+=--=*###**#%@@@@@@@**@@@@@",
            "@@@#==+*#%@@@@@%##@@%#**###*==---***@+=-----+**#%@@@%+---=+*%#*+====*##*+=#@@@@@",
            "@@@*++===++**#%%#+*##*+*+*##**=-=**#@#---=*##%@@@%%%%*---=+*%#+====-----=+%@@@@@",
            "@@@#+==++==+++==++*+=+*+--#%*%****#%@@**#%%@@@%%%#**#*---=+*%#+-====----+##@@@@@",
            "@@@@%*+*%%%%@@%%*+++=-===-*#*%@@@%%@*%##%@@@@@%@@%#**+---=+#%*======--=+*+*%@@@@",
            "@@@@@@@@@@@@@@@@@@%#**++===*%%#****#@@@@@@@@@@@@@@@%#*---=+#%*=====--=**+++*%#**",
            "@@@@@@@@@@@@@@@@%%*+*+++**+#@@%##%%%@@@@@@@@@@@@@@%%%*---=*%#+=++=--=**======+%@",
            "@@@@@@@@@@@@@@@@@@%**##*++=+%@@@%%@@@@@@@@@%%**#@@@%**---+#%*+++=--=*+======*#%@",
            "@@@@@@@@@@@@@@@@%%@@@%%#*+==#@@@@@@@@@@@@%%#**#%%@@%#*--=*%#+=+=--+*+=====++++%@",
            "@@@@@@@@@@@@@@@@@@@@@@@%%***%@@@@@@@%@@@#**#%%@%@@@%%+--+#%*===--++======+====%@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@%*#%@@@@@@#%@%%%%%%@@@@@@%##=-=*%*===-=++=====+======++",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%#%%@@@@%%@@@%*+*--+##==--+*+====++=====+%@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#%%@@@#%@@@@@@%++=-=*#====**====**+===+#@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@%++--=*+-=**+===*#+====*%@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@%#*#@@@@@%%%*=-=+*=+*+==+**=====+###%%%@@@"


        };

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int startY = csbi.dwCursorPosition.Y;

        for (int i = 0; i < art.size(); ++i) {
            int padX = (consoleWidth - art[i].size()) / 2;
            gotoxy(padX, startY + i);
            cout << art[i];
        }

        SetConsoleTextAttribute(hConsole, 7);
    }

    void nasherimg() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 13);

        vector<string> art = {

            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@+=+@@@##%@@@@%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@#==+%====*#@+==-=%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@*+=-=+%%++======+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@#==--+*+======----=#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@*====++++===--====-------=%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@+++*+++=++++++=====-----+##@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@%+*#*+*+++=+++==-----@%+++++==-#@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@#+=----=**++++===-----*****++**+@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@*++=++=+##*+*+*=++===-=*=@@@*+#@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@**++**+*##*+=+=*+++===+*=*@@@##@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@%*++=++*******+*#*+==+#%*%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@#*++********+**##**+%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@%+*+*******+*****+#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@*++******++++=++=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@%+++*****++==+=*==*%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*++*++++++=+++**%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*++++++=--=+=+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%+++++===--=-+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*++=++===---*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%+++++++=---*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@++=====----+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+===+++==--=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#%@@@@*==+====----#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@++**++=%@*+=+=====---=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@*++****+++++=++====---=#+=*%@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@+**###++++++++===++=---=*+=--#@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@%***##%*++++++++++===-=====+*%%%*@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@%+****#%+++**+*+++++++=+++=-+++*@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@+=***+==++++=-=**++++++**+=-+*@@##@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@%%*+=+*******+=--+***++***+==+@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@%++*+**%@@#***=-=+**#*+++*==@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@%+*+***%@#**%#*+-=#**=++=+-+@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@*++****#*+*+*##*=*%*+++=+=#@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@#+++****+*+*###*+#+++=-=#@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#++++++**++***=--===#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#*++++++++++#%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

        };

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int startY = csbi.dwCursorPosition.Y;

        for (int i = 0; i < art.size(); ++i) {
            int padX = (consoleWidth - art[i].size()) / 2;
            gotoxy(padX, startY + i);
            cout << art[i];
        }

        SetConsoleTextAttribute(hConsole, 7);
    }

    void Smiteimg() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 11);  // 주황
        cout << R"(
@@@@@@@@@@@@@@@@%%%%#####****=***+**++*******+--*+------====
@@@@@@@@@@@@@@@%%%%##+###***=******+++-::***+--+----------==
@@@@@@@@@@@@@%%%%%#==*##***+*++++++###%%%#-+::---:::::----==
@@@@@@@@@@@%%%%*=--=*#***++++++*%%##***#%%@::::.::::::----+*
@@@@@@@@@%%%#--:::+*#****++#####**#*=-==:-=**+=#@@@#-:--*+==
@@@@@@@@%%%=--:::********+@%####%%%%%#====-%#%%%%%%%@=--:-+*
@@@@@@@%%%+-----********+#%*=-===+*%%%@-..-=:-=+++*%@%.-****
@@@@@@%%%*-----+******+*@%#**#%#+--+*+##=...::..-=*#%@:++***
@@@@@%%%%%%*---+******=##++*#*%#%%:.-+***......:-=*#%%+=+***
@@@%#%%%%%%##*--=***+:%##%%+--+###%....:*-...-=-=*#*%@#-+**+
@@@+#%%%%%%###*===++-%**+*%%#::+*##*.......=+--+:..%@@%:*---
@@*-%%%%%%%####*++++:%#**=**%#..-**+:..................:::--
@@=-#%%%%%%%####++++:%#**+=:-==....--......:=+++++**#-::::-+
@@%-=%%%%%%%#=#**+*+*.*#*:............:-**====++**#%-.:-+*+*
@@@@-*%%%%%%#=##+*+=***:...........::*++++===++*##=.:%%=++**
@@@@%=*%%%%%=###**=**-..........::+++==++++++*###%%%%@#++***
@@@@@%+*%%%####**=++:.......:::-*+**++*+=++**###%%%%@#-+****
@@%@@@**%%#####*=--:.......::=+=--=*#****+**#%%%%%@@*:+***##
%%@@@@*%%%##+#*-:::.....:::::--=##%%#######%%%%@@@@@%:**####
%@@@#*%%%%#-%*-:::::.::::::--**.-%@%%%@@@@%%%@@+%@%%%@%:*###
%@@@%#@@%%=++-:::::::::::-+*****+::=#@@@%@%#+-#%##%%%%%@#+%%
@@@@@%@@%+-+:::::::::::-++=--*#****++-------*%%%%%#%%%%@@@@%
@@@@%%@%*-=::::::::::---=+#########**:=@@@%%%#%%%%%%%%%@%*==
@@@@@%%*-::::::::::-==################--@@%=---=*#%#+==-----
@@@@@%%=-:::::::-+#%%%%##%%%%#%%######%*=--------:---------+
@@@@@%+-:::::=+%%%%%###%#%#*********+======-----------+#%@@@
%@@@%*----=#%#****######***#%***+++++++++++++*#%@@@@@@@@@@%%
@@@%#--*%%#%@@@%%@%@@@@@%@%%%%%%%%%%%###%%%+%@@@@@@@@@@@@@@@
%@%##%%%%@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%+#@@@@@@@@@@@@@@
%%%%%%%@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%#*@@@@@@@@@@@@@

    )" << endl;
        SetConsoleTextAttribute(hConsole, 7);   // 기본색 
    }

}