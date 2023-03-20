#include "ColorTable.h"
#include <iostream>

Color::Color()
    : mRed(0), mGreen(0), mBlue(0){
}

Color::Color(const int &red, const int &green, const int &blue) :
    mRed(red), mGreen(green), mBlue(blue){
}

int Color::getRed() const {
    return mRed;
}

int Color::getGreen() const {
    return mGreen;
}

int Color::getBlue() const {
    return mBlue;
}

int Color::getChannel(const int &channel) const {
    if (channel == 0){
        return mRed;
    }
    else if (channel == 1){
        return mGreen;
    }
    else if (channel == 2){
        return mBlue;
    }
    return -1;
}

void Color::setRed(const int &value) {
    if (value >=0){
        mRed = value;
    }
}

void Color::setGreen(const int &value) {
    if (value >=0){
        mGreen = value;
    }
}

void Color::setBlue(const int &value) {
    if (value >=0){
        mBlue = value;
    }
}

void Color::setChannel(const int &channel, const int &value) {
    if (channel >= 0 && channel <= 3){
        if (value >= 0){
            if (channel == 0){
                setRed(value);
            }
            else if (channel == 1){
                setGreen(value);
            }
            else if (channel == 2){
                setBlue(value);
            }
        }
    }
}

void Color::invert(const int &max_color_value) {
    if (mRed <= max_color_value && mGreen <= max_color_value && mBlue <= max_color_value){
        mRed = max_color_value - mRed;
        mGreen = max_color_value - mGreen;
        mBlue = max_color_value - mBlue;
    }
    //if (mGreen <= max_color_value){
    //    mGreen = max_color_value - mGreen; }
    //if (mBlue <= max_color_value){
    //    mBlue = max_color_value - mBlue; }
}

bool Color::operator==(const Color &rhs) const {
    if (mRed == rhs.mRed && mGreen == rhs.mGreen && mBlue == rhs.mBlue){
        return true;
    }
    return false;
}

std::ostream& operator<<( std::ostream& os, const Color& color ){
    os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
    return os;
}

ColorTable::ColorTable(const int &num_color) {
    mColors.resize(num_color);
}

int ColorTable::getNumberOfColors() const {
    return mColors.size();
}

void ColorTable::setNumberOfColors(const int &num_color) {
    mColors.resize(num_color);
}

const Color& ColorTable::operator[](const int& i) const {
    if (i > (getNumberOfColors() -1)  || i < 0){
        static Color ec( -1, -1, -1 );
        static Color c( -1, -1, -1 );
        c = ec;
        return c;
    }
    return mColors[i];
}

Color& ColorTable::operator[](const int& i) {
    if (i > (getNumberOfColors() -1) || i < 0){
        static Color ec( -1, -1, -1 );
        static Color c( -1, -1, -1 );
        c = ec;
        return c;
    }
    return mColors[i];
}

void ColorTable::setRandomColor(const int &max_color_value, const int &position) {
    if (position >= 0 && position <= getNumberOfColors() && max_color_value >= 0){
        if (rand() % (max_color_value + 1) >= 0 && rand() % (max_color_value + 1) <= max_color_value){
        mColors[position].setRed(rand() % (max_color_value + 1));
        mColors[position].setGreen(rand() % (max_color_value + 1));
        mColors[position].setBlue(rand() % (max_color_value + 1));
        }
    }
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
    double rise = y2 - y1;
    double run = x2 - x1;
    return (rise/run);
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
    int x_diff = x - x1;
    double fy = slope * x_diff;
    double y = fy + y1;
    return y;
}

void ColorTable::insertGradient(const Color &color1, const Color &color2, const int &position1, const int &position2) {
    //double red_step = (color2.getRed() - color1.getRed()) / (position2 - 1);
    //double green_step = (color2.getGreen() - color1.getGreen()) / (position2 - 1);
    //double blue_step = (color2.getBlue() - color1.getBlue()) / (position2 - 1);
    double red_slope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
    double green_slope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
    double blue_slope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);
    if (position1 < position2 && position1 >= 0 && position1 <= int(mColors.size()-1) && position2 >= 0 && position2 <= int(mColors.size() -1)){
        for (int position = position1; position <= position2 ; position++){
            //double red_g = (color1.getRed() + position) * red_step;
            //double green_g = (color1.getGreen() + position) * green_step;
            //double blue_g = (color1.getBlue() + position) * blue_step;
            double red_g = gradientValue(color1.getRed(), position1, red_slope, position);
            double green_g = gradientValue(color1.getGreen(), position1, green_slope, position);
            double blue_g = gradientValue(color1.getBlue(), position1, blue_slope, position);
            mColors[position].setRed(red_g);
            mColors[position].setGreen(green_g);
            mColors[position].setBlue(blue_g);
        }
    }
}

int ColorTable::getMaxChannelValue() const {
    int max_channel_value = 0;
    for(int i = 0; i < getNumberOfColors(); i++){
        if (mColors[i].getRed() > max_channel_value){
            max_channel_value = mColors[i].getRed();
        }
        if (mColors[i].getGreen() > max_channel_value){
            max_channel_value = mColors[i].getGreen();
        }
        if (mColors[i].getBlue() > max_channel_value){
            max_channel_value = mColors[i].getBlue();
        }
    }
    return max_channel_value;
}
