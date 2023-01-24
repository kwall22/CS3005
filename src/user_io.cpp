#include <string>
#include "image_menu.h"
#include <iostream>

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt ) {
    std::string b;
    os << prompt;
    is >> b;
    return b;
}
int getInteger(std::istream& is, std::ostream& os, const 
std::string& prompt) {
    int a;
    os << prompt;
    is >> a;
    return a;
}
double getDouble( std::istream& is, std::ostream& os, const std::string& prompt ) {
    double c;
    os << prompt;
    is >> c;
    return c;
}
int askQuestions3(std::istream& is, std::ostream& os) {
    std::string color = getString(is, os, "What is your favorite color? ");
    int n = getInteger(is, os, "What is your favorite integer? ");
    double f = getDouble(is, os, "What is your favorite number? ");
    if(n > 0) {
        for(int i = 0; i < n; i++) {
        os << i+1 << " " << color << " " << f << std::endl;
        }
    }
    else {
        return n;
    }
    return n;
}

