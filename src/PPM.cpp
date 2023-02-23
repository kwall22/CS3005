#include "PPM.h"

PPM::PPM()
    : Image(), mMaxColorValue(1){
}

PPM::PPM(const int &height, const int &width)
    : Image(height, width), mMaxColorValue(1){
}

int PPM::getMaxColorValue() const {
    return mMaxColorValue;
}

bool PPM::valueValid(const int &value) const {
    if (value >= 0 && value <= mMaxColorValue)
        return true;
    return false;
}

bool PPM::operator==(const PPM &rhs) const{
    if (mHeight * mWidth == rhs.mHeight * rhs.mWidth){
        return true;
    }
    return false;
}

bool PPM::operator!=(const PPM &rhs) const{
    if (mHeight * mWidth != rhs.mHeight * rhs.mWidth){
        return true;
    }
    return false;
}

bool PPM::operator<(const PPM &rhs) const{
    if (mHeight * mWidth < rhs.mHeight * rhs.mWidth){
        return true;
    }
    return false;
}

bool PPM::operator<=(const PPM &rhs) const{
    if (mHeight * mWidth <= rhs.mHeight * rhs.mWidth){
        return true;
    }
    return false;
}

bool PPM::operator>(const PPM &rhs) const{
    if (mHeight * mWidth > rhs.mHeight * rhs.mWidth){
        return true;
    }
    return false;
}

bool PPM::operator>=(const PPM &rhs) const{
    if (mHeight * mWidth >= rhs.mHeight * rhs.mWidth){
        return true;
    }
    return false;
}

PPM &PPM::operator+=(const PPM &rhs){
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int rhs_val = rhs.getChannel(row, col, chan);
                int add_val = lhs_val + rhs_val;
                if (add_val > getMaxColorValue()){
                    setChannel(row, col, chan, getMaxColorValue());
                }
                else if (add_val < 0){
                    setChannel(row, col, chan, 0);
                }
                else {
                    setChannel(row, col, chan, add_val);
                }
            }
        }
    }
    return *this;
}

PPM &PPM::operator-=(const PPM &rhs) {
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int rhs_val = rhs.getChannel(row, col, chan);
                int minus_val = lhs_val - rhs_val;
                if (minus_val < 0){
                    setChannel(row, col, chan, 0);
                }
                else {
                    setChannel(row, col, chan, minus_val);
                }
            }
        }
    }
    return *this;
}

PPM &PPM::operator*=(const double& rhs) {
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int times_val = lhs_val * rhs;
                if (times_val < 0){
                    setChannel(row, col, chan, 0);
                }
                else if (times_val > getMaxColorValue()){
                    setChannel(row, col, chan, getMaxColorValue());
                }
                else {
                    setChannel(row, col, chan, times_val);
                }
            }
        }
    }
    return *this;
}

PPM &PPM::operator/=(const double &rhs) {
    for (int row = 0; row < mHeight; row++){
        for(int col = 0; col < mWidth; col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                double div_val = lhs_val / rhs;
                if (div_val < 0){
                    setChannel(row, col, chan, 0);
                }
                else if (div_val > getMaxColorValue()){
                    setChannel(row, col, chan, getMaxColorValue());
                }
                else {
                    setChannel(row, col, chan, div_val);
                }
            }
        }
    }
    return *this;
}

PPM PPM::operator+(const PPM &rhs) const {
    PPM NewPPM(getHeight(), getWidth());
    NewPPM.setMaxColorValue(getMaxColorValue());
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int rhs_val = rhs.getChannel(row, col, chan);
                int add_val = lhs_val + rhs_val;
                if (add_val > getMaxColorValue()){
                    NewPPM.setChannel(row, col, chan, getMaxColorValue());
                }
                else if (add_val < 0){
                    NewPPM.setChannel(row, col, chan, 0);
                }
                else {
                    NewPPM.setChannel(row, col, chan, add_val);
                }
            }
        }
    }
    return NewPPM;
}

PPM PPM::operator-(const PPM &rhs) const{
    PPM NewPPM(getHeight(), getWidth());
    NewPPM.setMaxColorValue(getMaxColorValue());
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int rhs_val = rhs.getChannel(row, col, chan);
                int minus_val = lhs_val - rhs_val;
                if (minus_val < 0){
                    NewPPM.setChannel(row, col, chan, 0);
                }
                else {
                    NewPPM.setChannel(row, col, chan, minus_val);
                }
            }
        }
    }
    return NewPPM;
}

PPM PPM::operator*(const double &rhs) const {
    PPM NewPPM(getHeight(), getWidth());
    NewPPM.setMaxColorValue(getMaxColorValue());
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int times_val = lhs_val * rhs;
                if (times_val > getMaxColorValue()){
                    NewPPM.setChannel(row, col, chan, getMaxColorValue());
                }
                else if (times_val < 0){
                    NewPPM.setChannel(row, col, chan, 0);
                }
                else {
                    NewPPM.setChannel(row, col, chan, times_val);
                }
            }
        }
    }
    return NewPPM;
}

PPM PPM::operator/(const double &rhs) const {
    PPM NewPPM(getHeight(), getWidth());
    NewPPM.setMaxColorValue(getMaxColorValue());
    for (int row = 0; row < getHeight(); row++){
        for(int col = 0; col < getWidth(); col++){
            for(int chan = 0; chan < 3; chan++){
                int lhs_val = getChannel(row, col, chan);
                int div_val = lhs_val / rhs;
                if (div_val > getMaxColorValue()){
                    NewPPM.setChannel(row, col, chan, getMaxColorValue());
                }
                else if (div_val < 0){
                    NewPPM.setChannel(row, col, chan, 0);
                }
                else {
                    NewPPM.setChannel(row, col, chan, div_val);
                }
            }
        }
    }
    return NewPPM;
}

void PPM::setMaxColorValue(const int &max_color_value) {
    if (max_color_value >= 1 && max_color_value <= 255){
        mMaxColorValue = max_color_value;
    }
}

void PPM::setChannel(const int &row, const int &column, const int &channel, const int &value) {
    if (valueValid(value)){
        Image::setChannel(row, column, channel, value);
    }
}

void PPM::setPixel(const int &row, const int &column, const int &red, const int &green, const int &blue) {
    Image::setChannel(row, column, 0, red);
    Image::setChannel(row, column, 1, green);
    Image::setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream &os) const {
    os << "P6" << " " << Image::getWidth() << " " << Image::getHeight() << " " << mMaxColorValue << "\n";
//rows   
    for (int i = 0; i < Image::getHeight(); i++) {
//pixels    
        for (int i2 = 0; i2 < Image::getWidth(); i2++) {
//rgb channels  
            for (int i3 = 0; i3 < 3; i3++){
                unsigned char c = Image::getChannel(i, i2, i3);
                os.write((char *) &c, sizeof(c));
                //os << "test\n";
            }
        }
    }
}

void PPM::readStream(std::istream &is) {
    //watch zoom for febuary 6
    int row, col, chan;
    std::string p6;
    int width, height, val;
    is >> p6;
    is >> width; 
    Image::setWidth(width); 
    is >> height;
    Image::setHeight(height);
    is >> val; 
    PPM::setMaxColorValue(val);
    unsigned char c;
    is.read((char *) &c, 1);
    for(row = 0; row < height; row++){
        for(col=0; col < width; col ++){
            for(chan = 0; chan < 3; chan ++){
                is.read((char *) &c, 1);
                PPM::setChannel(row, col, chan, c);
            }
        }
    }
}