#include<iostream>

#include "type.h"
#include "sysinfo.h"
#include "command.h"

using namespace std;

void version()
{
    std::cout << SYSTEM_NAME << ": Version " + SYSTEM_VERSION << std::endl;
    std::cout << "Development by: " << SYSTEM_AUTHOR << std::endl;
}

void help()
{
    std::cout << "Usages: " << SYSTEM_NAME << " <options>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "(remove | install) [package]" << std::endl;
    std::cout << "(-v | --version) - Display system version" << std::endl;
    std::cout << "(-h | --help) - Display this information" << std::endl;
}

int main(int argc, char** argv)
{
    if(argc == 1) // Only system command
    {
        help();
    }else{

        string cmd = argv[1];

        if(cmd == "--version" || cmd == "-v")
        {
            version();

        }else if(cmd == "--help" || cmd == "-h")
        {
            help();
        }else if(cmd == "install")
        {
            if(argc > 2){
                string package_name = argv[2];      
                install(package_name);
            }else{
                std::cout << "Installing error: Package name can not be empty!" << std::endl;
            }
           
        }else if(cmd == "remove")
        {
            if(argc > 2){
                string package_name = argv[2];
                remove(package_name);
            }else{
                std::cout << "Removing error: Package name can not be empty!" << std::endl;
            }
        }else{
            std::cout << "Error: [" + cmd + "] is not a valid command of " << SYSTEM_NAME << " system!" << std::endl;
        }
    }

    return 0;
}