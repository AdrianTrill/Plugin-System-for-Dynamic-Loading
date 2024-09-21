#include "PluginInterface.h"
#include <iostream>

class PluginA : public PluginInterface {
public:
    void execute() override {
        std::cout << "Plugin A executing..." << std::endl;
    }
};

extern "C" PluginInterface* createPluginA() {
    return new PluginA();
}