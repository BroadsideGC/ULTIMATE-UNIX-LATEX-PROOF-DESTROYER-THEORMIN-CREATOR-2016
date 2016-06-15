#include <iostream>
#include <algorithm>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>

using namespace std;

void delet(string &name) {
    freopen(name.c_str(), "r", stdin);
    mkdir("teormin", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    freopen(("teormin/" + name).c_str(), "w", stdout);
    string s;
    cin.clear();
    size_t proof = 0;
    while (getline(cin, s)) {
        if (s.find("\\begin{proof}") < s.size()) {
            proof++;
        }
        if (!proof && s.find("\\newpage") > s.size()) {
            cout << s << "\n";
        }
        if (s.find("\\end{proof}") < s.size()) {
            proof--;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<string> files;
    string dir = ".";
    auto dp = opendir(dir.c_str());
    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (strstr(dirp->d_name, ".tex") && ((string) dirp->d_name) != "main.tex") {
            files.push_back(string(dirp->d_name));
        }
    }
    closedir(dp);
    for (auto file : files) {
        delet(file);
    }
    return 0;
}