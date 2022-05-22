#include <iostream>
#include <fileapi.h>
#include <string>

int main() {

    bool hidden = GetFileAttributesA((LPCSTR)"locker") & FILE_ATTRIBUTE_HIDDEN;     // check if the file is hidden
    
    if(hidden) {                                    // if the file is hidden
        std::string passTry;
        getline(std::cin, passTry);                 // take in a password in the shell

        if(passTry.compare("joinme") == 0){         // check if the password is the required password (here 'joinme')
            system("attrib -s -h \"locker\"");      // remove the file's hidden (-h) and system (-s) tags.
                                                    // the hidden tag hides the file and the system tag will make it read only
                                                    // which makes it so that one cannot unhide the file with the file explorer options
            return 0;           // exit the program
        }
    }

    system("attrib +s +h \"locker\"");          // add the hidden tag and the system tag to the file

    return 0;
}