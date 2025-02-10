#include <string>
#include <cstring>

// We'll define an "exported" C++ function to process user input.
// The function takes a const char* (a C-string) and returns an integer
// representing the length of that string, just as a simple example.

extern "C" {
    int processInput(const char* input) {
        // In a real app, you might parse or do other calculations here.
        // We'll just return the length of the input string.

        // Safely get the length using standard C/C++.
        return (int)strlen(input);
    }
}
