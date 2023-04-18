#include <iostream>
#include <thread>
#include <utility>


#include "system.h"
#include "type.h"
#include "utils.h"
#include "globals.h"

using namespace std;

void print_action_header(int action)
{
    if(action == INSTALL)
    {
        
        std::cout << "[     Installing           ]" << std::endl;
      
    }else if(action == REMOVE)
    {
        std::cout << "[     Removing             ]" << std::endl; 
    }
        
}

void test_server_connection()
{
    std::cout << std::endl << "Testing server connection..." << std::endl;

    if(ping())
    {
            std::this_thread::sleep_for(1.2s);
            std::cout << "Testing Successfully!" << std::endl;
    }else{
            std::cout << std::endl << "Unavailable server!" << std::endl;
            std::cout << "The server is not ready to handle the request!" << std::endl;
            exit(0);
    }
}


void print_action_footer(int action)
{

    if(action == INSTALL)
    {
        std::cout << std::endl << "[Installed Successfully! =)]" << std::endl;
    }else if(action == REMOVE)
    {
        std::cout << std::endl << "[Removing  Successfully! =)]" << std::endl; 
    }
}

boolean check_integrity(string package_name)
{

    string remote_path =  DOWNLOAD_DIR+package_name+"."+CHECKSUM_FILE_EXTENSION;
    string local_path  =  DOWNLOAD_DIR+package_name+"."+CHECKSUM_FILE_EXTENSION+"_local";
 
    pair<string, string> local_file  = get_file_line(local_path);
    pair<string, string> remote_file = get_file_line(remote_path);
   
    return (local_file.first==remote_file.first)&&(local_file.second==remote_file.second) ? 1 : 0;

}

void test_package_integrity(string package_name)
{
    std::cout << std::endl << "Checking package integrity..." << std::endl;
    
    int local_checksum_status = checksum(package_name);
    int integrity_status      = check_integrity(package_name);
    
    if(local_checksum_status && integrity_status)
    {
        std::this_thread::sleep_for(1.2s);
        std::cout << "Checking Successfully!" << std::endl << std::endl;
    }else{

        std::this_thread::sleep_for(1.2s);
        std::cout << "Downloaded file is not integrity!" << std::endl << std::endl;

        rm(package_name);
        rm(package_name+"."+CHECKSUM_FILE_EXTENSION);
        rm(package_name+"."+CHECKSUM_FILE_EXTENSION+"_local");
        rm(INFO_PACKAGE);

        exit(1);
    }

}
   

void get_package_info(string package_name)
{
    std::cout << std::endl << "package name: " << package_name << std::endl;
        
    pair<string, string> infos = get_file_line(DOWNLOAD_DIR + "/" + INFO_PACKAGE);

    string author  = infos.first;
    string version = infos.second;

    std::cout << "author: " << author << std::endl;
    std::cout << "version: " << version << std::endl << std::endl;
}

boolean get_progress(string package_name, int action)
{

    boolean wget_response = wget(package_name);

    if(wget_response)
    {
        
        print_action_header(action);
        test_server_connection();
        test_package_integrity(package_name);
        get_package_info(package_name);
        
        
        string progress = "=>";
        string progress_install = "[" + progress + "                        ]";


        for(int i = 0; i < 25; i++)
        {

            int porcent = (int)(((double)i/(double)24)*100);
            std::cout << progress_install << " - " << porcent << "%" << std::endl;

            int pos = index(progress_install, '>');

            progress_install = replace(progress_install, '=', pos);
            progress_install = replace(progress_install, '>', pos+1);

            std::this_thread::sleep_for(0.1s);
        }

        print_action_footer(action);
        
        rm(package_name);
        rm(package_name+"."+CHECKSUM_FILE_EXTENSION);
        rm(package_name+"."+CHECKSUM_FILE_EXTENSION+"_local");
        rm(INFO_PACKAGE);
    }else{
        cout << "Error! Package not found!" << endl;
        exit(1);
    }

   
    
    return 1;
}