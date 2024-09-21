#pragma once

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual void execute() = 0;
};

extern "C" {
PluginInterface* create();
}

