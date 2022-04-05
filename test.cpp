#include <dirent.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
bool checkIfBinary(string fileName) {
    int c;
    std::ifstream ifs(fileName);
    if (ifs.fail()) {
        return 0;
    }
    while ((c = ifs.get()) != EOF && c <= 127)
        cout<<c;
    if (c == EOF) {
        return false;
    } else {
        return true;
    }
}
bool is_text(char *filename) {
    FILE *f = fopen(filename, "r");
    int c;
    if (!f) {
        perror("fopen failed");
        return false;
    }
    
    while ((c=fgetc(f) != EOF)) {
        if (!(isascii(c) || iscntrl(c)) && !isspace(c)) {
            printf("is binary\n");
            fclose(f);
            return false;
        }
    }
    printf("is text\n");
    fclose(f);
    return true;
}
int main() {

    char* p = (char*)"shit.txt";;
    bool is = checkIfBinary(p);
    if(is){
        cout<<endl <<"PASS";
    }
    else{
        cout<<endl <<"FAIL";
    }
    return 0;
}
