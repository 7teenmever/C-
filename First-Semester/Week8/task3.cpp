#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BrowserHistory {
private:
    stack<string> backHistory;
    stack<string> forwardHistory;
    string currentPage;

public:
    explicit BrowserHistory(const string& homepage)
        : currentPage(homepage) {}

    void visit(const string& url) {
        backHistory.push(currentPage);
        currentPage = url;

        while (!forwardHistory.empty()) {
            forwardHistory.pop();
        }
    }

    string back(int steps) {
        while (steps > 0 && !backHistory.empty()) {
            forwardHistory.push(currentPage);
            currentPage = backHistory.top();
            backHistory.pop();
            --steps;
        }
        return currentPage;
    }

    string forward(int steps) {
        while (steps > 0 && !forwardHistory.empty()) {
            backHistory.push(currentPage);
            currentPage = forwardHistory.top();
            forwardHistory.pop();
            --steps;
        }
        return currentPage;
    }

    string getCurrentPage() const {
        return currentPage;
    }
};

int main() {
    BrowserHistory browser("home.com");

    browser.visit("news.com");
    browser.visit("docs.com");
    browser.visit("mail.com");

    cout << "Current: " << browser.getCurrentPage() << endl;
    cout << "Back 1: " << browser.back(1) << endl;
    cout << "Back 1: " << browser.back(1) << endl;
    cout << "Forward 1: " << browser.forward(1) << endl;

    browser.visit("video.com");
    cout << "Current after visit: " << browser.getCurrentPage() << endl;
    cout << "Forward 2 (should stay same): " << browser.forward(2) << endl;

    return 0;
}
