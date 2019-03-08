//!
//! \file copyfile.cpp
//! \author Jxtopher
//! \version 1
//! \date 2017
//! \copyright *
//! \brief Copy a file
//!

#ifndef JXTOPHER_COPYFILE_H
#define JXTOPHER_COPYFILE_H

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <unistd.h>

namespace jxtopher {

int copyfile(char *src, char *dst);

int copyfile(char *src, char *dst) {
	// Declaration of global variables
	struct stat sb;
	int fdin, fdout;			// File descriptor
	ssize_t size;				// Size return read
	unsigned char *buffer;			// Buffer use in the tranfert file

	// Open file source and destination
	if ((fdin = open(src, O_RDONLY)) == -1) {
                perror("[-] Error opening file");
                return EXIT_FAILURE;
        }
	if ((fdout = open(dst, O_CREAT|O_WRONLY, S_IRWXU)) == -1) {
                perror("[-] Error create file");
                close(fdin);
                return EXIT_FAILURE;
        }

	if (stat(src, &sb) == -1) {
		perror("Error read stat");
		return EXIT_FAILURE;
	}

	// Allocation of a buffer with size sb.st_blksize
	buffer = static_cast<unsigned char *>(malloc(static_cast<long unsigned int>(sb.st_blksize) * sizeof(char *)));

	// Copy file
	while ((size = read(fdin, buffer, static_cast<size_t>(sb.st_blksize))) > 0)
		write(fdout, buffer, static_cast<size_t>(size));

	// If there was an error copying the file
	if (size == -1) {
		perror("[-] Error copying file");
		close(fdin);
		close(fdout);
		return EXIT_FAILURE;
	}

	free(buffer);

	// Close file source and destination
	close(fdin);
	close(fdout);

	return EXIT_SUCCESS;
}

}

#endif
