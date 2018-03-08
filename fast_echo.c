#define _BSD_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define BUFFER_SIZE BUFSIZ

int main(int argc, char *argv[]) {
	size_t len, written, size;
	char *buffer;

	// Check arguments.
	if (argc <= 1) {
		fprintf(stderr, "usage: %s text\n", *argv);
		return 1;
	}

	// Get the length of the input string and allocate the
	// buffer.
	len = strlen(argv[1]);
	size = len * BUFFER_SIZE;
	buffer = mmap(NULL, size, PROT_READ | PROT_WRITE,
	              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (buffer == MAP_FAILED) {
		perror("failed to get memory page: ");
		return -1;
	}

	// Populate the buffer.
	for (size_t i = 0; i < size; i++) {
		buffer[i] = argv[1][i % len];
	}

	// Write to the output.
	do {
		if ((written = write(1, buffer, size)) != size)
			goto fail;
	} while (1);

fail:
	munmap(buffer, len * BUFFER_SIZE);
}
