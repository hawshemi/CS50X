#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    FILE *img = NULL;

    BYTE buffer[512];
    char filename[8];
    int counter = 0;
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // checks if start of image in buffer
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if start of img and first image i.e. counter ==0
            // then begins writing a new image
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                counter += 1;
            }
            // if start of img but not first image then
            // closes the image and begins writing new image
            else if (counter > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                counter += 1;
            }
        }
        // if not start of new img
        // then it keeps on writing the image
        else if (counter > 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }

    }

    // Close file
    fclose(file);
    fclose(img);
}
