#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
 
//check for valid command line argument. Only 1 allowed
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
//open the input file
    char *input_name = argv[1];
    FILE *inputPointer = fopen(input_name, "r"); //open in read
 
    if (inputPointer == NULL) //if unable to open file, return error
    {
        printf("Error: Unable to open %s", input_name);
        return 1;
    }
//set variables
    BYTE buffer[512]; //define byte size
    int imageCounter = 0;
    FILE *outputPointer = NULL;
    char imagename[8]; //file name is 8 characters e.g. 001.jpg plus the \0 character
 
    while (fread(&buffer, 512, 1, inputPointer) == 1) //read the first 3 pointers of the jpeg file to determine if it is a jpeg
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0) // to determine the start of a new jpeg image. these are set values
        {
            if (!(imageCounter == 0))
            {
                fclose(outputPointer);
            }
         
            sprintf(input_name, "%03i.jpg", imageCounter); //output file name with image counter number in the file name
            outputPointer = fopen(input_name, "w");
            imageCounter++; //add 1 to image counter
        }
     
        if (!(imageCounter == 0))
        {
            fwrite(&buffer, 512, 1, outputPointer);
        }
    }
    if (outputPointer == NULL) //close files when no longer being used
    {
        fclose(outputPointer);
    }
 
    if (inputPointer == NULL)
    {
        fclose(inputPointer);
    }
 
    return 0;
}
