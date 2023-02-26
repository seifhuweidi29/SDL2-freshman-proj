void draw(int x_cells, int y_cells)
{
    //Initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    //Load Audio Files
    Mix_Music *backgroundmusic = Mix_LoadMUS("bgm.wav");
    Mix_Chunk *clickEffect = Mix_LoadWAV("coin.wav");
    Mix_Chunk *win = Mix_LoadWAV("win.wav");
    //Play music
    Mix_PlayMusic(backgroundmusic, -1);
    int spaces = 9;
    int winner = 0;
    int turn = 1; //starts with player 1 (blue)
    while (spaces > 0)
    {

        int key = get_key();
        if(is_mouse_clicked() && (turn==1) && (is_color_equal(get_cell_color(get_mouse_pos_x(),get_mouse_pos_y()),COLOR_WHITE)) && (winner==0))
        {
            set_cell_color(get_mouse_pos_x(),get_mouse_pos_y(),COLOR_BLUE);
            Mix_PlayChannel(-1, clickEffect, 0);
            spaces--;
            checkWinner(&turn, &winner, &spaces);
            if(winner==1)
            {
                Mix_HaltMusic();
                Mix_PlayChannel(-1, win, 0);
                //win animation for blue
                set_cell_color(1,1,COLOR_BLACK);
                delay(114);
                set_cell_color(1,0,COLOR_BLACK);
                set_cell_color(1,2,COLOR_BLACK);
                set_cell_color(0,1,COLOR_BLACK);
                set_cell_color(2,1,COLOR_BLACK);
                delay(127);
                set_cell_color(0,0,COLOR_BLACK);
                set_cell_color(2,0,COLOR_BLACK);
                set_cell_color(0,2,COLOR_BLACK);
                set_cell_color(2,2,COLOR_BLACK);
                delay(244);
                set_cell_color(0,0,COLOR_BLUE);
                set_cell_color(2,0,COLOR_BLUE);
                set_cell_color(0,2,COLOR_BLUE);
                set_cell_color(2,2,COLOR_BLUE);
                delay(207);
                set_cell_color(1,0,COLOR_BLUE);
                set_cell_color(1,2,COLOR_BLUE);
                set_cell_color(0,1,COLOR_BLUE);
                set_cell_color(2,1,COLOR_BLUE);
                delay(129);
                set_cell_color(1,1,COLOR_BLUE);

            }
            if(winner==0 && spaces==0)
            {
                flush();
                turn=1;
                spaces=9;
            }
            else
            {
                turn=2;
            }
        }
        else if(is_mouse_clicked() && (turn==2) && (is_color_equal(get_cell_color(get_mouse_pos_x(),get_mouse_pos_y()),COLOR_WHITE)) && (winner==0) && (spaces>0))
        {
            set_cell_color(get_mouse_pos_x(),get_mouse_pos_y(),COLOR_RED);
            Mix_PlayChannel(-1, clickEffect, 0);
            spaces--;
            checkWinner(&turn, &winner, &spaces);
            if(winner==2)
            {
                Mix_PlayChannel(-1, win, 0);
                Mix_HaltMusic();
                Mix_PlayChannel(-1, win, 0);
                //win animation for red
                set_cell_color(1,1,COLOR_BLACK);
                delay(114);
                set_cell_color(1,0,COLOR_BLACK);
                set_cell_color(1,2,COLOR_BLACK);
                set_cell_color(0,1,COLOR_BLACK);
                set_cell_color(2,1,COLOR_BLACK);
                delay(127);
                set_cell_color(0,0,COLOR_BLACK);
                set_cell_color(2,0,COLOR_BLACK);
                set_cell_color(0,2,COLOR_BLACK);
                set_cell_color(2,2,COLOR_BLACK);
                delay(244);
                set_cell_color(0,0,COLOR_RED);
                set_cell_color(2,0,COLOR_RED);
                set_cell_color(0,2,COLOR_RED);
                set_cell_color(2,2,COLOR_RED);
                delay(207);
                set_cell_color(1,0,COLOR_RED);
                set_cell_color(1,2,COLOR_RED);
                set_cell_color(0,1,COLOR_RED);
                set_cell_color(2,1,COLOR_RED);
                delay(129);
                set_cell_color(1,1,COLOR_RED);
            }
            turn=1;
        }
        delay(10);
    }
}

void flush()
{
    Mix_Chunk *se = Mix_LoadWAV("grass1.wav");
    int x,y;
    for(y=0; y<3; y++)
    {
        for(x=0; x<3; x++)
        {
            set_cell_color(x,y,COLOR_WHITE);
            Mix_PlayChannel(-1, se, 0);
            delay(100);
        }
    }
}

void checkWinner(int* p, int* w, int* s)
{
    if(*p==1)
    {
        if( ( (is_color_equal(get_cell_color(0,0),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,0),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,0),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(0,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,1),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(0,2),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,2),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,2),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(0,0),COLOR_BLUE)) && (is_color_equal(get_cell_color(0,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(0,2),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(1,0),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,2),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(2,0),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,2),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(0,0),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,2),COLOR_BLUE)) ) ||
           ( (is_color_equal(get_cell_color(0,2),COLOR_BLUE)) && (is_color_equal(get_cell_color(1,1),COLOR_BLUE)) && (is_color_equal(get_cell_color(2,0),COLOR_BLUE)) ) )
        {
            *w = 1;
        }
    }
    else if(*p==2)
    {
        if( ( (is_color_equal(get_cell_color(0,0),COLOR_RED)) && (is_color_equal(get_cell_color(1,0),COLOR_RED)) && (is_color_equal(get_cell_color(2,0),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(0,1),COLOR_RED)) && (is_color_equal(get_cell_color(1,1),COLOR_RED)) && (is_color_equal(get_cell_color(2,1),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(0,2),COLOR_RED)) && (is_color_equal(get_cell_color(1,2),COLOR_RED)) && (is_color_equal(get_cell_color(2,2),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(0,0),COLOR_RED)) && (is_color_equal(get_cell_color(0,1),COLOR_RED)) && (is_color_equal(get_cell_color(0,2),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(1,0),COLOR_RED)) && (is_color_equal(get_cell_color(1,1),COLOR_RED)) && (is_color_equal(get_cell_color(1,2),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(2,0),COLOR_RED)) && (is_color_equal(get_cell_color(2,1),COLOR_RED)) && (is_color_equal(get_cell_color(2,2),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(0,0),COLOR_RED)) && (is_color_equal(get_cell_color(1,1),COLOR_RED)) && (is_color_equal(get_cell_color(2,2),COLOR_RED)) ) ||
           ( (is_color_equal(get_cell_color(0,2),COLOR_RED)) && (is_color_equal(get_cell_color(1,1),COLOR_RED)) && (is_color_equal(get_cell_color(2,0),COLOR_RED)) ) )
        {
            *w = 2;
        }
    }
}
