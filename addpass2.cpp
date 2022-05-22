#include <iostream>
#include <filesystem>
#include <fileapi.h>
#include <string>
namespace fs = std::filesystem;

int main() {
    std::string folder = "./locker";

    // CHECK IF THE FOLDER EXISTS
    fs::path folder_path(folder);
    if(!fs::exists(folder_path)) {      // if the folder doesn't exist, make it
        fs::create_directory(folder);
        system("attrib +s +h \"locker\"");          // add the hidden tag and the system tag to the file
    }

    bool hidden = GetFileAttributesA((LPCSTR)"locker") & FILE_ATTRIBUTE_HIDDEN;     // check if the file is hidden
    
    if(hidden) {                                    // if the file is hidden
        std::string passTry;
        std::cout << "Enter password : ";
        getline(std::cin, passTry);                 // take in a password in the shell

        if(passTry.compare("joinme") == 0){         // check if the password is the required password (here 'joinme')
            system("attrib -s -h \"locker\"");      // remove the file's hidden (-h) and system (-s) tags.
                                                    // the hidden tag hides the file and the system tag will make it read only
                                                    // which makes it so that one cannot unhide the file with the file explorer options
            std::cout << "Folder is unlocked\n";
            return 0;           // exit the program
        } else {
            std::cout << "Incorrect password\n";
            return 0;
        }
    }

    system("attrib +s +h \"locker\"");          // add the hidden tag and the system tag to the file
    std::cout << "Folder is locked\n";
    return 0;
}
