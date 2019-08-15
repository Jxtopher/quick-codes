///
/// @file shellcode-run.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019
/// @brief Load and execute a shellcode
///
/// @compilation g++ -std=c++0x -Os -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Werror -Wno-unused shellcode-run.cpp
/// @execution *
///

#include <iostream>
#include <fstream>
#include <string>

#include <sys/mman.h>

using namespace std;

namespace jxtopher {

class ShellcodeExecution {
    public:
        // chargement du shellcode depuis un fichier
        ShellcodeExecution(string fileOpcode) {
            cout<<"[+] Loading shellcode"<<endl;
            fstream fin(fileOpcode, fstream::in);

            unsigned char ch;
            int state = 0;
            int i = 0;
            unsigned char hex[3];
            hex[0] = ' '; hex[1] = ' '; hex[2] = '\0';

            size_shellcode = 1;
            shellcode = new unsigned char[size_shellcode];


            while (fin >> noskipws >> ch) {
                //cout << ch; // Or whatever
                switch (state) {
                case 0:
                    if (ch == '\\')
                        state++;
                    break;
                case 1:
                    if (ch == 'x')
                        state++;
                    hex[0] = ' '; hex[1] = ' ';
                    break;
                case 2:
                    if (ch == '\\') {
                        state = 1;
                        std::string s = string(reinterpret_cast<const char *>(hex));
                        unsigned char num = std::stoi(s, 0, 16);
                        shellcode[size_shellcode - 1] = num;
                        size_shellcode++;
                        shellcode = static_cast<unsigned char*>(realloc(shellcode, sizeof(unsigned char)* size_shellcode));
                    } else {
                        hex[i%2] = ch;
                        i = (i + 1);
                    }
                default:
                    break;
                }
            }

            std::string s = string(reinterpret_cast<const char *>(hex));
            unsigned char num = std::stoi(s, 0, 16);
            shellcode[size_shellcode - 1] = num;

            fin.close();
        }

        ~ShellcodeExecution(){
            cout<<"[+] Free memory"<<endl;
            free(shellcode);
        }

        int operator()() {
            // Chagement en mémoire executable
            unsigned char* region = static_cast<unsigned char *>(mmap(NULL, size_shellcode, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON|MAP_PRIVATE, 0, 0));
            for(unsigned int i = 0 ; i < size_shellcode ; i++) {
                region[i] = shellcode[i];
            }

            if (region == MAP_FAILED) {
                perror("Could not mmap");
                return EXIT_FAILURE;
            }

            // Print shellcode
            cout<<"[+] Shellcode : ";
            for(unsigned int i = 0 ; i < size_shellcode ; i++) {
                //cout<<std::hex<<shellcode[i]<<" ";
                printf("\\X%02X", static_cast<unsigned char>(region[i]));
            }
            cout<<endl;

            // Execution
            void (*ptr)();
            ptr = reinterpret_cast<void (*)()>(region);

            cout<<"[+] Execution shellcode"<<endl;
            (ptr)();

            // Liberation des mémoires
            if (munmap(region, size_shellcode) != 0) {
                perror("Could not munmap");
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }

    private:
           unsigned size_shellcode;
           unsigned char *shellcode;
};
}

///===== Simple shellcode test ====
/// file basic.opcode :
/// \x90\x90\x90\xc3
/// ===============================

int main(int args, char**argv) {
    if (1 < args) {
        jxtopher::ShellcodeExecution scodeExe(argv[1]);
        if (scodeExe() == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    } else {
        cout<<"./shellcode-run file.opcode"<<endl;
    }
    return EXIT_SUCCESS;
}