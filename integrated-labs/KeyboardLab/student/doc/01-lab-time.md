## Lab Time Discussion

During your lab period, the TAs will demonstrate how to read the ASCII table and will provide a refresher on bitwise AND, bitwise OR, and left- and right-shifts.
This refresher will include a class discussion about why this code always outputs "The number is 255." except when number is 0:
```c
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
```
During the remaining time, the TAs will be available to answer questions.

---

|                 |      [⬆️](../README.md)      |               [➡️](02-numbers-as-characters.md)               |
|:---------------:|:----------------------------:|:-------------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [Treating Numbers as Characters](02-numbers-as-characters.md) |
