#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define block 512
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("File Error");
        return 2;
    }
    uint8_t buffer[block] = {0};
    int jpgcounter = 0;
    char jpgname[8];
    FILE *tmpjpg = NULL;
    while (fread(&buffer, 1, block, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] - 0xe0 >=0 && buffer[3] - 0xe0 <=0x0f)
        {
            if (jpgcounter != 0)
                {
                    fclose(tmpjpg);
                }
                sprintf(jpgname, "%03i.jpg" ,jpgcounter);
                tmpjpg = fopen(jpgname, "a ");
                jpgcounter++;
        }
        if (tmpjpg !=NULL)
        {
            fwrite(&buffer, block, 1, tmpjpg);
        }
    }
    fclose(card);
    fclose(tmpjpg);
}

