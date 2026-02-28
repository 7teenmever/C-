#include <iostream>
#include <string>
using namespace std;

class GameCharacter {
private:
    string name;
    int health;
    int attackPower;
    int level;
    int experience;

public:
    GameCharacter(const string& characterName, int initialHealth = 100, int initialAttack = 20)
        : name(characterName), health(initialHealth), attackPower(initialAttack), level(1), experience(0) {}

    void takeDamage(int damage) {
        if (damage <= 0) {
            return;
        }
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    void attack(GameCharacter& target) {
        if (!isAlive()) {
            cout << name << " cannot attack because they are defeated." << endl;
            return;
        }

        cout << name << " attacks " << target.name << " for " << attackPower << " damage." << endl;
        target.takeDamage(attackPower);
        gainExperience(30);
    }

    void gainExperience(int exp) {
        if (exp <= 0) {
            return;
        }
        experience += exp;
        while (experience >= 100) {
            experience -= 100;
            levelUp();
        }
    }

    void levelUp() {
        ++level;
        health += 20;
        attackPower += 5;
        cout << name << " leveled up to level " << level << "!" << endl;
    }

    void displayStatus() const {
        cout << "Name: " << name
             << ", HP: " << health
             << ", ATK: " << attackPower
             << ", LVL: " << level
             << ", EXP: " << experience
             << endl;
    }

    bool isAlive() const {
        return health > 0;
    }
};

int main() {
    GameCharacter knight("Knight", 120, 25);
    GameCharacter orc("Orc", 110, 22);

    cout << "Initial status:" << endl;
    knight.displayStatus();
    orc.displayStatus();
    cout << endl;

    int round = 1;
    while (knight.isAlive() && orc.isAlive() && round <= 10) {
        cout << "Round " << round << ":" << endl;
        knight.attack(orc);
        if (orc.isAlive()) {
            orc.attack(knight);
        }
        knight.displayStatus();
        orc.displayStatus();
        cout << endl;
        ++round;
    }

    cout << "Battle result:" << endl;
    if (knight.isAlive() && !orc.isAlive()) {
        cout << "Knight wins!" << endl;
    } else if (!knight.isAlive() && orc.isAlive()) {
        cout << "Orc wins!" << endl;
    } else {
        cout << "It's a draw." << endl;
    }

    return 0;
}
