#include "ActionData.h"

ActionData::ActionData(std::istream& is, std::ostream& os) 
    : mIs(is), mOs(os), mQuit(false) {
}

std::istream& ActionData::getIS() {
    return mIs;
}

std::ostream& ActionData::getOS() {
    return mOs;
}

PPM& ActionData::getInputImage1() {
    return mII1;
}

PPM& ActionData::getInputImage2() {
    return mII2;
}

PPM& ActionData::getOutputImage() {
    return mOutI;
}

bool ActionData::getDone() const {
    return mQuit;
}

void ActionData::setDone() {
    mQuit = true;
}
