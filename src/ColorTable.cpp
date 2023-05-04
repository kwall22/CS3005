#include "ColorTable.h"
#include <iostream>
#include <cmath>

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

void Color::setFromHSV(const double& hue, const double& saturation, const double& value) { 
    double red = mRed;
    double green = mGreen;
    double blue = mBlue;
    HSV_to_RGB(hue, saturation, value, red, green, blue);
}

void Color::getHSV(double& hue, double& saturation, double& value) const {
    double red = mRed;
    double green = mGreen;
    double blue = mBlue;
    RGB_to_HSV(red, green, blue, hue, saturation, value);
}

std::ostream& operator<<( std::ostream& os, const Color& color ){
    os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
    return os;
}

void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double& green, double& blue) {
    //Inputs and ranges:
   //0.0 <= hue <= 360.0
    // 0.0 <= saturation <= 1.0
   //* 0.0 <= value <= 1.0
   //*
   //* Outputs and ranges:
  // * 0.0 <= red <= 255.0
  // * 0.0 <= green <= 255.0
   //* 0.0 <= blue <= 255.0

  if(hue < 0.0 || hue > 360.0 || saturation < 0.0 || saturation > 1.0 || value < 0.0 || value > 1.0) {
    red = green = blue = 0.0;
    std::cerr << "HSV_to_RGB() input parameters out of range." << std::endl
              << " hue: " << hue  << std::endl
              << " saturation: " << saturation << std::endl
              << " value: " << value << std::endl;
    return;
  }

  // chroma selects the strength of the "primary" color of the current area of the wheel
  double chroma = value * saturation;
  // hue2 selects which 60-degree wedge of the color wheel we are in
  double hue2 = hue / 60.0;
  // x selects the strength of the "secondary" color of the current area of the wheel
  double x = chroma * ( 1 - std::abs( std::fmod( hue2, 2 ) - 1 ) );
  if( hue2 >= 0 && hue2 < 1 ) {
    red = chroma;
    green = x;
    blue = 0.0;
  } else if( hue2 >= 1 && hue2 < 2 ) {
    red = x;
    green = chroma;
    blue = 0.0;
  } else if( hue2 >= 2 && hue2 < 3 ) {
    red = 0.0;
    green = chroma;
    blue = x;
  } else if( hue2 >= 3 && hue2 < 4 ) {
    red = 0.0;
    green = x;
    blue = chroma;
  } else if( hue2 >= 4 && hue2 < 5 ) {
    red = x;
    green = 0.0;
    blue = chroma;
  } else if( hue2 >= 5 && hue2 <= 6 ) {
    red = chroma;
    green = 0.0;
    blue = x;
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  // m scales all color channels to obtain the overall brightness.
  double m = value - chroma;
  red = 255.0*( red + m );
  green = 255.0*( green + m );
  blue = 255.0*( blue + m );
}

void RGB_to_HSV(const double& red0, const double& green0, const double& blue0, double& hue, double& saturation, double& value) {
    /* Red, Green, Blue to Convert Hue, Saturation, Value
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
   *
   * Inputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   *
   * Outputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   */
  if(red0 < 0.0 || red0 > 255.0 || green0 < 0.0 || green0 > 255.0 || blue0 < 0.0 || blue0 > 255.0) {
    hue = saturation = value = 0.0;
    std::cerr << "RGB_to_HSV() input parameters out of range." << std::endl
              << " red: " << red0  << std::endl
              << " green: " << green0 << std::endl
              << " blue: " << blue0 << std::endl;
    return;
  }

  double red   = red0 / 255.0;
  double green = green0 / 255.0;
  double blue  = blue0 / 255.0;

  // x_max helps identify the primary hue
  double x_max = red;
  if(green > x_max) { x_max = green; }
  if(blue > x_max) { x_max = blue; }
  value = x_max;

  double x_min = red;
  if(green < x_min) { x_min = green; }
  if(blue < x_min) { x_min = blue; }

  double chroma = x_max - x_min;

  if(chroma == 0) {
    hue = 0;
  } else if(value == red) {
    hue = 60.0 * (0 + (green - blue)/chroma);
  } else if(value == green) {
    hue = 60.0 * (2 + (blue - red)/chroma);
  } else if(value == blue) {
    hue = 60.0 * (4 + (red - green)/chroma);
  } else {
    hue = -720.0;
  }
  if(hue < 0.0) {
    hue += 360.0;
  }

  if(value == 0.0) {
    saturation = 0.0;
  } else {
    saturation = chroma/value;
  }

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

void ColorTable::insertHueSaturationValueGradient(const Color &color1, const Color &color2, const int &position1, const int &position2) {
    double hue1;
    double saturation1;
    double value1;
    double red1 = color1.getRed();
    double green1 = color1.getGreen();
    double blue1 = color1.getBlue();
    //color1.getHSV(hue1, saturation1, value1);
    RGB_to_HSV(red1, green1, blue1, hue1, saturation1, value1);
    double hue2;
    double saturation2;
    double value2;
    double red2 = color2.getRed();
    double green2 = color2.getGreen();
    double blue2 = color2.getBlue();
    //color2.getHSV(hue2, saturation2, value2);
    RGB_to_HSV(red2, green2, blue2, hue2, saturation2, value2);


    double hue_slope = gradientSlope(hue1, hue2, position1, position2);
    double saturation_slope = gradientSlope(saturation1, saturation2, position1, position2);
    double value_slope = gradientSlope(value1, value2, position1, position2);
    
    if (position1 < position2 && position1 >= 0 && position1 <= int(mColors.size()-1) && position2 >= 0 && position2 <= int(mColors.size() -1)){
        for (int position = position1; position <= position2 ; position++){
            //double red_g = (color1.getRed() + position) * red_step;
            //double green_g = (color1.getGreen() + position) * green_step;
            //double blue_g = (color1.getBlue() + position) * blue_step;
            double hue_g = gradientValue(hue1, position1, hue_slope, position);
            double saturation_g = gradientValue(saturation1, position1, saturation_slope, position);
            double value_g = gradientValue(value1, position1, value_slope, position);
            mColors[position].setFromHSV(hue_g, saturation_g, value_g);
        }
    }
}
