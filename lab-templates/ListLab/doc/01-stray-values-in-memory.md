## Stray Values in Memory

> 📇 **Scenario**
>
> Working at the Pleistocene Petting Zoo certainly is proving to be interesting.
> You’re glad that you don’t have to worry about the problem of the giant sloths very slowly chasing their handlers, but now it seems that Archie has decided to try to write a program or two.
> At a glance, his code is smellier than the wooly rhinoceros’ enclosure.
> But you take a closer look anyway to try to understand why his code acts strangely.

- [ ] Open the [ListLab Code Study](https://canvas.unl.edu/courses/209782/assignments/2190066) quiz in Canvas.

### Pleistocene Petting Zoo Marquee

> Archie shows you his first program, which he hoped would be used to greet guests, but it doesn’t always work right:
> ```c
>  1. /***********************************************************************
>  2.  *  This program will output
>  3.  **         Welcome to the
>  4.  **    Pleistocene Petting Zoo!
>  5.  **
>  6.  **    Get ready for hands-on excitement on the count of three! 1.. 2.. 3..
>  7.  **    Have fun!
>  8.  *  With brief pauses during the "Get ready" line.
>  9.  ***********************************************************************/
> 10. 
> 11. #include <stdio.h>
> 12. #include <unistd.h>
> 13. 
> 14. void splash_screen(void) {
> 15.     char const *first_line = "\t     Welcome to the\n";
> 16.     char const *second_line = "\tPleistocene Petting Zoo!\n";
> 17.     printf("%s%s\n", first_line, second_line);
> 18. }
> 19. 
> 20. void count(void) {
> 21.     int i;
> 22.     sleep(1);
> 23.     printf("Get ready for hands-on excitement on the count of three! ");
> 24.     while (i < 3) {
> 25.         fflush(stdout);
> 26.         sleep(1);
> 27.         i++;
> 28.         printf("%d.. ", i);
> 29.     }
> 30.     printf("\nHave fun!\n");
> 31. }
> 32. 
> 33. int main(void) {
> 34.     splash_screen();
> 35.     count();
> 36.     return 0;
> 37. }
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
>  1. /***********************************************************************
>  2. * This program will add two numbers, and then it will multiply two other
>  3. * numbers. Finally, it will subtract the second result from the first
>  4. * result.
>  5. ***********************************************************************/
>  6.
>  7. #include <stdio.h>
>  8.
>  9. int *add(int a, int b) {
> 10.     int addition_result = a + b;
> 11.     return &addition_result;
> 12. }
> 13. 
> 14. int *multiply(int p, int q) {
> 15.     int multiplication_result = p * q;
> 16.     return &multiplication_result;
> 17. }
> 18. 
> 19. int main(void) {
> 20.     int *sum = add(4, 5);
> 21.     printf("sum = %d\n", *sum);
> 22.     int *product = multiply(2, 3);
> 23.     printf("product = %d\n", *product);
> 24.     printf("sum - product = %d - %d = %d\n",
> 25.            *sum, *product, *sum - *product);
> 26.     return 0;
> 27. }
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
