## Launching the Program

### RP2040 Memories

The Raspberry Pi Pico on your Cow&nbsp;Pi has two memories:

- 264KB SRAM data memory
- 2MB Flash instruction memory

Unlike modern microprocessors, most microcontrollers don't have cache memories because the CPU and memory speeds are well-matched.
For example, the RP2040 on a Raspberry Pi Pico is clocked at 133MHz, about one order of magnitude slower than the microprocessor in your personal computer.
It doesn't have a cache for the data memory, whose speed is well-matched,
but it does have a 2-way set associative cache for the instruction memory.
Because it shares the same address space as the data memory, we will be able to read from instruction memory to influence the cache's contents.


### Start the Program

The starter code, besides assorted header files and configuration files, consists of:

- `src/`
  - **MemoryLab.c** Driver code
  - **memory_measurement.c** Code to measure the speed of memory reads
  - **cache_measurement.c** Code to obtain data that will allow you to infer information about the RP2040's instruction cache
- `data/`
  <!-- - **answers.txt** A text file with questions for you to answer -->
  - **CacheCharts.xlsx** A spreadsheet that will parse the program's output to generate graphs

<!-- You do not need to (and should not) edit any files other than *answers.txt* and *CacheCharts.xlsx*. -->
You do not need to (and should not) edit any files other than *CacheCharts.xlsx*.

[//]: # (- [ ] Open *answers.txt*, found in the `data/` directory..)
- [ ] Open the MemoryLab assignment on Canvas.
- [ ] Open *CacheCharts.xlsx*, found in the `data/` directory.
- [ ] Connect your Cow&nbsp;Pi to your laptop.
- [ ] Compile the program and upload it to your Cow&nbsp;Pi.

The display module will show the main menu:

<img src="images/Mk4Screens/MainMenu.png" alt="The main menu consists of (1) Memory access time, (2) Cache size, and (3) Cache line size" width="50%">

Use the numeric keypad to make your selection:
1. Measure the memory access times for SRAM data memory and Flash instruction memory
2. Determine the size of the instruction cache using timing data
3. Infer the size of a cache line using timing data


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |           [➡️](03-memory-speed.md)           |
|:----------------------------------------:|:----------------------------:|:---------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Measuring Memory Speed](03-memory-speed.md) |
