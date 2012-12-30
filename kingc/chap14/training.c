#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROG "spaceloop"
#define MAXLINE 1000
#define SPACE ' '
#define TAB '\n'



static void spaceloop(FILE *f, int pad_char, int count); 
static void pad(int pad_char, int count); 
static void usage(FILE *f); 

int main(int argc, char *argv[])
{
	int pad_char = SPACE;
	int count = 4; 
	
	int c = 0; 
	int errflag = 0; 
	extern char *optarg; 
	extern int optopt, opterr; 
	
	char *infile; 
	FILE *f; 
	int i = 0;
	int file = 0;

	///////////////	
	//getoptions//
	while ((c = getopt(argc, argv, "f:h")) != -1) {
		switch(c) {
			case 'h':
				usage(stdout); 
				exit(0); 
				break; 
			case 'f': 
				infile = optarg; //strange enough, no strcpy?
				file = 1;
				break; 
			case '?': 
				fprintf(stderr, "Wrong option usage\n"); 
				errflag++; 
			default:
				break;
		}
	}

	
	if (errflag) {
		usage(stderr); 
		exit(EXIT_FAILURE); 
	}
	
	argc -= optind; 
	argv += optind; 

	///////////////	
	///////////////	

	//stdin if no -f FILE
	if (file) {
		if ((f = fopen(infile, "r")) == NULL) {
			fprintf(stderr, "%s Error opening %s.\n",
				PROG, infile);
		}
		else {
			spaceloop(f, pad_char, count);
		}
	}
	else {
		spaceloop(stdin, pad_char, count);
	}

	return 0; 
}

////////////////////////////////////////////////////////////////////////////////
static void spaceloop(FILE *f, int pad_char, int count)
{
	char s[MAXLINE]; 

	while ((fgets(s, sizeof(s), f)) != NULL ) {
				pad(pad_char, count); 
				printf("%s", s); 
	}
}

static void pad(int pad_char, int count)
{
	while (count-- > 0) {
		putchar(pad_char); 
	}
}


////////////////////////////////////////////////////////////////////////////////
static void usage(FILE *f)
{
	fprintf(f, "\nUsage: %s [-h] [-f FILE]\n", PROG); 
}
