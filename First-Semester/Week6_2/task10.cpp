#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const string& message) = 0;
};

class FileLogger : public Logger {
private:
    string fileName;

public:
    FileLogger(const string& file = "app.log") : fileName(file) {}

    void log(const string& message) override {
        ofstream out(fileName, ios::app);
        if (!out) {
            cout << "FileLogger error: unable to open file." << endl;
            return;
        }
        out << "[FILE] " << message << endl;
        cout << "FileLogger wrote to " << fileName << endl;
    }
};

class ConsoleLogger : public Logger {
public:
    void log(const string& message) override {
        cout << "[CONSOLE] " << message << endl;
    }
};

class DatabaseLogger : public Logger {
public:
    void log(const string& message) override {
        cout << "[DATABASE] Stored log entry: " << message << endl;
    }
};

class LoggerFactory {
public:
    static Logger* createLogger(const string& type) {
        if (type == "file") {
            return new FileLogger();
        }
        if (type == "console") {
            return new ConsoleLogger();
        }
        if (type == "database") {
            return new DatabaseLogger();
        }
        return nullptr;
    }
};

int main() {
    vector<string> loggerTypes = {"console", "file", "database", "unknown"};

    for (const string& type : loggerTypes) {
        Logger* logger = LoggerFactory::createLogger(type);

        if (logger == nullptr) {
            cout << "Unsupported logger type: " << type << endl;
            continue;
        }

        logger->log("Factory-created logger of type '" + type + "' is active.");
        delete logger;
    }

    return 0;
}
