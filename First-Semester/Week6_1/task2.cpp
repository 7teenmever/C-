#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(const string& number = "N/A", const string& holder = "Unknown", double initialBalance = 0.0)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit failed: amount must be positive." << endl;
            return;
        }
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal failed: amount must be positive." << endl;
            return;
        }
        if (amount > balance) {
            cout << "Withdrawal failed: insufficient balance." << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << endl;
    }

    void displayBalance() const {
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: " << balance << endl;
    }
};

int main() {
    BankAccount account1("ACC1001", "Alice", 1000.0);

    account1.displayBalance();
    cout << endl;

    account1.deposit(250.0);
    account1.withdraw(300.0);
    account1.withdraw(2000.0);

    cout << endl;
    account1.displayBalance();

    return 0;
}
