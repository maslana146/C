#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
 
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;
 
typedef struct {
    WORD bfType;
    DWORD bfSize; //int
    WORD  bfReserved1; //unsigned short int
    WORD  bfReserved2;
    DWORD bfOffBits; //usigned int
} HEADER;
       
typedef struct {
    DWORD biSize;        
    LONG  biWidth;
    LONG  biHeight;          
    WORD  biPlanes;    
    WORD  biBitCount;      
    DWORD biCompression;      
    DWORD biSizeImage;          
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;        
    DWORD biClrImportant;  
} INFOHEADER;

int place(unsigned char data)
{   // get value of pixel and put in correct place in table
    if(data>=0&data<=15) return 0;
    else if(data>15&data<=31) return 1;
    else if(data>31&data<=47) return 2;
    else if(data>47&data<=63) return 3;
    else if(data>63&data<=79) return 4;
    else if(data>79&data<=95) return 5;
    else if(data>95&data<=111) return 6;
    else if(data>111&data<=127) return 7;
    else if(data>127&data<=143) return 8;
    else if(data>143&data<=159) return 9;
    else if(data>159&data<=175) return 10;
    else if(data>175&data<=191) return 11;
    else if(data>191&data<=207) return 12;
    else if(data>207&data<=223) return 13;
    else if(data>223&data<=239) return 14;
    else if(data>239&data<=255) return 15;
}

int main(int argc, char **argv){
    HEADER fh;
    INFOHEADER ih;
    FILE *fPointer;
    FILE *fWrite;
    
    fPointer = fopen(argv[1], "rb");
    fWrite = fopen(argv[2], "wb");
   
    if(fPointer == NULL)
    { 
        printf("'%s' does not exist.\n",argv[1]);
        return 1;
    }
    unsigned char header[54];

    // reading file header information
    fread (&(fh.bfType), 1, 2, fPointer);
    fread (&(fh.bfSize), 1, 4, fPointer);
    fread (&(fh.bfReserved1), 1, 2, fPointer);
    fread (&(fh.bfReserved2), 1, 2, fPointer);
    fread (&(fh.bfOffBits), 1, 4, fPointer);
    
    fwrite(&(fh.bfType), 1, 2, fWrite);
    fwrite(&(fh.bfSize), 1, 4, fWrite);
    fwrite(&(fh.bfReserved1), 1, 2, fWrite);
    fwrite(&(fh.bfReserved2), 1, 2, fWrite);
    fwrite(&(fh.bfOffBits), 1, 4, fWrite);

    char lo = fh.bfType & 0xFF; //changing Hex (of type uint16_t) to char, byte by byte
    char hi = fh.bfType >> 8;  //changing Hex (of type uint16_t) to char, byte by byte
 
    //printing header information
    printf("BITMAPFILEHEADER:\n");
    printf("    bfType:        0x%02X (%c%c) \n", fh.bfType, lo, hi); //print both Hex and ASCII
    printf("    bfSize:        %u\n", fh.bfSize);
    printf("    bfReserved1:   0x%01X\n", fh.bfReserved1); //print Hex
    printf("    bfReserved2:   0x%01X\n", fh.bfReserved2); //print Hex
    printf("    bfOffBits:     %u\n", fh.bfOffBits);
    //reading info header
    fread(&ih, sizeof(unsigned char), sizeof(INFOHEADER), fPointer);
    fwrite(&ih, sizeof(unsigned char), sizeof(INFOHEADER), fWrite);
    //printing info header
    printf("BITMAPINFOHEADER:\n");
    printf("    biSize:            %u\n", ih.biSize);
    printf("    biWidth:           %u\n", ih.biWidth);
    printf("    biHeight:          %u\n", ih.biHeight);
    printf("    biPlanes:          %u\n", ih.biPlanes);
    printf("    biBitCount:        %u\n", ih.biBitCount);
    printf("    biCompression:     %u\n", ih.biCompression);
    printf("    biSizeImage:       %u\n", ih.biSizeImage);
    printf("    biXPelsPerMeter:   %u\n", ih.biXPelsPerMeter);
    printf("    biYPelsPerMeter:   %u\n", ih.biYPelsPerMeter);
    printf("    biClrUsed:         %u\n", ih.biClrUsed);
    printf("    biClrImportant:    %u\n", ih.biClrImportant);
    printf("\n");

    

    int width, height, padding, bitcount, size, sumOfCollors,pad,move;
    unsigned char *data = 0;
    unsigned int red[16];
    unsigned int green[16];
    unsigned int blue[16];    
    unsigned int gray[16];
    unsigned char pixel[3];
 
     
    //reseting tables from garbage
    for(int i=0;i <16;++i)
    {
        red[i]=0;
        green[i]=0;
        blue[i]=0;
        gray[i]=0;
    }

    width = (ih.biWidth);
    height = (ih.biHeight);
    bitcount = (ih.biBitCount);
    size = ((width * bitcount + 31) / 32) * 4 * height;
    padding = width % 4;
    move = (width * 3 + 3) & ~3;
    
    if(bitcount != 24)
    {
        printf("Image is not 24-bit BMP.\n");
        fclose(fPointer);
        return 1;
    }

    for(int row = height - 1; row >= 0; row--)
    {
        for(int col = 0; col < width; col++)
        {   // read pixel value from fPointer
            fread(pixel, 3, 1, fPointer);
            // Calculating gray value 
            unsigned char gray = pixel[0] * 0.3 + pixel[1] * 0.5 + pixel[2] * 0.11;
            // seting gray into pixel
            memset(pixel, gray, sizeof(pixel));
            // writing value of pixel to fWrite
            fwrite(&pixel, 3, 1, fWrite);
        }
        // moving pointer
        fread(pixel, padding, 1, fPointer);
        fwrite(pixel, padding, 1, fWrite);
    }

    data = malloc(size);
    //An artifact of the File offset to Pixel array in the Bitmap file heade
    fseek(fPointer, fh.bfOffBits, SEEK_SET);
    fread(data, 1, size, fPointer);
    // reading of values pixel by pixel
    
    for(int row = height - 1; row >= 0; row--)
    {
        for(int col = 0; col < width; col++)
        {
            int p = (row * width + col) * 3 + row * padding;

            blue[place(data[p + 0])] +=1;
            green[place(data[p + 1])]+=1;
            red[place(data[p + 2])]+=1;
        }
    }   
    int Color = width * height;
    int k = 0;
    int q = 0;
    float percentage = 0.0;  
    
    // creating historgram RGB   
    printf("RED: \n");
    for(int i = 0; i < 240; i+=15)
    {
        percentage = (float)red[q] / Color;
        printf("%d-%d: %0.2f%%  \n", i+k, i+k+15, percentage*100);
        k++;
        q++;
    }
    k = 0;
    q = 0;

    printf("\n");
    printf("GREEN: \n");
    for(int i = 0; i < 240; i+=15)
    {
        percentage = (float)green[q] / Color;
        printf("%d-%d: %0.2f%%  \n", i+k, i+k+15, percentage*100);
        k++;
        q++;
    }
    k = 0;
    q = 0;

    printf("\n");
    printf("BLUE: \n");
    for(int i = 0; i < 240; i+=15)
    {
        percentage = (float)blue[q] / Color;
        printf("%d-%d: %0.2f%%  \n", i+k, i+k+15, percentage*100);
        k++;
        q++;
    }
    // creating gray scale
    for(int i=0;i<=15;i++)
    {
        sumOfCollors = ((red[i] * 61) + (green[i] * 174) + (blue[i] * 21)) / 256;
        gray[i] = sumOfCollors;
    }
    
    k = 0;
    q = 0;
    printf("\n");
    for(int i = 0; i < 240; i+=15)
    {
        percentage = (float)gray[q] / Color;
        printf("%d-%d: %0.2f%%  \n", i+k, i+k+15, percentage*100);
        k++;
        q++;
    }
    free(data);
    fclose(fPointer);
    fclose(fWrite);
    return 0;
}
