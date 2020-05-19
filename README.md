# year-1-spell-checker-coursework

Simple spell checker tool written in C for first year uni module "Programming Fundamentals"

## How to use

To use the spell check tool extract the zip file to a known location and using the Developer Command Prompt for Microsoft Visual Studio 2015 locate the files location and enter:

nmake spell

This will compile the program and make it ready to use. To spell check a document use the following format where [input] is the name of your input text file and [output] is the name of the text file to be created:

spell -i [input].txt -o [output].txt 

The tool will output your spelling mistakes into a text file with the corresponding line numbers. 
