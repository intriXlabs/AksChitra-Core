#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>






// existing functions
int AksChitra_pixel(int cc);
int AksChitra_pixel_xy(int row, int column, int cc);
int AksChitra_pixel_timed(int cc, double delay);
int AksChitra_pixel_timed_xy(int row, int column, int cc, double delay);

int AksChitra_rpixel();
int AksChitra_rpixel_xy(int row, int column);
int AksChitra_rpixel_timed(double delay);
int AksChitra_rpixel_timed_xy(int row, int column, double delay);

int AksChitra_pixel_blink(int cc, double delay, int repeat_count);
int AksChitra_pixel_random_blink(double delay, int repeat_count);

// needed checks and helper functions
int AksChitra_pixel_coords_check(int row, int column);
int AksChitra_get_random_color(void);
void AksChitra_hide_cursor(void);
void AksChitra_show_cursor(void);













// Hide cursor
void AksChitra_hide_cursor(void) {
    printf("\033[?25l");
    fflush(stdout);
}

// Show cursor
void AksChitra_show_cursor(void) {
    printf("\033[?25h");
    fflush(stdout);
}

int AksChitra_get_random_color(void) {
    static int initialized = 0;
    
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    
    return rand() % 256;
}

int AksChitra_pixel_coords_check(int row, int column){

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int term_rows = w.ws_row;
    int term_cols = w.ws_col;

    if(row < 1 || row > term_rows || column < 1 || column > term_cols){
        printf("Invalid coordinates\n");
        return -1;
    }
    return 0;
}

int AksChitra_pixel(int cc){
    if(cc < 0 || cc > 255){
        printf("Invalid color code\n");
        return -1;
    }
    printf("\033[48;5;%dm \033[0m", cc);
    fflush(stdout);
    return 0;
}

int AksChitra_pixel_xy(int row, int column, int cc){
    if(cc < 0 || cc > 255){
        printf("Invalid color code\n");
        return -1;
    }
    if(AksChitra_pixel_coords_check(row, column) == -1){
        return -1;
    }
    printf("\033[%d;%dH\033[48;5;%dm \033[0m", row, column, cc);
    fflush(stdout);
    return 0;
}

int AksChitra_pixel_timed(int cc, double delay){
    if(cc < 0 || cc > 255){
        printf("Invalid color code\n");
        return -1;
    }
    if (delay > 3600) {
    printf("Delay too large\n");
    return -1;
    }
    printf("\033[48;5;%dm \033[0m", cc);
    usleep(delay * 1000000);
    fflush(stdout);
    return 0;
}

int AksChitra_pixel_timed_xy(int row, int column, int cc, double delay){
    if(cc < 0 || cc > 255){
        printf("Invalid color code\n");
        return -1;
    }
    if(AksChitra_pixel_coords_check(row, column) == -1){
        return -1;
    }
    if (delay > 3600) {  // 1 hour max
    printf("Delay too large\n");
    return -1;
    }
    printf("\033[%d;%dH\033[48;5;%dm \033[0m", row, column, cc);
    usleep(delay * 1000000);
    fflush(stdout);
    return 0;
}

int AksChitra_rpixel(){
    int cc = AksChitra_get_random_color();
    printf("\033[48;5;%dm \033[0m", cc);
    fflush(stdout);
    return 0;
}

int AksChitra_rpixel_xy(int row, int column){
    if(AksChitra_pixel_coords_check(row, column) == -1){
        return -1;
    }
    int cc = AksChitra_get_random_color();
    printf("\033[%d;%dH\033[48;5;%dm \033[0m", row, column, cc);
    fflush(stdout);
    return 0;
}

int AksChitra_rpixel_timed(double delay){
    int cc = AksChitra_get_random_color();
    printf("\033[48;5;%dm \033[0m", cc);
    usleep(delay * 1000000);
    fflush(stdout);
    return 0;
}

int AksChitra_rpixel_timed_xy(int row, int column, double delay){
    if(AksChitra_pixel_coords_check(row, column) == -1){
        return -1;
    }
    if (delay > 3600) {
    printf("Delay too large\n");
    return -1;
    }
    int cc = AksChitra_get_random_color();
    printf("\033[%d;%dH\033[48;5;%dm \033[0m", row, column, cc);
    usleep(delay * 1000000);
    fflush(stdout);
    return 0;
}

int AksChitra_pixel_blink(int cc, double delay, int repeat_count){
    if(cc < 0 || cc > 255){
        printf("Invalid color code\n");
        return -1;
    }
    if (delay > 3600) {
    printf("Delay too large\n");
    return -1;
    }
    AksChitra_hide_cursor();
    for(int i = 0; i < repeat_count; i++){
        printf("\033[48;5;%dm \033[0m", cc);
        fflush(stdout);
        usleep(delay * 1000000);
        printf("\b \b");
        fflush(stdout);
        usleep(delay * 1000000);
    }
    AksChitra_show_cursor();
    return 0;
}

int AksChitra_pixel_random_blink(double delay, int repeat_count){
    if(delay > 3600) {
    printf("Delay too large\n");
    return -1;}
    int cc;
    AksChitra_hide_cursor();
    for(int i = 0; i < repeat_count; i++){
        cc= AksChitra_get_random_color();
        printf("\033[48;5;%dm \033[0m", cc);
        fflush(stdout);
        usleep(delay * 1000000);
        printf("\b \b");
        fflush(stdout);
        usleep(delay * 1000000);
    }
    AksChitra_show_cursor();

    return 0;
}