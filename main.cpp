#include "PluginInterface.h"
#include <iostream>
#include <dlfcn.h> // For macOS and Linux. Use <windows.h> for Windows with appropriate API calls.

int main() {
    void* pluginHandle = nullptr;
    PluginInterface* (*createPlugin)();
    PluginInterface *plugin = nullptr;

    std::string pluginName;
    bool running = true;

    while (running) {
        std::cout << "Enter plugin name to load ('PluginA' or 'PluginB'), 'reload' to reload the current plugin, or 'quit' to exit: ";
        std::cin >> pluginName;

        if (pluginName == "quit") {
            running = false;
            continue;
        }

        // Attempt to unload any previously loaded plugin
        if (pluginHandle) {
            delete plugin; // Destroy the plugin instance
            dlclose(pluginHandle); // Close the library
            plugin = nullptr;
            pluginHandle = nullptr;
        }

        // Construct the library path and symbol name based on input
        std::string libPath = "/Users/adriantrill/Desktop/plugIn/lib" + pluginName + ".dylib"; // Use .so on Linux
        std::string symbolName = "create" + pluginName;

        // Load the plugin library
        pluginHandle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!pluginHandle) {
            std::cerr << "Failed to load plugin: " << dlerror() << std::endl;
            continue;
        }

        // Get the creation function
        createPlugin = (PluginInterface* (*)())dlsym(pluginHandle, symbolName.c_str());
        if (!createPlugin) {
            std::cerr << "Failed to find create function: " << dlerror() << std::endl;
            dlclose(pluginHandle);
            pluginHandle = nullptr;
            continue;
        }

        // Create an instance of the plugin and execute its function
        plugin = createPlugin();
        if (plugin) {
            plugin->execute();
        }
    }

    // Cleanup before exiting
    if (pluginHandle) {
        delete plugin;
        dlclose(pluginHandle);
    }

    return 0;
}


/* //! Use those commands in the command for MacOs to create the .dylib files
 *g++ -dynamiclib PluginA.cpp -o libPluginA.dylib
 *g++ -dynamiclib PluginB.cpp -o libPluginB.dylib
 *

 //! Use those commands in the command for Linux to create the .so files
 * g++ -fPIC -shared PluginA.cpp -o PluginA.so
 * g++ -fPIC -shared PluginB.cpp -o PluginB.so
 * g++ Main.cpp -o main -ldl
 */

//? ReadMe
//? This code demonstrates how to load and execute plugins at runtime using dynamic loading on macOS and Linux.
//? The code defines a simple PluginInterface class with an execute method that is implemented by PluginA and PluginB.
//? The main function allows the user to load either PluginA or PluginB dynamically at runtime by entering the plugin name.
//? The code uses dlopen and dlsym to load the shared libraries and retrieve the create function for each plugin.
//? The create function is then called to instantiate the plugin, and the execute method is invoked to run the plugin's functionality.
//? The code also handles unloading the plugin and cleaning up resources before exiting.
