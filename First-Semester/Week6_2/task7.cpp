#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;

    virtual bool validatePayment() const = 0;
    virtual void processPayment(double amount) = 0;
    virtual double getTransactionFee() const = 0;
    virtual string getMethodName() const = 0;
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;
    string cvv;

public:
    CreditCard(const string& number, const string& code) : cardNumber(number), cvv(code) {}

    bool validatePayment() const override {
        return cardNumber.length() >= 12 && cvv.length() == 3;
    }

    void processPayment(double amount) override {
        if (!validatePayment()) {
            cout << "CreditCard validation failed." << endl;
            return;
        }
        double fee = amount * getTransactionFee();
        cout << "CreditCard payment processed: $" << amount << ", fee: $" << fee << endl;
    }

    double getTransactionFee() const override {
        return 0.025;
    }

    string getMethodName() const override {
        return "CreditCard";
    }
};

class DebitCard : public PaymentMethod {
private:
    string cardNumber;
    string pin;

public:
    DebitCard(const string& number, const string& pinCode) : cardNumber(number), pin(pinCode) {}

    bool validatePayment() const override {
        return cardNumber.length() >= 10 && pin.length() == 4;
    }

    void processPayment(double amount) override {
        if (!validatePayment()) {
            cout << "DebitCard validation failed." << endl;
            return;
        }
        double fee = amount * getTransactionFee();
        cout << "DebitCard payment processed: $" << amount << ", fee: $" << fee << endl;
    }

    double getTransactionFee() const override {
        return 0.01;
    }

    string getMethodName() const override {
        return "DebitCard";
    }
};

class PayPal : public PaymentMethod {
private:
    string email;

public:
    PayPal(const string& mail) : email(mail) {}

    bool validatePayment() const override {
        return email.find('@') != string::npos;
    }

    void processPayment(double amount) override {
        if (!validatePayment()) {
            cout << "PayPal validation failed." << endl;
            return;
        }
        double fee = amount * getTransactionFee() + 0.30;
        cout << "PayPal payment processed: $" << amount << ", fee: $" << fee << endl;
    }

    double getTransactionFee() const override {
        return 0.03;
    }

    string getMethodName() const override {
        return "PayPal";
    }
};

class Cryptocurrency : public PaymentMethod {
private:
    string walletAddress;

public:
    Cryptocurrency(const string& wallet) : walletAddress(wallet) {}

    bool validatePayment() const override {
        return walletAddress.length() >= 10;
    }

    void processPayment(double amount) override {
        if (!validatePayment()) {
            cout << "Cryptocurrency validation failed." << endl;
            return;
        }
        double fee = getTransactionFee();
        cout << "Cryptocurrency payment processed: $" << amount << ", network fee: $" << fee << endl;
    }

    double getTransactionFee() const override {
        return 1.50;
    }

    string getMethodName() const override {
        return "Cryptocurrency";
    }
};

int main() {
    vector<PaymentMethod*> methods;
    methods.push_back(new CreditCard("1234567890123456", "123"));
    methods.push_back(new DebitCard("998877665544", "1234"));
    methods.push_back(new PayPal("user@example.com"));
    methods.push_back(new Cryptocurrency("walletXYZ12345"));

    double amount = 120.0;
    for (PaymentMethod* method : methods) {
        cout << "Method: " << method->getMethodName() << endl;
        method->processPayment(amount);
        cout << endl;
    }

    for (PaymentMethod* method : methods) {
        delete method;
    }

    return 0;
}
