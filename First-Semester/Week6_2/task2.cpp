#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;

protected:
    vector<string> transactionHistory;

public:
    BankAccount(const string& number, double initialBalance)
        : accountNumber(number), balance(initialBalance) {
        transactionHistory.push_back("Account created with balance: " + to_string(balance));
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit failed: amount must be positive." << endl;
            return;
        }
        balance += amount;
        transactionHistory.push_back("Deposited: " + to_string(amount));
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
        transactionHistory.push_back("Withdrew: " + to_string(amount));
    }

    double getBalance() const {
        return balance;
    }

    string getAccountNumber() const {
        return accountNumber;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(const string& number, double initialBalance, double rate)
        : BankAccount(number, initialBalance), interestRate(rate) {}

    void applyInterest() {
        double interest = getBalance() * (interestRate / 100.0);

        // balance += interest; // Not allowed: balance is private in BankAccount.
        deposit(interest);

        transactionHistory.push_back("Interest applied at rate: " + to_string(interestRate) + "%");
    }

    void displayTransactionHistory() const {
        cout << "Transaction history for account " << getAccountNumber() << ":" << endl;
        for (const string& entry : transactionHistory) {
            cout << "- " << entry << endl;
        }
    }
};

int main() {
    SavingsAccount account("SA-1001", 1000.0, 5.0);

    account.deposit(200.0);
    account.withdraw(150.0);
    account.applyInterest();

    cout << "Current balance: " << account.getBalance() << endl;
    account.displayTransactionHistory();

    return 0;
}
