#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char* argv[]) {
	FILE *input;
	struct stat file_details;
	char *file_contents;
	char *p1, *p2;
	int count1 = 1, count2 = 2;
	size_t write_file = 0;
	char *input_file = NULL, *output_file = NULL;

	if(argc != 5) {
		fprintf(stderr, "Usage: shuffle -i inputfile -o outputfile\n");
		exit(1);
	}

	if(strcmp(argv[1], "-i") != 0 && strcmp(argv[1], "-o") != 0) {
		fprintf(stderr, "Usage: shuffle -i inputfile -o outputfile\n");
		exit(1);
	}

	if(strcmp(argv[3], "-i") != 0 && strcmp(argv[3], "-o") != 0) {
		fprintf(stderr, "Usage: shuffle -i inputfile -o outputfile\n");
		exit(1);
	}

	for(int argv_count = 0; argv_count < 5; argv_count++) {
		if(strcmp(argv[argv_count], "-i") == 0) {
			input_file = argv[argv_count + 1];
		}
		if(strcmp(argv[argv_count], "-o") == 0) {
			output_file = argv[argv_count + 1];
		}
	}


	input = fopen(input_file, "r");
	if(input <= 0) {
		fprintf(stderr, "Error: Cannot open file %s\n", input_file);
		exit(1);
	}

	stat(input_file, &file_details);
	printf("The size of the file is %ld bytes\n", file_details.st_size);
	
	file_contents = malloc(file_details.st_size);
	if(file_contents != NULL) {
		printf("Memory has been assigned\n");
	}
	else {
		exit(1);
	}

	size_t read_byte = fread(file_contents, 1, file_details.st_size, input);
	if(read_byte > 0) {
		printf("Data has been transferred to the memory and is %zu bytes\n", read_byte);
	}

	p1 = file_contents;
	p2 = file_contents + file_details.st_size;

	printf("%c, %c, %c\n", *p2, *(p2-4), *(p2-1));

	FILE *output = fopen(output_file, "w");
	
	if (p1 == p2 - 1) {
		write_file = fwrite(p1, 1, 1, output);
	}
	p1 = p1 - 1;


	while(p1 < p2-1){
		while(*(p1 + count1) != '\n') {
			count1++;
		}
		
		p1 = p1 + count1;		
		write_file = fwrite(p1+1-count1, 1, count1, output);
		count1 = 1;


		if(p1 == p2-1){
			break;
		}


		while (*(p2 - count2) != '\n') {
			count2++;
		}
		p2 = p2 - count2 + 1;
			
		write_file = fwrite(p2, 1, count2 - 1, output);
		count2 = 2;
		printf("%c", *p2);
		
	}

	if(write_file > 0){
		printf("Write successful\n");
	}
	free(file_contents);
	fclose(output);
	return 0;
}
