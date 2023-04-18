#ifndef __UTILS_H__

    #include<string>

    using namespace std;

    int index(string str, char char_position);
    pair<string, string> get_file_line(string file_path);
    string replace(string str, char new_char, int pos);
    
#endif // __UTILS_H__