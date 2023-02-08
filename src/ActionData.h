#ifndef ActionData_H
#define ActionData_H
#include <iostream>
#include "PPM.h"



class ActionData {
public:
    ActionData();
    ActionData(std::istream& is, std::ostream& os);

    std::istream& getIS();
    std::ostream& getOS();
    PPM& getInputImage1();
    PPM& getInputImage2();
    PPM& getOutputImage();
    bool getDone() const;
    void setDone();

private:
    std::istream& mIs;
    std::ostream& mOs;
    PPM mII1;
    PPM mII2;
    PPM mOutI;
    bool mQuit;

};
#endif