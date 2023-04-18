#include "system.h"
#include "type.h"
#include "globals.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

boolean ping()
{
    string cmd = "ping -w 1 -c 1 " + SERVER_DOMAIN + " > /dev/null";

    int system_response = system(cmd.c_str());
    return system_response == 0 ? 1 : 0;
}

boolean checksum(string package_name)
{
    string files = DOWNLOAD_DIR+package_name+" "+DOWNLOAD_DIR+INFO_PACKAGE+" >> "; 
    string checksum_cmd = "sha256sum " + files + DOWNLOAD_DIR + package_name+"."+CHECKSUM_FILE_EXTENSION+"_local";

    int checksum_response = system(checksum_cmd.c_str());
    
    return checksum_response == 0 ? 1 : 0;
}

boolean wget(string package_name)
{
    string wget_cmd = "wget"+WGET_MAJOR_VERSION+"-"+WGET_MINOR_VERSION+"/bin/wget"+WGET_MAJOR_VERSION;
    string uri      = " "+SERVER_DOMAIN+"/"+REPOSITORY_NAME+"/"+package_name+"/latest";
    
    string package_uri  = uri+"/"+package_name;
    string info_uri     = uri+"/"+INFO_PACKAGE;
    string checksum_uri = uri+"/"+package_name+"."+CHECKSUM_FILE_EXTENSION;

    string package_cmd  = wget_cmd + package_uri  + " -P "  + DOWNLOAD_DIR + " > /dev/null";
    string info_cmd     = wget_cmd + info_uri     + " -P "  + DOWNLOAD_DIR + " > /dev/null";
    string checksum_cmd = wget_cmd + checksum_uri + " -P "  + DOWNLOAD_DIR + " > /dev/null";
    
    int package_response  = system(package_cmd.c_str());
    int info_response     = system(info_cmd.c_str());
    int checksum_response = system(checksum_cmd.c_str());

    return (package_response == 0 && info_response == 0 && checksum_response == 0) ? 1 : 0;
}

boolean rm(string file)
{
    string cmd = "rm " + DOWNLOAD_DIR + "/" + file;

    int response = system(cmd.c_str());
    return (response == 0 && response == 0) ? 1 : 0;
}