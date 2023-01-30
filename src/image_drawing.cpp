#include "image_menu.h"
#include "Image.h"
#include "PPM.h"


void diagonalQuadPattern( std::istream& is, std::ostream& os, Image& image ) {
    (void) is;
    int height = getInteger(is, os, "Image height? ");
    int width = getInteger(is, os, "Image width? ");
    image.setHeight(height);
    image.setWidth(width);

    int i = height/2;
    int i2 = 0;
    //red channel 0
    for (;i < height; i++){
        for (int i2 = 0; i2 < width; i2++){
            image.setChannel(i, i2, 0, 255);
        } 
    }
    //green channel 1
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
           image.setChannel(i, i2, 1, ( 2*i + 2*i2 ) % 256 ); 
        }
    }
    //blue channel 2 
    for(i = 0; i < height; i++){
        i2 = width/2;
        for (;i2 < width; i2++){
            image.setChannel(i, i2, 2, 255);
        }
    }
}

void stripedDiagonalPattern( std::istream& is, std::ostream& os, PPM& p ){
    int height = getInteger(is, os, "Image height? ");
    int width = getInteger(is, os, "Image width? ");
    p.setHeight(height);
    p.setWidth(width);
    int val = (height + width) / 3;
    if (val >= 255){
        p.setMaxColorValue(255);
    }
    else {
    p.setMaxColorValue((height + width) / 3);
    }
//red 
    int i = height/2;
    int i2 = 0;
    for (;i < height; i++){
        for (;i2 % 3 != 0; i2++){
            p.setChannel(i, i2, 0, p.getMaxColorValue());
        }
    }
//green
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
            p.setChannel(i, i2, 1, (i + width - i2 -1) % (p.getMaxColorValue() + 1));
        }
    }
//blue
    for (i = 0; i < height; i++){
        for (i2 = 0; i2 < width; i2++){
            if (i2 >= i){
                p.setChannel(i, i2, 2, p.getMaxColorValue());
            }
        }
    }
}
