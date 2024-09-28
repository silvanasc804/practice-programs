#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define the size of a block of data (512 bytes)
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // While there's still data left to read from the memory card
    uint8_t buffer[BLOCK_SIZE];

    // Keep track of the number of JPEG files found
    int file_count = 0;

    // Pointer to the currently open output JPEG file
    FILE *img = NULL;

    // Filename for each JPEG
    char filename[8];

    // While there are still blocks left to read from the memory card
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card) == 512)
    {
        // Look for beginniing of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a new JPEG is found, close the previous file (if any)
            if (img != NULL)
            {
                fclose(img);
            }

            // Filenames ###.jpg starting at 000.jpg
            sprintf(filename, "%03i.jpg", file_count);
            // Open a new JPEG file
            img = fopen(filename, "w");
            file_count++;
        }

        // Write 512 bytes until a new JPEG is found
        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the memory card file
    fclose(card);

    return 0;
}
