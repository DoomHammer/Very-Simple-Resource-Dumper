#include "dumpedHeader.h"
#include <stdio.h>

int main (int argc, char const *argv[])
{
    unsigned long long img_size = 0;
    unsigned long long txt_size = 0;
    
    const char* img = getResource("/imgs/Pen.png", &img_size);
    const char* txt = getResource("/Text.txt", &txt_size);
    
    FILE* fimg = fopen("dumpedImage.png", "wb");
    fwrite(img, 1, img_size, fimg);
    fclose(fimg);
    
    FILE* ftxt = fopen("dumpedText.txt", "wb");
    fwrite(txt, 1, txt_size, ftxt);
    fclose(ftxt);
    
    return 0;
}
