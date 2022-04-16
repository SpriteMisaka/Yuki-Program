#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define wait()  Sleep(100)
#define YUKI    "YUKI.N>"
#define EMPTY   "       "

const char* filename = "text";
const unsigned char* text = ">これをあなたが読んでいる時、\n\
わたしはわたしではないだろう。\n\
\n\
>このメッセージが表示されたということは、\n\
そこにはあなた、わたし、涼宮ハルヒ、朝比奈みくる、\n\
小泉一樹が存在しているはずである。\n\
\n\
>それが鍵。\n\
あなたは解答を見つけ出した。\n\
\n\
>これは緊急脱出プログラムである。\n\
\n\
起動させる場合はエンターキーを、\n\
そうでない場合はそれ以外のキーを選択せよ。\n\
\n\
起動させた場合、\n\
あなたは時空修正の機会を得る。\n\
ただし成功は保証できない。\n\
また帰還の保証もできない。\n\
\n\
>このプログラムが起動するのは一度きりである。\n\
実行ののち、消去される。\n\
\n\
非実行が選択された場合は起動せずに消去される。\n\
\n\
Ｒｅａｄｙ？";

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
    while ((fp = fopen(filename, "rb")) == NULL) {
        fp = fopen(filename, "wb+");
        fputs(text, fp);
        fclose(fp);
    }
    
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

