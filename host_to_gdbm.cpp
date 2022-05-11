#include <iostream>
#include <fstream>
#include <vector>


using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;

int main()
{
    string filename("/etc/hosts");
    vector<string> lines;
    string line;
    string ip;
    bool ip_started = false;
    bool ip_done = false;
    bool host_started = false;
    string host;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line)){
        lines.push_back(line);
    }
    for (const auto &i : lines){
        ip =  "";
        host =  "";
        ip_started = false;
        host_started = false;
        ip_done = false;
        for(int o = 0 ; i.length() > o; o++){
            if(i[o]=='#')
                break;
            if(ip_done == false && i[o]!=' '){
                ip.append(i.substr(o, 1));
                ip_started = true;
                continue;
            }
            if(ip_done == true && i[o]!=' '){
                host.append(i.substr(o, 1));
                host_started = true;
                continue;
            }
            if(host_started == true && i[o]==' '){
               cout << host <<  "=" << ip <<endl;
               host_started = false;
               continue;
            }
            if(i[o]==' ' && ip_started == true){
                ip_done = true;
                continue;
            }

        }
    }
    input_file.close();
    return EXIT_SUCCESS;
}
