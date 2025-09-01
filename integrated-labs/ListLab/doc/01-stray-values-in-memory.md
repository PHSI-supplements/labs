## Stray Values in Memory

> 📇 **Scenario**
>
> Working at the Pleistocene Petting Zoo certainly is proving to be interesting.
> You’re glad that you don’t have to worry about the problem of the giant sloths very slowly chasing their handlers, but now it seems that Archie has decided to try to write a program or two.
> At a glance, his code is smellier than the wooly rhinoceros’ enclosure.
> But you take a closer look anyway to try to understand why his code acts strangely.

### Pleistocene Petting Zoo Marquee

> Archie shows you his first program, which he hoped would be used to greet guests, but it doesn’t always work right:
> ```c
> /***********************************************************************
>   * This program will output
>   **         Welcome to the
>   **    Pleistocene Petting Zoo!
>   **
>   ** Get ready for hands-on excitement on the count of three! 1.. 2.. 3..
>   ** Have fun!
>   * With brief pauses during the "Get ready" line.
>   ***********************************************************************/
> 
> #include <stdio.h>
> #include <unistd.h>
> 
> void splash_screen(void) {
>     char const *first_line = "\t     Welcome to the\n";
>     char const *second_line = "\tPleistocene Petting Zoo!\n";
>     printf("%s%s\n", first_line, second_line);
> }
> 
> void count(void) {
>     int i;
>     sleep(1);
>     printf("Get ready for hands-on excitement on the count of three! ");
>     while (i < 3) {
>         fflush(stdout);
>         sleep(1);
>         i++;
>         printf("%d.. ", i);
>     }
>     printf("\nHave fun!\n");
> }
> 
> int main(void) {
>     splash_screen();
>     count();
>     return 0;
> }
> ```
> Sometimes the output was what he expected:
> ```
>          Welcome to the
>     Pleistocene Petting Zoo!
>
> Get ready for hands-on excitement on the count of three! 1.. 2.. 3..
> Have fun!
> ```
> But sometimes the output was missing the "1.. 2.. 3..":
> ```
>          Welcome to the
>     Pleistocene Petting Zoo!
>
> Get ready for hands-on excitement on the count of three!
> Have fun!
> ```

What mistake did Archie make?
What change to *one* line will fix Archie's bug?

- [ ] Type your answers in the Canvas quiz.


### Math Doesn't Work Right ... Or Does It?

> 📇 **Scenario, continued**
>
> “Wow,” Archie says.
> “I can’t believe that I missed that.
> Maybe you can help me with some other code that I wrote for one of my other start-ups.
> Here it is.”
> Archie shows you the code:
> ```c
> /***********************************************************************
> * This program will add two numbers, and then it will multiply two other
> * numbers. Finally, it will subtract the second result from the first
> * result.
> ***********************************************************************/
>
> #include <stdio.h>
>
> int *add(int a, int b) {
>     int addition_result = a + b;
>     return &addition_result;
> }
> 
> int *multiply(int p, int q) {
>     int multiplication_result = p * q;
>     return &multiplication_result;
> }
> 
> int main(void) {
>     int *sum = add(4, 5);
>     printf("sum = %d\n", *sum);
>     int *product = multiply(2, 3);
>     printf("product = %d\n", *product);
>     printf("sum - product = %d - %d = %d\n",
>     *sum, *product, *sum - *product);
>     return 0;
> }
> ```
> Archie explains that when he compiles the program with the **clang** compiler and then runs it, he gets this output:
> ```
> sum = 9
> product = 6
> sum - product = 6 - 6 = 0
> ```
> And when he compiles the program with the **gcc** compiler and then runs it, the program terminates with a segmentation fault.
>
> "I see that one compiler is giving me an incorrect answer,
> and the other compiler is telling me that I'm using memory in an unsafe way --
> but what am I doing wrong, and why does it produce an incorrect answer?"

What mistake did Archie make?
Why does `*sum` have the value 6 on line 25?
Why does `*sum - *product` produce the value 0?
Without changing the function signatures, how can Archie's code be fixed?

- [ ] Type your answers in the Canvas quiz.

---

|                 |      [⬆️](../README.md)      |              [➡️](02-getting-started.md)              |
|:---------------:|:----------------------------:|:-------------------------------------------------:|
|                 | [Front Matter](../README.md) |  [The Books, Business Rules](02-getting-started.md)   |
