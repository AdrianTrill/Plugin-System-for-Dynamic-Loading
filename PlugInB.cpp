#include "PluginInterface.h"
#include <iostream>

class PluginB : public PluginInterface {
public:
    void execute() override {
        std::cout << "Plugin B executing..." << std::endl;
    }
};

extern "C" PluginInterface* createPluginB() {
    return new PluginB();
}