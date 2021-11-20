#include "cal.h"
#include <string.h>

int main() {
    char str1[] = "fffffffffffffffffffffffffffffffffffffffffffffffffffffff";
    char str2[] = "fffffffffffffffffffffffffffffff";

    number* a = createNumber(a, 0);
    number* b = createNumber(b, 0);

    a = setNumberWithString(a, str1, strlen(str1));
    b = setNumberWithString(b, str2, strlen(str2));

    showNumber(a);
    showNumber(b);

    return 0;
}
