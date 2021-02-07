#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <ncurses.h>
#include <map>

class Windowmanager{

    public: 
         /* Members */
        int screenwidth, screenheight;
        

        /* Methods */
        Windowmanager();
        Windowmanager(int height, int width, int startx, int starty);
        ~Windowmanager();
        void printxyc(unsigned int x, unsigned int y, short text, short background, bool bold, const char* string);
        void printc(short text, short background, bool bold, const char* string);
        void clearscreen();


    private:
        /* Members */
        WINDOW *mywindow, *screen;
        bool hascolor;
        std::map<std::pair<int,int>, int> knowncombinations;
        int combiterator;

        /* Methods */
        

};


#endif
