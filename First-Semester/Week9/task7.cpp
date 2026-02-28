#include <iostream>
using namespace std;

class PolyNode {
public:
    int coeff;
    int exp;
    PolyNode* next;

    PolyNode(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

class Polynomial {
private:
    PolyNode* head;

    void clear() {
        PolyNode* current = head;
        while (current != nullptr) {
            PolyNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    void copyFrom(const Polynomial& other) {
        PolyNode* current = other.head;
        while (current != nullptr) {
            insertTerm(current->coeff, current->exp);
            current = current->next;
        }
    }

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        clear();
    }

    Polynomial(const Polynomial& other) : head(nullptr) {
        copyFrom(other);
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    Polynomial(Polynomial&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    Polynomial& operator=(Polynomial&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    void insertTerm(int coeff, int exp) {
        if (coeff == 0) {
            return;
        }

        PolyNode* newNode = new PolyNode(coeff, exp);

        if (head == nullptr || exp > head->exp) {
            newNode->next = head;
            head = newNode;
            return;
        }

        if (head->exp == exp) {
            head->coeff += coeff;
            delete newNode;
            if (head->coeff == 0) {
                PolyNode* temp = head;
                head = head->next;
                delete temp;
            }
            return;
        }

        PolyNode* current = head;
        while (current->next != nullptr && current->next->exp > exp) {
            current = current->next;
        }

        if (current->next != nullptr && current->next->exp == exp) {
            current->next->coeff += coeff;
            delete newNode;
            if (current->next->coeff == 0) {
                PolyNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    Polynomial add(Polynomial& other) {
        Polynomial result;

        PolyNode* p1 = head;
        PolyNode* p2 = other.head;

        while (p1 != nullptr && p2 != nullptr) {
            if (p1->exp == p2->exp) {
                result.insertTerm(p1->coeff + p2->coeff, p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            } else if (p1->exp > p2->exp) {
                result.insertTerm(p1->coeff, p1->exp);
                p1 = p1->next;
            } else {
                result.insertTerm(p2->coeff, p2->exp);
                p2 = p2->next;
            }
        }

        while (p1 != nullptr) {
            result.insertTerm(p1->coeff, p1->exp);
            p1 = p1->next;
        }

        while (p2 != nullptr) {
            result.insertTerm(p2->coeff, p2->exp);
            p2 = p2->next;
        }

        return result;
    }

    void display() {
        if (head == nullptr) {
            cout << "0" << endl;
            return;
        }

        PolyNode* current = head;
        bool first = true;

        while (current != nullptr) {
            if (!first && current->coeff > 0) {
                cout << " + ";
            }
            if (current->coeff < 0) {
                cout << " - ";
            }

            int absCoeff = current->coeff < 0 ? -current->coeff : current->coeff;

            if (current->exp == 0) {
                cout << absCoeff;
            } else if (current->exp == 1) {
                if (absCoeff != 1) {
                    cout << absCoeff;
                }
                cout << "x";
            } else {
                if (absCoeff != 1) {
                    cout << absCoeff;
                }
                cout << "x^" << current->exp;
            }

            first = false;
            current = current->next;
        }

        cout << endl;
    }
};

int main() {
    Polynomial p1;
    p1.insertTerm(5, 3);
    p1.insertTerm(2, 2);
    p1.insertTerm(1, 0);

    Polynomial p2;
    p2.insertTerm(3, 3);
    p2.insertTerm(4, 1);
    p2.insertTerm(2, 0);

    cout << "P1: ";
    p1.display();

    cout << "P2: ";
    p2.display();

    Polynomial sum = p1.add(p2);
    cout << "Sum: ";
    sum.display();

    return 0;
}
