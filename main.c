#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define wait()  Sleep(100)
#define YUKI    "YUKI.N>"
#define EMPTY   "       "

const char* filename = "text";
const unsigned char* text = ">����򤢤ʤ����i��Ǥ���r��\n\
�錄���Ϥ錄���ǤϤʤ�������\n\
\n\
>���Υ�å��`������ʾ���줿�Ȥ������Ȥϡ�\n\
�����ˤϤ��ʤ����錄�������m�ϥ�ҡ������Τߤ��롢\n\
СȪһ�䤬���ڤ��Ƥ���Ϥ��Ǥ��롣\n\
\n\
>���줬�I��\n\
���ʤ��Ͻ���Ҋ�Ĥ���������\n\
\n\
>����Ͼo���ѳ��ץ����Ǥ��롣\n\
\n\
���Ӥ�������Ϥϥ��󥿩`���`��\n\
�����Ǥʤ����ϤϤ�������Υ��`���x�k���衣\n\
\n\
���Ӥ��������ϡ�\n\
���ʤ��ϕr�������ΙC���ä롣\n\
�������ɹ��ϱ��^�Ǥ��ʤ���\n\
�ޤ���߀�α��^��Ǥ��ʤ���\n\
\n\
>���Υץ���ब���Ӥ���Τ�һ�Ȥ���Ǥ��롣\n\
�g�ФΤΤ�����ȥ����롣\n\
\n\
�ǌg�Ф��x�k���줿���Ϥ����Ӥ�������ȥ����롣\n\
\n\
�ң������";

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

