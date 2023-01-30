#ifndef PPM_H
#define PPM_H
#include "Image.h"
#include <iostream>


class PPM: public Image{
public:
    PPM();
    PPM(const int& height, const int& width);

    int getMaxColorValue( ) const;
    bool valueValid( const int& value ) const;

    void setMaxColorValue( const int& max_color_value );
    void setChannel( const int& row, const int& column, const int& channel, const int& value );
    void setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue );
    void writeStream(std::ostream& os) const;

private:
    //int mHeight;
    //int mWidth;
    int mMaxColorValue;
};
#endif