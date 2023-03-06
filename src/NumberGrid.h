#ifndef NUMBERGRID_H
#define NUMBERGRID_H
#include <vector>
#include "PPM.h"

class NumberGrid {
public:
    NumberGrid();
    NumberGrid(const int& height, const int& width);

    virtual ~NumberGrid();
    int getHeight( ) const;
    int getWidth( ) const;
    int getMaxNumber( ) const;
    void setGridSize( const int& height, const int& width );
    void setMaxNumber( const int& number );
    const std::vector< int >& getNumbers( ) const;
    int index( const int& row, const int& column ) const;
    bool indexValid( const int& row, const int& column ) const;
    bool numberValid( const int& number ) const;
    int getNumber( const int& row, const int& column ) const;
    void setNumber( const int& row, const int& column, const int& number );
    void setPPM( PPM& ppm ) const;

    protected:
        int mHeight;
        int mWidth;
        int mMaxValue;
        std::vector<int> mGrid;

};
#endif