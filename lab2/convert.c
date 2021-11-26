#include "convert.h"

# define ALLOC_ERR -1

char int_to_char(int number) {
    char symbol;
    if (number >= 0 && number <= 9) {
        symbol = number + '0';
    }
    else {
        symbol = number + 'A' - 10;
    }
    return symbol;
}

int resize(char** digits, int len) {
    len += 50;
    char* tmp = realloc(*digits, len * sizeof(char));
    if (tmp != NULL) {
        *digits = tmp;
        return len;
    }
    else {
        free(*digits);
        return ALLOC_ERR;
    }
}

void reverse(char* digits, int len) {
    for (int i = 0; i < len / 2; i++) {
        int j = len - i - 1;
        char tmp = digits[i];
        digits[i] = digits[j];
        digits[j] = tmp;
    }
}

char* convert(int input, int base){
    int flag_neg = 0;
    if (input < 0) {
        input *= (-1);
        flag_neg = 1;
    }

    if (input == 0){
        return "0";
    }

    int len = 50;
    int curlen = 0;

    char* digits = calloc(len, sizeof(char));

    for (; input != 0; curlen++) {
        int mod = input % base;
        char digit = int_to_char(mod);

        if (curlen > len) {
            len = resize(&digits, len);
        }

        digits[curlen] = digit;
        input /= base;
    }

    if (flag_neg) {
        if (curlen > len) {
            len = resize(&digits, len);
        }

        digits[curlen] = '-';
        curlen++;

        if (curlen > len) {
            len = resize(&digits, len);
        }
    }

    digits[curlen] = '\0';

    resize(&digits, curlen);

    reverse(digits, curlen);

    return digits;
}