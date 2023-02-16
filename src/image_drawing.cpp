#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"

void setSize( ActionData& action_data ){
    int height = getInteger(action_data, "Height? ");
    int width = getInteger(action_data, "Width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ){
    int val = getInteger(action_data, "Max color value? ");
    action_data.getInputImage1().setMaxColorValue(val);
}

void setChannel( ActionData& action_data ){
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int chan = getInteger(action_data, "Channel? ");
    int val = getInteger(action_data, "Value? ");
    action_data.getInputImage1().setChannel(row, col, chan, val);
}

void setPixel( ActionData& action_data ){
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getInputImage1().setPixel(row, col, red, green, blue);
}

void clearAll( ActionData& action_data ){
    int height = action_data.getInputImage1().getHeight();
    int width = action_data.getInputImage1().getWidth();

    for (int i = 0; i < height; i++){
        for (int i2 = 0; i2 < width; i2++){
            action_data.getInputImage1().setPixel(i, i2, 0, 0, 0);
        } 
    }
}

void diagonalQuadPattern( ActionData& action_data) {
    (void) action_data.getIS();
    int height = getInteger(action_data, "Image height? ");
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(255);

    int i = height/2;
    int i2 = 0;
    //red channel 0
    for (;i < height; i++){
        for (int i2 = 0; i2 < width; i2++){
            action_data.getInputImage1().setChannel(i, i2, 0, 255);
        } 
    }
    //green channel 1
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
           action_data.getInputImage1().setChannel(i, i2, 1, ( 2*i + 2*i2 ) % 256 ); 
        }
    }
    //blue channel 2 
    for(i = 0; i < height; i++){
        i2 = width/2;
        for (;i2 < width; i2++){
            action_data.getInputImage1().setChannel(i, i2, 2, 255);
        }
    }
}

void stripedDiagonalPattern( ActionData& action_data ){
    int height = getInteger(action_data, "Image height? ");
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    int val = (height + width) / 3;
    if (val >= 255){
        action_data.getInputImage1().setMaxColorValue(255);
    }
    else {
    action_data.getInputImage1().setMaxColorValue((height + width) / 3);
    }
//red 
    int i = height/2;
    int i2;
    for (;i < height; i++){
        if (i % 3 != 0) {
            for (i2 = 0; i2 < width; i2++){
                action_data.getInputImage1().setChannel(i, i2, 0, action_data.getInputImage1().getMaxColorValue());
            }
        }
    }
//green
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
            action_data.getInputImage1().setChannel(i, i2, 1, (i + width - i2 -1) % (action_data.getInputImage1().getMaxColorValue() + 1));
        }
    }
//blue
    for (i = 0; i < height; i++){
        for (i2 = 0; i2 < width; i2++){
            if (i2 >= i){
                action_data.getInputImage1().setChannel(i, i2, 2, action_data.getInputImage1().getMaxColorValue());
            }
        }
    }
}

void flagRomaniaPattern( ActionData& action_data ){
    int height = getInteger(action_data, "Image height? ");
    action_data.getInputImage1().setHeight(height);
    int width = (height * 3) / 2;
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(255);
    //int col_1 = p.getWidth() / 3
    //int col_2 = p.getWidth() / 3 + col_1
    //int col_3 = p.getWidth() / 3 + col_1 + col_2

    //blue section 
    int i;
    int i2 = 0;
    for (i = 0; i < height; i++){
        for (i2 = 0; i2 < width / 3; i2++ ){
                action_data.getInputImage1().setChannel(i, i2, 0, 0);
                action_data.getInputImage1().setChannel(i, i2, 1, 43);
                action_data.getInputImage1().setChannel(i, i2, 2, 127);
        }
    }
    //yellow section
    for (i = 0; i < height; i++){
        for (i2 = width / 3; i2 < (width / 3) * 2 ; i2++ ){
                action_data.getInputImage1().setChannel(i, i2, 0, 252);
                action_data.getInputImage1().setChannel(i, i2, 1, 209);
                action_data.getInputImage1().setChannel(i, i2, 2, 22);
        }
    }
    //red section
    for (i = 0; i < height; i++){
        for (i2 = (width / 3) * 2; i2 < width ; i2++ ){
                action_data.getInputImage1().setChannel(i, i2, 0, 206);
                action_data.getInputImage1().setChannel(i, i2, 1, 17);
                action_data.getInputImage1().setChannel(i, i2, 2, 38);
        }
    }
}
