#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string s1 = "";
    std::string s2 = "";

    std::ifstream in("file");
    //assure(in, "file");
    int i = 1;
    int n = 0;

    while ( true ) {
        in >> s1;
        in >> s2;
        if (s1 != "" && s2 == "") {
            std::cout << s1;
            break;
        } else if (s1 == "" && s2 == "") {
            break;
        } else {
            std::cout << s2 << '\n' << s1 << '\n';
            s1 = s2 = "";
        }
    }
    std::cout << std::endl;
    
    return 0;
}