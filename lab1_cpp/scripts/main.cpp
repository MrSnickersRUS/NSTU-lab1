#include "commands.h"
#include "containers/stack.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    try {
        string filePath;
        string query;
    
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (arg == "--file" && i + 1 < argc) {
                filePath = argv[++i];
            } else if (arg == "--query" && i + 1 < argc) {
                query = argv[++i];
            }
        }
    
        if (filePath.empty() || query.empty()) {
            throw runtime_error("Использование: " + string(argv[0]) + " --file <путь_к_файлу> --query '<команда>'");
        }
        
        processQuery(query, filePath);
        return 0;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}