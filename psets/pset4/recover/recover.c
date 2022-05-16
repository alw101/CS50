#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Check to see if correct number of args
    if (argc != 2) 
    {
        printf("Usage: ./recover image\n"); 
        return 1;
    }

    //Initialize variables
    long size;
    int bytesRead;
    int imageNum = 0;
    char filename[50];
    FILE *img;
    typedef uint8_t BYTE;
    BYTE buffer[512];

    //Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
    {
        printf("Unable to open file\n"); 
        return 1;
    }

    //Get file size
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    
    //Repeat for the size of the file
    do
    {
    
        //Store current section in buffer
        bytesRead = fread(buffer, 512, 1, file);
        
        //Check to see if at end of card
        if (bytesRead != 1)
        {
            break;
        }
        
        //Check to see if start of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            sprintf(filename, "%03i.jpg", imageNum);
            
            if (imageNum != 0)
            {
                fclose(img);
            }
            
            img = fopen(filename, "w");
            imageNum++;
        }
        
        //Write contents to file
        if (imageNum != 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    
    }
    while (bytesRead == 1);

    //Close Files
    fclose(img);
    fclose(file);
    

}
