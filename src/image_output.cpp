#include "image_menu.h"
#include "Image.h"
void drawAsciiImage( std::istream& is, std::ostream& os, const Image& image ) {
    (void) is;
    int row = image.getHeight();
    int column = image.getWidth();
    for (int i = 0; i < row; i++){
        for (int i2 = 0; i < column; i2++){
            int red_val = image.getChannel(i, i2, 0);
            int green_val = image.getChannel(i, i2, 1);
            int blue_val = image.getChannel(i, i2, 2);
            int pix_sum = red_val + green_val + blue_val;
            double pix_strength = double(pix_sum) / 765.0;
            if (pix_strength >= 1.0){
                os << "@";
            }
            else if (pix_strength >= 0.9){
                os << "#";
            }
            else if (pix_strength >= 0.8){
                os << "%";
            }
            else if (pix_strength >= 0.7){
                os << "*";
            }
            else if (pix_strength >= 0.6){
                os << "|";
            }
            else if (pix_strength >= 0.5){
                os << "+";
            }
            else if (pix_strength >= 0.4){
                os << ";";
            }
            else if (pix_strength >= 0.3){
                os << "~";
            }
            else if (pix_strength >= 0.2){
                os << "-";
            }
            else if (pix_strength >= 0.1){
                os << ".";
            }
            else if (pix_strength >= 0.0){
                os << " ";
            }
            }
        os << "/n";
    }

}