#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define wait()  Sleep(100)
#define YUKI    "YUKI.N>"
#define EMPTY   "       "

const char* filename = "text";
const unsigned char* text = ">これをあなたが?iんでいる?r、\n\
わたしはわたしではないだろう。\n\
\n\
>このメッセ?`ジが燕幣されたということは、\n\
そこにはあなた、わたし、???mハルヒ、劾曳栂みくる、\n\
弌畑匯?笋?贋壓しているはずである。\n\
\n\
>それが?I。\n\
あなたは盾基を??つけ竃した。\n\
\n\
>これは?o識用竃プログラムである。\n\
\n\
軟?咾気擦???栽はエンタ?`キ?`を、\n\
そうでない??栽はそれ參翌のキ?`を?x?kせよ。\n\
\n\
軟?咾気擦???栽、\n\
あなたは?r腎俐屎の?C氏を誼る。\n\
ただし撹孔は隠?^できない。\n\
また｢??の隠?^もできない。\n\
\n\
>このプログラムが軟?咾垢襪里碗散箸?りである。\n\
?g佩ののち、??肇される。\n\
\n\
掲?g佩が?x?kされた??栽は軟?咾擦困墨?肇される。\n\
\n\
Ｒｅａｄｙ??";

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

