#include "MandelbrotSet.h"
#include <cmath>

MandelbrotSet::MandelbrotSet()
    : ComplexFractal(){
}

MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y){
}

MandelbrotSet::~MandelbrotSet() {

}

void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const {
    x1 = (x0 * x0) - (y0 * y0) + a;
    y1 = (2 * x0 * y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount(const double& a, const double& b) const {
    int escape_count = 0;
    //double a_in = a;
    //double b_in = b;
    double x_in = a;
    double y_in = b;
    while (sqrt(x_in * x_in + y_in * y_in) <= 2 && escape_count < mMaxValue){
        escape_count++;
        double x_out;
        double y_out;
        calculateNextPoint(x_in, y_in, a, b, x_out, y_out);
        x_in = x_out;
        y_in = y_out;
    }
    return escape_count;
}

int MandelbrotSet::calculateNumber(const int& row, const int& column) const {
    if (row < 0 || row >= mHeight || column < 0 || column >= mWidth ){
        return -1;
    }
    else{
        double x = calculatePlaneXFromPixelColumn(column);
        double y = calculatePlaneYFromPixelRow(row);
        int val = calculatePlaneEscapeCount(x, y);
        return val;
    }
}

MandelbrotPower::MandelbrotPower()
    : MandelbrotSet(), mD(2.0){
}

MandelbrotPower::~MandelbrotPower() {
}

double MandelbrotPower::getPower() const { 
    return mD;
}

void MandelbrotPower::setPower(const double& power) {
    mD = power;
}

void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const {
    double x = x0;
    double y = y0;
    double r = std::sqrt( (x * x) + (y * y) );
    double theta = std::atan2( y, x );
    x1 = std::pow(r, mD) * std::cos( mD * theta ) + a;
    y1 = std::pow(r, mD) * std::sin( mD * theta ) + b;
}
