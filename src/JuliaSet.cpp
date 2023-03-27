#include "JuliaSet.h"
#include <cmath>

JuliaSet::JuliaSet() 
    : ComplexFractal(), mA(-0.650492), mB(-0.478235) { 
    setMaxNumber(255);
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b) 
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(-0.650492), mB(-0.478235) {
    mA = a;
    mB = b;
}

JuliaSet::~JuliaSet(){

}

double JuliaSet::getA() const {
    return mA;
}

double JuliaSet::getB() const {
    return mB;
}

void JuliaSet::setParameters(const double& a, const double& b) {
    if (a >= -2.0 && a <= 2.0 && b >= -2.0 && b <= 2.0){
        mA = a;
        mB = b;
    }
}

void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const {
    x1 = (x0 * x0) - (y0 * y0) + mA;
    y1 = (2 * x0 * y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const {
    int escape_count = 0;
    double x_in = x0;
    double y_in = y0;
    while (sqrt(x_in * x_in + y_in * y_in) <= 2 && escape_count < mMaxValue){
        escape_count++;
        double x_out = (x_in * x_in) - (y_in * y_in) + mA;
        double y_out = (2 * x_in * y_in) + mB;
        x_in = x_out;
        y_in = y_out; 
    }
    return escape_count;
}

int JuliaSet::calculateNumber(const int &row, const int &column) const {
    //double x = calculatePlaneXFromPixelColumn(column);
    //double y = calculatePlaneYFromPixelRow(row);
    //calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
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
