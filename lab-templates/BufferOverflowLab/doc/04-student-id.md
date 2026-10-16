## What is Your Student ID?

[//]: # (In Stages 0 and 5, you do not need your student ID.)
In Stage 0, you do not need your student ID.
In the remaining stages, you will need your student ID, either as an integer or as a string.


### Your Student ID as an Integer

For 98.8% of students, the integer version of your student ID is simply your NUID interpreted as a decimal integer.
For the other 1.2% of students, this simple interpretation would result in a `0A` byte, which will be problematic in your attack.
For those students, your student ID is a modified form of your NUID.

- If multiplying your NUID by 2 does not have a `0A` byte, then that is the integer version of your student ID; otherwise,
- If dividing your NUID by 2 does not have a `0A` byte, then that is the integer version of your student ID; otherwise,
- If multiplying your NUID by 4 does not have a `0A` byte, then that is the integer version of your student ID; otherwise,
- Dividing your NUID by 4 will not have a `0A` byte, and that is the integer version of your student ID.

Examples of this modification:

|   NUID   |   No shifts   | One left shift | One right shift | Two left shifts | Two right shifts |
|:--------:|:-------------:|:--------------:|:---------------:|:---------------:|:----------------:|
|          |     98.8%     |     1.03%      |     0.143%      |    0.00121%     |    0.000002%     |
| 00000001 | 0x00'00'00'01 |                |                 |                 |                  |
| 00000010 | 0x00'00'00'0A | 0x00'00'00'14  |                 |                 |                  |
| 87556106 | 0x05'38'00'0A | 0x0A'70'00'14  |  0x02'9C'00'05  |                 |                  |
| 88738324 | 0x05'4A'0A'14 | 0x0A'94'14'28  |  0x02'A5'05'0A  |  0x15'28'28'50  |                  |
| 42273300 | 0x02'85'0A'14 | 0x05'0A'14'28  |  0x01'42'85'0A  |  0x0A'14'28'50  |  0x00'A1'42'85   |


### Your Student ID as a String

The string version of your student ID consists of the digits of your NUID, including leading `0`s.
Even if the integer version of your student ID required modification, the string version is unmodified.


### Double-Checking Your Student ID

If in doubt, run `build/target` without any arguments; in addition to providing usage information,
this will print the possibly-modified integer version and the string version of your NUID.

For example, most students will not have their NUID be modified:

```
% build/target

[INFO] Usage:
[INFO]   target <stage-number> [print (input|stack)+]
[INFO]
[INFO] Arguments:
[INFO]   <stage-number>  Required integer in the range [0, 4]
[INFO]   print           Enable printing of diagnostic data
[INFO]     input         Print your input
[INFO]     stack         Print stack snapshots

[INFO] Student ID (integer): 12345678 (0x00bc614e)
[INFO] Student ID (string): "12345678"

```

but a few will:

```
% build/target

[INFO] Usage:
[INFO]   target <stage-number> [print (input|stack)+]
...

[INFO] Student ID (integer): 354953296 (0x15282850)
[INFO] Student ID (string): "88738324"

```


---

|                      [⬅️](03-stage0.md)                      |      [⬆️](../README.md)      |                      [➡️](05-stage1.md)                       |
|:------------------------------------------------------------:|:----------------------------:|:-------------------------------------------------------------:|
| [Stage 0: Simple Buffer Overflow on the Stack](03-stage0.md) | [Front Matter](../README.md) | [Stage 1: Code Injection with Integer Argument](05-stage1.md) |
