#include "copyfile.h"


int main(int argc, char **argv) {
        if (argc != 3) {
                fprintf(stderr, "%s src dst\n",argv[0]);
                return EXIT_FAILURE;
        }

	jxtopher::copyfile(argv[1], argv[2]);

	return EXIT_SUCCESS;
}
