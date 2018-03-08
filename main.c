#include <stdio.h>

int main() {
	
}

/**
 * Reads a line from the console, handling errors and removing line endings.
 *
 * @param
 *  - inputLength: The max length of the input.
 *  - output: The inputted line is returned through this array.
 */
bool requestInput(int inputLength, char output[]) {
    if (fgets(output, inputLength, stdin)) {
        if (output[0] == '\n' || output[0] == '\0') {
            return false;
        } else {
            for (int i = 0; i < inputLength; i++) {//Loop through the list and find the first return carriage. Replace this with the null terminator.
                if (output[i] == '\n') {
                    output[i] = '\0';
                    break;
                }
            }
            return true;
        }
    } else {
        printf("We encountered an error reading input.");
        exit(1);
    }
    return false;
}