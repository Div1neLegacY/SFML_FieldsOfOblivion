#include <iostream>
#include <filesystem>
#include <dlfcn.h>

namespace fs = std::filesystem;

// Match the signature of your exported DLL function
typedef int (*GetNumFn)();

// Paths relative to your bin directory execution context
const std::string SOURCE_LIB = "./build/bin/libgame_logic.so";
const std::string RUNNING_LIB = "./build/bin/libgame_logic_running.so";

struct HotReloadSystem {
    void* handle = nullptr;
    fs::file_time_type lastKnownWriteTime;
    GetNumFn hot_reload_get_num = nullptr;
};

void try_hot_reload(HotReloadSystem& sys) {
    if (!fs::exists(SOURCE_LIB)) return;

    try {
        // Fetch the file modification timestamp from the OS
        auto currentWriteTime = fs::last_write_time(SOURCE_LIB);

        // If this matches our active instance, skip reloading completely
        if (sys.handle && currentWriteTime == sys.lastKnownWriteTime) return;

        // 1. Unload the previous version if it exists
        if (sys.handle) {
            dlclose(sys.handle);
            sys.handle = nullptr;
            sys.hot_reload_get_num = nullptr;
        }

        // 2. Small defensive sleep to allow the compiler a tiny window to completely finish flush operations
        sf::sleep(sf::milliseconds(50));

        // 3. Shadow Copy: duplicate the new library so the original file stays unlocked for future builds
        fs::copy_file(SOURCE_LIB, RUNNING_LIB, fs::copy_options::overwrite_existing);
        sys.lastKnownWriteTime = currentWriteTime;

        // 4. Open our standalone shadow copy instead of the main target
        sys.handle = dlopen(RUNNING_LIB.c_str(), RTLD_NOW);
        if (!sys.handle) {
            std::cerr << "[Watcher] Failed loading runtime instance: " << dlerror() << "\n";
            return;
        }

        // 5. Re-bind your function pointer matching your exact export symbol name
        sys.hot_reload_get_num = (GetNumFn)dlsym(sys.handle, "hot_reload_get_num");
        
        if (!sys.hot_reload_get_num) {
            std::cerr << "[Watcher] Error resolving dynamic function pointer symbol: " << dlerror() << "\n";
        } else {
            std::cout << "[Watcher] SUCCESS: libgame_logic.so successfully swapped live!\n";
        }

    } catch (const fs::filesystem_error& e) {
        // Catch filesystem exceptions cleanly if we hit a race condition mid-build compilation pass
        return; 
    }
}