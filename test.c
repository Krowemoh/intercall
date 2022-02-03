#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intcall.h"

int main(char *argc, char *argv[]) {
    char *server_name = "localhost";
    char *user_name = "username";
    char *password = "password";
    char *account = "/path/to/account";

    long code;
    long session_id = ic_universe_session(server_name, user_name, password, account, &code, NULL);

    if (code != 0) {
        fprintf(stderr, "Failed to open session. Code = %ld\n", code);

    } else {
        char subname[4] = "NIVT";
        long subname_len = 4;
        long sub_status = 0;
        long numargs = 3;

        ICSTRING arg1, arg2, arg3;

        arg1.len = 0;

        char *text = "123456780";
        long size = strlen(text);
        arg2.len = size;
        arg2.text = ic_calloc(&size);
        memcpy(arg2.text, text, size);

        arg3.len = 0;

        ic_subcall(subname, &subname_len, &sub_status, &numargs, &arg1, &arg2, &arg3);

        if (sub_status == 0) {
            printf("Calling: %s\n", subname);
            printf("Arg 1: %s\n", arg1.text);;

        } else {
            fprintf(stderr, "Failed to complete subroutine. Code = %ld\n", sub_status);
        }

        ic_free(arg2.text);

        ic_quit(&code);
        if (code != 0) {
            fprintf(stderr, "Failed to close session. Code = %ld\n", code);
        }
    }

    exit(0);
}
