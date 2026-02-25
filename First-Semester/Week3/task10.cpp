#include <iostream>
using namespace std;

struct Character{
    string name;
    string classType;
    int hp;
    int attack;
    int mana;
    int level;
};
Character createCharacter(int choice, string name){
    Character c;
    c.name = name;
    c.level = 1;
    switch(choice){
        case 1: // Warrior
            c.classType = "Warrior";
            c.hp = 150;
            c.attack = 20;
            c.mana = 20;
            break;

        case 2: // Mage
            c.classType = "Mage";
            c.hp = 80;
            c.attack = 25;
            c.mana = 100;
            break;

        case 3: // Archer
            c.classType = "Archer";
            c.hp = 100;
            c.attack = 18;
            c.mana = 40;
            break;
    }
    return c;
}
void showStats(const Character& c){
    cout<<"\n===== CHARACTER STATS =====\n";
    cout<<"Name: "<<c.name<<endl;
    cout<<"Class: "<<c.classType<<endl;
    cout<<"Level: "<<c.level<<endl;
    cout<<"HP: "<<c.hp<<endl;
    cout<<"Attack: "<<c.attack<<endl;
    cout<<"Mana: "<<c.mana<<endl;
}
void showSkills(const Character& c){
    cout<<"\nSkills:\n";
    if(c.classType == "Warrior"){
        cout<<"- Slash\n- Shield Block\n";
    }
    else if(c.classType == "Mage"){
        cout<<"- Fireball\n- Ice Spike\n";
    }
    else if(c.classType == "Archer"){
        cout<<"- Arrow Shot\n- Multi Shot\n";
    }
}
void levelUp(Character& c){
    c.level++;
    c.hp += 20;
    c.attack += 5;
    c.mana += 10;
    cout<<"\nLevel Up! You are now level "<<c.level<<"!\n";
}
int main(){
    int choice;
    string name;
    cout<<"Enter character name: ";
    cin>>name;
    cout<<"\nChoose class:\n";
    cout<<"1. Warrior\n2. Mage\n3. Archer\n";
    cin>>choice;
    Character player = createCharacter(choice, name);
    while(true){
        int action;
        showStats(player);
        showSkills(player);
        cout<<"\n1. Level Up\n2. Exit Game\nChoose action: ";
        cin>>action;
        switch(action){
            case 1:
                levelUp(player);
                break;

            case 2:
                cout<<"Exiting game...\n";
                break;

            default:
                cout<<"Invalid choice\n";
        }
        if(action == 2) break;
    }
    return 0;
}