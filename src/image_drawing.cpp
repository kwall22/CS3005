#include "image_menu.h"
#include "Image.h"

void diagonalQuadPattern( std::istream& is, std::ostream& os, Image& image ) {
    (void) is;
    int height = getInteger(is, os, "Image height? ");
    int width = getInteger(is, os, "Image width? ");
    image.setHeight(height);
    image.setWidth(width);

    int i = height/2;
    int i2 = 0;

    for (;i < height; i++){
        for (int i2 = 0; i2 < width; i2++){
            image.setChannel(i, i2, 0, 255);
        } 
    } 
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
           image.setChannel(i, i2, 1, ( 2*i + 2*i2 ) % 256 ); 
        }
    }

    for(i = 0; i < height; i++){
        i2 = width/2;
        for (;i2 < width; i2++){
            image.setChannel(i, i2, 2, 255);
        }
    }
}





    // for (int i = 0; i2 > width/2; i2++) {
    //    image.setChannel(i, i2, 2, 255); 
    // }     
    //     if (i2 < width/2){
    //             image.setChannel(i, i2, 2, 0);
    //         }
    //         else{
    //             image.setChannel(i, i2, 2, 255);
    //         }
    //         image.setChannel(i, i2, 1, ( 2*i + 2*i2 ) % 256 );
    //     }
    // }}