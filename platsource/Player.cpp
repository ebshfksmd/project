#include "sPlayer.h"
#include <iostream>

namespace smite {

    using namespace std;
    using namespace chrono;

    Player::Player(const string& name)
        : Entity(name), killCount(0), lastSmiteTime(steady_clock::now() - seconds(10)) {
    }

    void Player::incrementKill() {
        killCount++;
    }

    void Player::smite(Monster& monster, int smiteDamage, int reactionTimeMs) {
        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - lastSmiteTime);
        if (elapsed.count() < 7) {
            cout << "��Ÿ ���� ��� �� (" << (7 - elapsed.count()) << "�� ����)\n";
            return;
        }
        lastSmiteTime = now;

        if (monster.getHp() <= smiteDamage) {
            monster.kill();
            incrementKill();
            cout << ">> óġ ����! ���� �ð�: " << reactionTimeMs << "ms\n";
        }
        else {
            monster.decreaseHp(smiteDamage);
            cout << ">> ����! ���� ü��: " << monster.getHp()
                << " | ���� �ð�: " << reactionTimeMs << "ms\n";
        }
    }

    void Player::info() const {
        cout << "[�÷��̾�] " << name << " | �� ų ��: " << killCount << "\n";
    }

}