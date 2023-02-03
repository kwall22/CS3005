#include "image_menu.h"
#include "Image.h"
#include "PPM.h"

int assignment1(std::istream& is, std::ostream& os) {
    return askQuestions3(is, os);
}

int assignment2( std::istream& is, std::ostream& os ) {
    Image Myimage;
    diagonalQuadPattern(is, os, Myimage);
    drawAsciiImage(is, os, Myimage);
    return 0;
}

int assignment3( std::istream& is, std::ostream& os ) {
    PPM MyPPM;
    stripedDiagonalPattern(is, os, MyPPM);
    writeUserImage(is, os, MyPPM);
    return 0;
}

int flag_romania( std::istream& is, std::ostream& os ) {
    PPM romania;
    flagRomaniaPattern(is, os, romania);
    writeUserImage(is, os, romania);
    return 0;
}