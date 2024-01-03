#include <stdio.h>

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (number | 0xFF == number & 0xFF) {
        printf("The number is 255.\n");
    } else {
        printf("The number is not 255.\n");
    }
    return 0;
}

