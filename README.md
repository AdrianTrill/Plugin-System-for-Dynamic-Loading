---

# Plugin System for Dynamic Loading

## Overview

This project demonstrates a plugin system implemented in C++ for dynamically loading shared libraries (plugins) at runtime. The code supports dynamic library loading using `dlopen` and `dlsym` (on macOS and Linux), with options to load multiple plugins and execute their functions without recompiling the main program.

### Features

- **Platform Support**: macOS and Linux.
- **Dynamic Plugin Loading**: Load and execute plugins (e.g., `PluginA`, `PluginB`) at runtime using shared libraries (`.dylib` for macOS and `.so` for Linux).
- **Modular Architecture**: Easily extendable by adding new plugins.
- **Resource Management**: Safely loads and unloads shared libraries while managing memory and resource clean-up.

## How It Works

- The `PluginInterface` class defines a common interface for all plugins with an abstract `execute()` method.
- `PluginA` and `PluginB` are two sample plugin implementations of the `PluginInterface` class.
- The main program allows users to specify which plugin to load, and dynamically loads the corresponding shared library, executes the plugin, and handles cleanup.

## Project Structure

```bash
.
├── main.cpp             # Main application logic
├── PluginInterface.h    # Base interface for plugins
├── PluginA.cpp          # Implementation of Plugin A
├── PluginB.cpp          # Implementation of Plugin B
```

## Build Instructions

### macOS

1. Compile `PluginA` and `PluginB` as dynamic libraries:

   ```bash
   g++ -dynamiclib PluginA.cpp -o libPluginA.dylib
   g++ -dynamiclib PluginB.cpp -o libPluginB.dylib
   ```

2. Compile and link the `main.cpp` with the dynamic loading library (`-ldl`):

   ```bash
   g++ main.cpp -o main -ldl
   ```

3. Run the program:

   ```bash
   ./main
   ```

### Linux

1. Compile `PluginA` and `PluginB` as shared libraries:

   ```bash
   g++ -fPIC -shared PluginA.cpp -o libPluginA.so
   g++ -fPIC -shared PluginB.cpp -o libPluginB.so
   ```

2. Compile and link the `main.cpp` with `-ldl`:

   ```bash
   g++ main.cpp -o main -ldl
   ```

3. Run the program:

   ```bash
   ./main
   ```

## How to Use

1. When the program starts, it prompts you to enter the name of the plugin you wish to load (`PluginA` or `PluginB`), or to enter `quit` to exit the program.
   
2. The system will load the corresponding shared library (`libPluginA.dylib`/`.so` or `libPluginB.dylib`/`.so`), create an instance of the plugin, and call its `execute()` method.

3. You can enter `reload` to reload the currently loaded plugin.

4. Example output:

   ```bash
   Enter plugin name to load ('PluginA' or 'PluginB'), 'reload' to reload the current plugin, or 'quit' to exit: PluginA
   Plugin A executing...
   ```

## Extending the System

To add new plugins:

1. Implement a new class inheriting from `PluginInterface` with the `execute()` method.
2. Create a factory function (e.g., `createPluginX`) and export it.
3. Follow the same compilation steps to generate the shared library.
4. Update the `main.cpp` code if necessary to recognize the new plugin.

## License

MIT License. Feel free to use, modify, and distribute.

---
