#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include<list>
#include <utility>
#include "globals.h"
#include "utils.h"

using namespace std;

string replace(string str, char new_char, int pos)
{
    str[pos] = new_char;
    return str;
}

pair<string, string> get_file_line(string file_path)
{
    string line;

    pair<string,string> data_info;

    ifstream ifstream_file(file_path);

    string lines[2];
    int i = 0;

    while (getline(ifstream_file, line)) 
    {
        lines[i++] = line;
    }

    // Close the file
    ifstream_file.close();

    int first_position_delimiter   = lines[0].find("=");
    int second_position_delimiter  = lines[1].find("=");

    int first_position      = lines[0].length();
    int second_position     = lines[1].length();

    data_info.first  = lines[0].substr(first_position_delimiter+1, first_position);
    data_info.second = lines[1].substr(second_position_delimiter+1, second_position);

    return data_info;
}

int index(string str, char char_position)
{

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == char_position)
        {
            return i;
        }
    }

    return -1;
}

