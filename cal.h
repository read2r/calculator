#ifndef __CAL_H__
#define __CAL_H__

typedef unsigned int element;

typedef struct _Number {
    int size;
    element* data;
} Number;

typedef Number number;

int atoi16(char a);
char itoa16(int i);

number* createNumber(number* newNumber, element size);
number* resizeNumber(number* num, int size, int initFlag);
void releaseNumber(number* num);

number* setNumberWithUnsignedInt(number* num, element n);
number* setNumberWithNumber(number* num, const number* src);
number* setNumberWithString(number* num, char* str, int len);

element getDataAt(const number* num, element idx);
void showNumber(const number* num);

element getCarry(const element a, const element b, element carry);
number* add(number* result, const number* A, const number* B);
//number* sub(number* result, const number* A, const number* B);
//number* mul(number* result, const number* A, const number* B);
//number* div(number* result, const number* A, const number* B);

int compareSize(const number* A, const number* B);
int equal(const number* A, const number* B);

#endif
