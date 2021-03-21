#ifndef COLORLUT_HPP
#define COLORLUT_HPP

//singleton class for a color look up table. 
//singleton for practise (and because it makes sense)

#include <map>

class ColorLut{

    public:

    /*Methods*/
    static ColorLut& getInstance(){
        static ColorLut instance; // This is guaranteed to be created once and destroyed properly.

        return instance;
    }
    int rgb_to_8bit(double r, double g, double b);

    //delete methods we dont want to have in our singleton
    ColorLut(ColorLut const&)       = delete;
    void operator=(ColorLut const&) = delete;

    private:

    /*Members*/
    std::map<int, int> LUT;

    /*Methods*/
    ColorLut();

};

#endif