#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "expected 1 arg only: filename\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "unable to open '%s'\n", argv[1]);
        return 1;
    }

    // scan file
    while (!feof(f)) {
        char tmp = fgetc(f);
        if ((tmp > 8 && tmp < 13) || (tmp > 31 && tmp < 127)) {
            fputc(tmp, stdout);
        } else if (tmp == '\\') {
            // escape backslash
            fputc('\\', stdout);
            fputc('\\', stdout);
        } else {
            fprintf(stdout, "\033[0;31m\\x%02X\033[0m", (unsigned char)tmp);
        }
    }

    // add final newline
    fprintf(stdout, "\n");
    fclose(f);
    return 0;
}

