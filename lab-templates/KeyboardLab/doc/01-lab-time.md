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

## Workflow Review

If you have forgotten how to retrieve the project and merge it into `main`, review the steps:
- [Using the Terminal](../../documentation/workflow/terminal/retrieving-the-lab.md)
- [Using VS Code](../../documentation/workflow/vscode/retrieving-the-lab.md)
- [Using CLion](../../documentation/workflow/clion/retrieving-the-lab.md)

If you have forgotten how to configure the project, review the steps:
- [Using the Terminal](../../documentation/workflow/terminal/working-on-the-lab.md#configuring-compiling-running-and-testing-linux-native-code)
- [Using VS Code](../../documentation/workflow/vscode/working-on-the-lab.md#configuring-compiling-running-and-testing-linux-native-code)
- [Using CLion](../../documentation/workflow/clion/working-on-the-lab.md#configuring-compiling-running-and-testing-linux-native-code)


---

|                 |      [⬆️](../README.md)      |               [➡️](02-numbers-as-characters.md)               |
|:---------------:|:----------------------------:|:-------------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [Treating Numbers as Characters](02-numbers-as-characters.md) |
