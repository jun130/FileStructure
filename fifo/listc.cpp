// listc.cpp

// program using C streams to read characters from a file 
// and write them to the terminal screen 
#include <stdio.h>
main( ) {
	char ch;
	FILE * file; // file descriptor
	char filename[20];
	printf("Enter the name of the file: ");	// Step 1
	gets(filename);					// Step 2
	file =fopen(filename, "r");			// Step 3
	while (fread(&ch, 1, 1, file) != 0)		// Step 4a
		fwrite(&ch, 1, 1, stdout);		// Step 4b
	fclose(file);					// Step 5
}
