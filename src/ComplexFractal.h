#ifndef COMPLEXFRACTAL_H
#define COMPLEXFRACTAL_H
#include "NumberGrid.h"


class ComplexFractal: public NumberGrid {
public:
    ComplexFractal();
    ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y );
    virtual ~ComplexFractal( );
    double getMinX( ) const;
    double getMaxX( ) const;
    double getMinY( ) const;
    double getMaxY( ) const;
    virtual void setGridSize( const int& height, const int& width );
    void setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y );
    double getDeltaX( ) const;
    double getDeltaY( ) const;
    void setDeltas( const double& delta_x, const double& delta_y );
    double calculateDeltaY( ) const;
    double calculateDeltaX( ) const;
    double calculatePlaneXFromPixelColumn( const int& column ) const;
    double calculatePlaneYFromPixelRow( const int& row ) const;
    void calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const;
    virtual int calculateNumber( const int& row, const int& column ) const;

protected:
  double mMin_x;
  double mMax_x;
  double mMin_y;
  double mMax_y;
  double mDelta_x;
  double mDelta_y;
};


#endif