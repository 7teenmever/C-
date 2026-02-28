#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Position {
    int x;
    int y;
};

class GameCharacter {
protected:
    string name;
    int health;
    Position position;
    int level;

public:
    GameCharacter(const string& characterName, int hp, Position pos, int lvl = 1)
        : name(characterName), health(hp), position(pos), level(lvl) {}

    virtual ~GameCharacter() = default;

    virtual int attack() = 0;
    virtual int defend(int incomingDamage) = 0;
    virtual void useSpecialAbility() = 0;

    void takeDamage(int damage) {
        if (damage < 0) {
            damage = 0;
        }
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    string getName() const {
        return name;
    }

    void showStatus() const {
        cout << name << " | HP: " << health
             << ", Pos: (" << position.x << ", " << position.y << ")"
             << ", Level: " << level << endl;
    }
};

class Warrior : public GameCharacter {
public:
    Warrior(const string& n, Position pos) : GameCharacter(n, 140, pos) {}

    int attack() override {
        return 18 + level * 3;
    }

    int defend(int incomingDamage) override {
        int reduced = incomingDamage - 8;
        return (reduced > 0) ? reduced : 0;
    }

    void useSpecialAbility() override {
        cout << name << " uses Shield Wall: defense increased this turn." << endl;
    }
};

class Mage : public GameCharacter {
public:
    Mage(const string& n, Position pos) : GameCharacter(n, 90, pos) {}

    int attack() override {
        return 24 + level * 4;
    }

    int defend(int incomingDamage) override {
        int reduced = incomingDamage - 2;
        return (reduced > 0) ? reduced : 0;
    }

    void useSpecialAbility() override {
        cout << name << " casts Fireball for burst damage." << endl;
    }
};

class Archer : public GameCharacter {
public:
    Archer(const string& n, Position pos) : GameCharacter(n, 110, pos) {}

    int attack() override {
        return 20 + level * 3;
    }

    int defend(int incomingDamage) override {
        int reduced = incomingDamage - 5;
        return (reduced > 0) ? reduced : 0;
    }

    void useSpecialAbility() override {
        cout << name << " uses Piercing Shot from range." << endl;
    }
};

void performAttack(GameCharacter& attacker, GameCharacter& defender) {
    if (!attacker.isAlive() || !defender.isAlive()) {
        return;
    }

    int baseDamage = attacker.attack();
    int finalDamage = defender.defend(baseDamage);
    defender.takeDamage(finalDamage);

    cout << attacker.getName() << " attacks " << defender.getName()
         << " for " << finalDamage << " damage." << endl;
}

int main() {
    Warrior warrior("Thorin", {0, 0});
    Mage mage("Lyra", {1, 0});
    Archer archer("Rin", {2, 0});

    vector<GameCharacter*> characters = {&warrior, &mage, &archer};

    cout << "Initial status:" << endl;
    for (GameCharacter* c : characters) {
        c->showStatus();
    }
    cout << endl;

    warrior.useSpecialAbility();
    mage.useSpecialAbility();
    archer.useSpecialAbility();
    cout << endl;

    for (int round = 1; round <= 3; ++round) {
        cout << "Round " << round << ":" << endl;
        performAttack(warrior, mage);
        performAttack(mage, archer);
        performAttack(archer, warrior);

        for (GameCharacter* c : characters) {
            c->showStatus();
        }
        cout << endl;
    }

    return 0;
}
