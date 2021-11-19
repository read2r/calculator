#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "cal.h"

int atoi16(char a) {
    int i;
    if(a >= '0' && a <= '9') {
        i = a - '0';
    } else if (a >= 'a' && a <= 'z') {
        i = a - 'a' + 10;
    } else if (a >= 'A' && a <= 'Z') {
        i = a - 'A' + 10;
    }
    return i;
}

char itoa16(int i) {
    char a;
    if(i >= 0 && a <= 9) {
        a = i + '0';
    } else if(a >= 10 && a <= 15) {
        a = i - 10 + 'A';
    }
    return a;
}

number* createNumber(number* newNumber, element size) {
    newNumber = (number*)malloc(sizeof(number));
    newNumber->size = size ? size : 1;
    newNumber->data = (element*)malloc(sizeof(element) * newNumber->size);
    memset(newNumber->data, 0, sizeof(element) * newNumber->size);
    return newNumber;
}

void releaseNumber(number* num) {
    free(num->data);
    num->data = NULL;
    free(num);
    num = NULL;
}

number* resizeNumber(number* num, int size, int initFlag) {
    if(num == NULL || num->size == size) {
        return num;
    }

    if(num->size > size) {
        num->size = size;
        num->data = (element*)realloc(num->data, sizeof(element) * size);
    }

    if(initFlag) {
        memset(num->data, 0, sizeof(element) * num->size);
    }

    return num;
}

number* setNumberWithUnsignedInt(number* num, element n) {
    if(num == NULL) {
        return num;
    }
    num = resizeNumber(num, 1, 1);
    num->data[0] = n;
    return num;
}

number* setNumberWithNumber(number* num, const number* src) {
    if(num == NULL) {
        return num;
    }
    num = resizeNumber(num, src->size, 1);
    memcpy(num, src, sizeof(unsigned) * src->size);
    return num;
}

number* setNumberWithString(number* num, char* str, int len) {
    if(num == NULL) {
        return num;
    }

    int size = len / 8;
    size = (len % 8) ? size + 1 : size;
    num = resizeNumber(num, size, 1);

    element temp = 0;
    for(int i = 0; i < size; i++) {
        int sublen = 8;
        int start = len - sublen * (i + 1);

        if(start < 0) {
            sublen += start;
            start = 0;
        }

        for(int j = 0; j < sublen; j++) {
            num->data[i] <<= 4;
            num->data[i] += atoi16(str[start + j]);
        }
    }

    return num;
}

element getDataAt(const number* num, element idx) {
    if(num == NULL) {
        return 0;
    }

    if(idx < num->size) {
        return num->data[idx];
    } else {
        return 0;
    }
}

void showNumber(const number* num) {
    if(num == NULL) {
        return;
    }

    for(int i = 0; i < num->size; i++) {
        int idx = num->size - i - 1;
        printf("%08x ", num->data[idx]);
    }
    printf("\n");
}

element getCarry(const element a, const element b, element carry) {
    element ah, al, bh, bl;

    ah = a >> 16;
    al = b & 0xffff;
    bh = b >> 16;
    bl = a & 0xffff;

    carry = (al + bl + carry) >> 16;
    carry = (ah + bh + carry) >> 16;

    return carry;
}

number* add(number* result, const number* A, const number* B) {
    if(result == NULL) {
        return result;
    }

    element size = (A->size > B->size) ? A->size : B->size;
    number* temp = createNumber(temp, size + 1);

    element Adata, Bdata, idx, carry;
    idx = 0;
    carry = 0;

    for(; idx < size; idx++) {
        Adata = getDataAt(A, idx);
        Bdata = getDataAt(B, idx);

        temp->data[idx] = Adata + Bdata + carry;
        carry = getCarry(Adata, Bdata, carry);
    }

    if(carry) {
        temp->data[idx] += carry;
    } else {
        resizeNumber(temp, size, 0);
    }

    releaseNumber(result);
    result = temp;

    return result;
}

int compareSize(const number* A, const number* B) {
    return (A->size - B->size);
}

int equal(const number* A, const number* B) {
    if(!compareSize(A, B)) {
        return 0;
    }

    for(int i = 0; i < A->size; i++) {
        if(A->data[i] != B->data[i]) {
            return 0;
        }
    }

    return 1;
} 
