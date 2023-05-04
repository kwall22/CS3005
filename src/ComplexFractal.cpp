#include "ComplexFractal.h"
#include "ThreadedGrid.h"
#include <cmath>

ComplexFractal::ComplexFractal()
    : ThreadedGrid(201, 301){ // mMin_x(-1.5), mMax_x(1.5), mMin_y(-1), mMax_y(1), mDelta_x(0.01), mDelta_y(0.01){
        setPlaneSize(-1.5, 1.5, -1, 1);
}

ComplexFractal::ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
    : ThreadedGrid(height, width){ // mMin_x(-1.5), mMax_x(1.5), mMin_y(-1), mMax_y(1), mDelta_x(0.01), mDelta_y(0.01) {
    //ThreadedGrid::setGridSize(height, width);
    setPlaneSize(min_x, max_x, min_y, max_y);
    //mDelta_x = 0.01;
    //mDelta_y = 0.01;
    //mMin_x = min_x;
   // mMax_x = max_x;
   // mMin_y = min_y;
    //mMax_y = max_y;
    //setDeltas(calculateDeltaX(), calculateDeltaY());
}

ComplexFractal::~ComplexFractal(){
}

double ComplexFractal::getMinX() const {
    return mMin_x;
}

double ComplexFractal::getMaxX() const {
    return mMax_x;
}

double ComplexFractal::getMinY() const {
    return mMin_y;
}

double ComplexFractal::getMaxY() const {
    return mMax_y;
}

void ComplexFractal::setGridSize(const int &height, const int &width) {
    if (height >= 2 && width >= 2){
        ThreadedGrid::setGridSize(height, width);
        setDeltas(calculateDeltaX(), calculateDeltaY());
    }
}

void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y) {
    if (min_x < -2.0 || min_x > 2.0 || max_x < -2.0 || max_x > 2.0 || min_y < -2.0 || min_y > 2.0 || max_y < -2.0 || max_y > 2.0 || min_x == max_x || min_y == max_y){
        return;
    }
        
    if (min_x > max_x){
        mMax_x = min_x;
        mMin_x = max_x;
    }
    else{
        mMin_x = min_x;
        mMax_x = max_x;
    }
    if (min_y > max_y){
        mMax_y = min_y;
        mMin_y = max_y;
    }
    else{
        mMin_y = min_y;
        mMax_y = max_y;
    }
    setDeltas(calculateDeltaX(), calculateDeltaY());
}

double ComplexFractal::getDeltaX() const {
    return mDelta_x;
}

double ComplexFractal::getDeltaY() const {
    return mDelta_y;
}

void ComplexFractal::setDeltas(const double &delta_x, const double &delta_y) {
    if (delta_x > 0 && delta_y > 0){
        mDelta_x = delta_x;
        mDelta_y = delta_y;
    }
    //else{
        //mDelta_x = 0.01;
        //mDelta_y = 0.01;
    //}
}

double ComplexFractal::calculateDeltaY() const {
    double delta_y = (mMax_y - mMin_y) / (mHeight - 1); 
    return delta_y;
}

double ComplexFractal::calculateDeltaX() const {
    double delta_x = (mMax_x - mMin_x) / (mWidth -1);
    return delta_x;
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const {
    if (column < 0 || column >= mWidth){
        return 0.0;
    }
    double x = getMinX() + column * getDeltaX();
    return x;
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const {
    if (row < 0 || row >= mHeight){
        return 0.0;
    }
    double y = getMaxY() - row * getDeltaY();
    return y;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const {
    if (row < 0 || row >= mHeight || column < 0 || column >= mWidth ){
        y = 0.0;
        x = 0.0;
    }
    else{
        y = calculatePlaneYFromPixelRow(row);
        x = calculatePlaneXFromPixelColumn(column);
    }
}

int ComplexFractal::calculateNumber(const int &row, const int &column) const {
    if (row < 0 || row >= mHeight || column < 0 || column >= mWidth ){
        return -1;
    }
    else{
        double x = calculatePlaneXFromPixelColumn(column);
        double y = calculatePlaneYFromPixelRow(row);
        int val = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
        return val;
    }
}
