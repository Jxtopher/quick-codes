//!
//! \file filerepair.cpp
//! \author Jxtopher
//! \version 1
//! \date 27 Jan 2019
//! \brief Réparer un fichier avec plusieurs versions corrompu du même fichier
//! @Compilation: g++ -std=c++0x -Wall -Os -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused  filerepair.cpp -o filerepair
//!

#include <bitset>
#include <iostream>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

namespace jxtopher {

class ReadFile {
	public:
	ReadFile(char * const namefile) {
		// Open file source and destination
		if ((fdin = open(namefile, O_RDONLY)) == -1) {
			cout<<">"<<namefile<<endl;
			throw string("[-] Error opening file for read");
		}

		if (stat(namefile, &sb) == -1)
			throw string("[-] Error read stat");

		// Allocation of a buffer with size sb.st_blksize
		buffer = static_cast<unsigned char *>(malloc(static_cast<long unsigned int>(sb.st_blksize) * sizeof(char *)));
		size = 0;
	}

	~ReadFile() {
		free(buffer);
		close(fdin);
	}

	bool bufferNotEmpty() {
		if (size == 0) {
			size = read(fdin, buffer, static_cast<size_t>(sb.st_blksize));
			maxsize = size;
			if (size > 0)
				return true;
			else if (size == 0)
				return false;
			else if (size == -1) {
				throw string("[-] Error copying file");
			}
		} else {
			return true;
		}
		return true;
	}

	unsigned char readByte() {
		size--;
		return buffer[maxsize - size - 1];
	}

	protected:
	ssize_t maxsize, size;
	int fdin;				// File descriptor
	unsigned char *buffer;			// Buffer use in the tranfert file
	struct stat sb;

};

class WriteFile {
	public:

	WriteFile(char * const namefile) {
		if ((fdout = open(namefile, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) == -1) {
			throw string("[-] Error opening file for write");
		}

		if (stat(namefile, &sb) == -1)
			throw string("[-] Error read stat");

		// Allocation of a buffer with size sb.st_blksize
		maxsize = static_cast<ssize_t>(sb.st_blksize * sizeof(char *));
		size = 0;
		buffer = static_cast<unsigned char *>(malloc(static_cast<long unsigned int>(sb.st_blksize) * sizeof(char *)));
	}

	~WriteFile() {
		write(fdout, buffer, static_cast<size_t>(size));
		free(buffer);
		close(fdout);
	}

	void writeByte(unsigned char byte) {
		if (size < maxsize) {
			buffer[size] = byte;
			size++;
		} else {
			write(fdout, buffer, static_cast<size_t>(size));
			buffer[0] = byte;
			size = 1;
		}
	}

	protected:
	ssize_t maxsize, size;
	int fdout;		// File descriptor
	unsigned char *buffer;	// Buffer use in the tranfert file
	struct stat sb;


};

bool filerepair(int argc, char **argv) {
	unsigned int nbfile = static_cast<unsigned int>(argc - 2);

	WriteFile wf(argv[1]);
	ReadFile *rf[nbfile];
	bitset<8> byte[nbfile];
	bitset<8> recoveryByte;
	for (unsigned int i = 0 ; i < nbfile ; i++)
		rf[i] = new ReadFile(argv[2 + i]);

	unsigned int coutNotEmpty = 0;
	for (unsigned int i = 0 ; i < nbfile ; i++)
		coutNotEmpty += rf[i]->bufferNotEmpty();

	while(ceil(nbfile/2.0) <= coutNotEmpty) {
		for (unsigned int i = 0 ; i < nbfile ; i++) {
			byte[i] = rf[i]->readByte();
		}

		for (unsigned int i = 0 ; i < 8 ; i++) {
			unsigned int nbOne = 0, nbZero = 0;
			for (unsigned int j = 0 ; j < nbfile ; j++) {
				byte[j].test(i) ? nbOne++ : nbZero++;
			}

			if (nbOne == nbZero) {
				cerr<<"[-] "<<__FILE__<<":"<<__LINE__<<" Undecidable choice"<<endl;
				return EXIT_FAILURE;
			} else if (nbOne < nbZero) {
				recoveryByte.reset(i);
			} else {
				recoveryByte.set(i);
			}
		}

		wf.writeByte(static_cast<unsigned char>(recoveryByte.to_ulong()));

		coutNotEmpty = 0;
		for (unsigned int i = 0 ; i < nbfile ; i++)
			coutNotEmpty += rf[i]->bufferNotEmpty();
	}
	return EXIT_SUCCESS;

}

}

int main(int argc, char **argv) {
	if (argc < 5) {
		cerr<<"./a.out f.out v1.in v2.in v3.in"<<endl;
		exit(EXIT_FAILURE);
	}

	try {
		jxtopher::filerepair(argc, argv);
	} catch(string const& s) {
		cerr<<s<<endl;
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
