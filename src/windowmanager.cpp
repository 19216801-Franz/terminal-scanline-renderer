#include "../include/windowmanager.hpp"

Windowmanager::Windowmanager(int height, int width, int startx, int starty){

    // initialise windows, this time also screen
    this->mywindow = initscr();
    this->screen = newwin(height,width,starty,startx);
    // getch() nonblocking
    nodelay(mywindow, TRUE);
    // dont print inputs to screen
    noecho();
    // no cursor
    curs_set(0);
    start_color();
    use_default_colors();
    this->hascolor = (has_colors() == TRUE) ? true : false;
    // set combination code iterator to default value over 1
    combiterator = 3;

    screenwidth = width;
    screenheight = height;
}

Windowmanager::~Windowmanager(void){

    nodelay(mywindow, FALSE);
    endwin();
}

void Windowmanager::printxyc(unsigned int x, unsigned int y, short text, short background, bool bold, const char* string){    

    // only print color if terminal supports color output
    if(hascolor){

        // save color combination if it's the first time we use it
        if(knowncombinations[std::make_pair(text,background)] == 0){

            knowncombinations[std::make_pair(text,background)] = combiterator;
            init_pair(combiterator++, text, background);
        }

        int code = knowncombinations[std::make_pair(text,background)];
        
        attron(COLOR_PAIR(code));
        if(bold){attron(A_BOLD);}
            
        mvwprintw(mywindow, y, x, string);

        attroff(COLOR_PAIR(code));
        if(bold){attroff(A_BOLD);}

        return;

    }else{
        mvwprintw(mywindow, y, x, string);
        return;

    } 
}

void Windowmanager::printc(short text, short background, bool bold, const char* string){
    
    // only print color if terminal supports color output
    if(hascolor){

        // save color combination if it's the first time we use it
        if(knowncombinations[std::make_pair(text,background)] == 0){

            knowncombinations[std::make_pair(text,background)] = combiterator;
            init_pair(combiterator++, text, background);
        }

        int code = knowncombinations[std::make_pair(text,background)];
        
        attron(COLOR_PAIR(code));
        if(bold){attron(A_BOLD);}

        wprintw(mywindow, string);

        attroff(COLOR_PAIR(code));
        if(bold){attroff(A_BOLD);}

        return;

    }else{
         wprintw(mywindow, string);
         return;

    } 


}
void Windowmanager::clearscreen(){
    erase(); 
}
