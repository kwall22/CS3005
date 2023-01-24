#include "image_menu.h"
#include "Image.h"

int assignment1(std::istream& is, std::ostream& os) {
    return askQuestions3(is, os);
}

int assignment2( std::istream& is, std::ostream& os ) {
    Image Myimage;
    diagonalQuadPattern(is, os, Myimage);
    drawAsciiImage(is, os, Myimage);
    return 0;
}