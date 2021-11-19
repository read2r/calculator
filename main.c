#include "cal.h"

int main() {
    number* temp = createNumber(temp, 0);
    temp = setNumberWithUnsignedInt(temp, 1);
    
    for(int i = 0; i < 10000; i++) {
        temp = add(temp, temp, temp);
    }

    showNumber(temp);

    return 0;
}
