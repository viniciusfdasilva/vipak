#include "command.h"
#include "system.h"
#include "type.h"
#include "progress.h"
#include "globals.h"

boolean install(string package_name)
{

    boolean installation_response = get_progress(package_name, INSTALL);
    
   // if(installation_response)
    return 1;
}

boolean remove(string package_name)
{

    boolean removing_response = get_progress(package_name, REMOVE);
    return 1;
}