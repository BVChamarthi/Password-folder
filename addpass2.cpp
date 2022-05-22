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
    
    // CHECK IF THE USER CREATED A PASSWORD
    fs::path password_path("./locker/password.dat");
    if(!fs::exists(password_path)) {                        // if the user hasn't created a password :
        std::fstream password_file;
        password_file.open("./locker/password.dat", std::ios::out | std::ios::binary);
        std::cout << "Create new Password : ";              // ask the user to create a new password and store it in the protected folder itself
        std::string password;
        getline(std::cin, password);
        password_file << password;
        password_file.close();
        
        system("attrib +s +h +r \"locker/password.dat\"");          // add the hidden, system and read-only tags to the password file
        
        std::cout << "New password set\n";
    }

    bool hidden = GetFileAttributesA((LPCSTR)"locker") & FILE_ATTRIBUTE_HIDDEN;     // check if the file is hidden
    
    if(hidden) {                                    // if the file is hidden
        std::string passTry;
        std::cout << "Enter password : ";
        getline(std::cin, passTry);                 // take in a password in the shell
        
        std::fstream password_file;                               // get the actual password from the password file
        password_file.open("./locker/password.dat", std::ios::in | std::ios::binary);
        std::string password;
        getline(password_file, password);
        password_file.close();

        if(passTry.compare(password) == 0){         // check if the password is the required password (here 'joinme')
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
