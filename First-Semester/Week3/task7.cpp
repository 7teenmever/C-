#include <iostream>
using namespace std;
float totalCost=0;
struct prices{
    int burger=5;
    int pizza=8;
    int pasta=7;
    int salad=4;
    int FrenchFries=3;
    int drink=2;
    int desert=6;
};
float discount(float total){
    if (total>=50 and total < 100)
    {
        total=(total*10)/100;
    }
    else if(total >= 100)
    {
        total=(total*25)/100;
    }
    return total;
}
void menu(){
    cout<<"\n==========MENU==========\n";
    cout<<"1 - Burger = $5\n2 - Pizza = $8\n3 - Pasta = $7\n4 - Salad - $4\n5 - French Fries = $3\n6 - Drink = $2\n7 - Desert = $6\n8 - Order\n9 - ReOrder\n";
    cout<<"========================\n";
}
int main(){
    int choice;
    prices p;
    menu();
    while (true){
        cout<<"Enter Order: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            totalCost+=p.burger;
            break;
        case 2:
            totalCost+=p.pizza;
            break;
        case 3:
            totalCost+=p.pasta;
            break;
        case 4:
            totalCost+=p.salad;
            break;
        case 5: 
            totalCost+=p.FrenchFries;
            break;
        case 6:
            totalCost+=p.drink;
            break;
        case 7:
            totalCost+=p.desert;
            break;
        case 8:
            cout<<"\n========================\n";
            cout<<"Total Cost: $"<<totalCost - discount(totalCost);
            cout<<"\n========================\n";
            return 0;
            
            break;
        case 9:
            totalCost=0;
            break;
        default:
            cout<<"Invalid Order: \n";
            break;
        }
    }
    return 0;
}