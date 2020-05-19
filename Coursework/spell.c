// Christopher Johnson - 40275286
// Date of Last Modification - 26/02/2017
// Program - Spell Checker
 
// Including Standards
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
// Declare Global Variables
char *inputFile;
char *outputFile;
 
// This section is needed to take command line arguments of -i and -o
void cmdNames(int argc, char **numberOfArgs)
{
    for(int i = 0; i < argc; i++)
    {
        // This stores the text following "-i" so that the right file can be opened
        if(strcmp(numberOfArgs[i], "-i") == 0)
        {
            inputFile = numberOfArgs[i + 1];
        }
        // This stores the text following "-o" so that the right output file can be produced
        else if(strcmp(numberOfArgs[i], "-o") == 0)
        {  
            outputFile = numberOfArgs[i + 1];
        }
		// If no filenames are specified retrieve via stdin
		// NOTE - Currently not working but does not affect program given files are specified
		else if(numberOfArgs[i] == NULL)
		{
			char inFile[50];
			char outFile[50];
			printf("Please enter your input file name including file extension:");
			fgets(inFile, 50, stdin);
			inputFile = inFile;
			printf("Please enter your output file name including file extension:");
			fgets(outFile, 50, stdin);
			outputFile = outFile;
		}
    }  
}
 
int main (int argc, char **argv)
{
    cmdNames(argc, argv);
   
   // Declare files
    FILE *dictionary;
    FILE *input;
    FILE *output;
   
    // Open the various files
    dictionary = fopen("dictionary.txt", "r");
    input = fopen(inputFile, "r");
    output = fopen(outputFile, "w");
 
 
    // Set the count for dictionary file
    int totalLines = 0;
 
    // If the dictionary file is erroneous, print an error
    if(dictionary == NULL) {
        printf("ERROR - DICTIONARY FILE NOT FOUND\n");
        return 0;
    } else {
        // If it's okay, add 1 to total lines for later
        totalLines++;
    }
 
    //  Now count the lines
    int chr=0;
    while ((chr = fgetc(dictionary)) != EOF) {
        if (chr == '\n') {
            totalLines++;
        }
    }
	
	// The sizes of array variables in C must be known at compile time
    char *data;
    char *word;
	// Allocating memory - this took so much trial and error
    data = malloc(totalLines * 25);
    word = malloc(totalLines * 25);
 
    int line = 1;
 
    while (fgets(data, totalLines, input) != NULL)
    {
        char delim[9] = {' ', ' ', '\n', '?', '!', ',', '.', ';', ':'};
       
        char *filedata;
        // Split the data into words by the delims stated
        filedata = strtok (data, delim);
       
        while (filedata != NULL)
        {
           
            int a = 0;
           
            while (filedata[a] != '\0')
            {
				// If the characters are uppercase convert them into lowercase
                if (filedata[a] >= 'A' && filedata[a] <= 'Z')
                {
                    filedata[a] = filedata[a] + 32;
                }
                a++;
            }
       
        int flag = 0;
       
        while (fgets(word, totalLines, dictionary) != NULL)
        {
            flag = 0;
           
            int b = 0;
           
            while (word[b] != '\0')
            {
				// Convert all the dictionary characters to lowercase
                if (word[b] >= 'A' && word[b] <= 'Z')
                {
                    word[b] = word[b] + 32;
                }
                b++;
            }
			// Remove \n characters
            char * pos;
            if ((pos=strchr(word, '\n')) != NULL)
                    *pos = '\0';
            int check = strcmp(word, filedata);
                if (check == 0)
                {
                    flag = 1;
                    break;
                }
            }
            // If the word is spelt incorrectly print it along with line number       
            if (flag == 0)
            {
                fprintf(output, "line number %d\n", line);
                fprintf(output, "%s\n", filedata);
            }
           
            rewind(dictionary);
            filedata = strtok(NULL, delim);
        }
        line++;
    }
   
    fclose(dictionary);
    fclose(input);
    fclose(output);
    return 0;
}