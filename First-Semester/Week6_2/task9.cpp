#include <iostream>
#include <string>
using namespace std;

class DeviceNV {
protected:
    string deviceId;

public:
    DeviceNV(const string& id) : deviceId(id) {}

    void showDeviceId() const {
        cout << "DeviceNV ID: " << deviceId << endl;
    }
};

class PrinterNV : public DeviceNV {
public:
    PrinterNV(const string& id) : DeviceNV(id) {}

    void printDocument(const string& doc) const {
        cout << "PrinterNV printing: " << doc << endl;
    }
};

class ScannerNV : public DeviceNV {
public:
    ScannerNV(const string& id) : DeviceNV(id) {}

    void scanDocument() const {
        cout << "ScannerNV scanning document." << endl;
    }
};

class AllInOneNV : public PrinterNV, public ScannerNV {
public:
    AllInOneNV(const string& printerId, const string& scannerId)
        : PrinterNV(printerId), ScannerNV(scannerId) {}

    void showBothDeviceIds() const {
        PrinterNV::showDeviceId();
        ScannerNV::showDeviceId();
    }
};

class DeviceV {
protected:
    string deviceId;

public:
    DeviceV(const string& id) : deviceId(id) {}

    void showDeviceId() const {
        cout << "DeviceV ID: " << deviceId << endl;
    }
};

class PrinterV : virtual public DeviceV {
public:
    PrinterV() : DeviceV("UNSET") {}

    void printDocument(const string& doc) const {
        cout << "PrinterV printing: " << doc << endl;
    }
};

class ScannerV : virtual public DeviceV {
public:
    ScannerV() : DeviceV("UNSET") {}

    void scanDocument() const {
        cout << "ScannerV scanning document." << endl;
    }
};

class AllInOneV : public PrinterV, public ScannerV {
public:
    AllInOneV(const string& id) : DeviceV(id), PrinterV(), ScannerV() {}
};

int main() {
    cout << "Without virtual inheritance (diamond issue):" << endl;
    AllInOneNV machineNV("PRN-100", "SCN-200");
    machineNV.printDocument("Report.pdf");
    machineNV.scanDocument();
    machineNV.showBothDeviceIds();

    cout << endl;
    cout << "With virtual inheritance (single shared Device):" << endl;
    AllInOneV machineV("AIO-500");
    machineV.printDocument("Invoice.pdf");
    machineV.scanDocument();
    machineV.showDeviceId();

    return 0;
}
