#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define wait()  Sleep(100)
#define YUKI    "YUKI.N>"
#define EMPTY   "       "

void fullscreen() {
    // Get current console window.
    HWND hwnd = GetConsoleWindow();
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Set buffer size to disable scroll bar.
    COORD size;
    size.X = GetSystemMetrics(SM_CXMIN);
    size.Y = GetSystemMetrics(SM_CYMIN);
    SetConsoleScreenBufferSize(handle, size);
    
    // Fullscreen.
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);
    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) &
        ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
} 

int main(void) {
    fullscreen();
    
    FILE* fp;
    if((fp = fopen("text", "r")) == NULL) exit(0);
    
    char ch, prev;
    while((ch = fgetc(fp)) != EOF) {
        if(ch == '>') {
            char* p;
            for(p = YUKI; *p != '\0'; ++p) {
                printf("%c", *p);
                wait();
            }
        }
        else if(ch & 0x80) {
            if(prev == '\n') {
                printf(EMPTY);
            }
            char tmp[3];
            tmp[0] = ch;
            tmp[1] = fgetc(fp);
            tmp[2] = '\0';
            printf("%s", tmp);
            wait();
        } else {
            printf("%c", ch);
            wait();
        }
        prev = ch;
    }
    
    getch();
    
    fclose(fp);
    return 0;
}

