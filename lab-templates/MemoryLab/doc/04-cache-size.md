## Measuring the Size of the Cache

One of the functions in *cache_measurement.c* is `measure_cache_size()`.
This function, with the assistance of a helper function, iterates over an "array" that  is at one of the addresses that map to the flash instruction memory;
its particular address is one that uses the cache.
On a cache hit, the value is read from the cache's SRAM;
on a cache miss, the value is retrieved from flash memory, and the corresponding block is placed in the cache.

While the first access to the array's elements will probably be misses,
by repeatedly reading from the array, we expect that most accesses will be hits.
Until the size of the "array" is too great to fit into the cache, that is.
When that happens, we will thrash the cache, causing all (or nearly all) accesses to be misses.

The `measure_cache_size()` will increase the size of the "array" until it is too great to fit into the cache.
The program will measure how much CPU time your process spends accessing the data.
We are less concerned with the specific amount of time, as we are with when the program stops being "fast."
(This is a subjective inference, but the data you collect from the RP2040 for this part of the lab won't be subtle.)

Here we show a graph similar to the one you will produce.
The figure shows the cache size measurements for an Intel Core i7 processor in a 2018 MacBook Pro.
This particular processor has a 32KB L1 data cache (also a 32KB L1 instruction cache), a 256KB L2 cache, and a 2MB L3 cache.
There are labels showing where these limits are exceeded -- other measurement artifacts make it difficult to discern the limit of the L1 cache, but we can use the chart to reasonably estimate the sizes of the L2 and L3 caches with an error less than a factor of 2.

![Measurement of cache levels on Intel Core i7 processor. There is a subtle plateau when the working set exceeds L1 cache and a more pronounced plateau when the working set exceeds L2 cache. When the working set exceeds l3 cache, the timing data skyrockets off the chart.](images/IntelImages/IntelI7caches.png)

The main differences between that chart and the chart you'll produce are:
- The RP2040 has only one cache level
- There is less competition for the cache on the RP2040


When taking measurements on the Intel Core i7 processor, the data can be "mushy" because there are other processes using the processor, which will also use the cache.
On the RP2040, the only competition for the cache will be the program's instructions which will occasionally conflict with the "data" we're reading,
and the occasional interrupt by MBED&nbsp;OS\@.

- [ ] Press the **2** key on the numeric keypad (*Cache size*).

A screen with the time to access each of the memories will be displayed:

<img src="images/Mk4Screens/Option2Screen1.png" alt="32B: ___us; 40B: ___us; 48B: ___us; 64B: ___us; 80B: ___us; Press left button to continue" width="150">

- [ ] Open the "Data" tab in *CacheCharts.xlsx* and locate the portion labeled "CACHE SIZE".
- [ ] Copy the times reported for working sets sized 32--80 bytes into the spreadsheet's cells B2--B6.
- [ ] Press the left button to advance to the next page of data.

<img src="images/Mk4Screens/Option2Screen2.png" alt="96B: ___us; 128B: ___us; 160B: ___us; 192B: ___us; 256B: ___us; 320B: ___us; Press left button to continue" width="150">
<img src="images/Mk4Screens/Option2Screen3.png" alt="384B: ___us; 512B: ___us; 640B: ___us; 768B: ___us; 1024B: ___us; 1280B: ___us; Press left button to continue" width="150">
<img src="images/Mk4Screens/Option2Screen4.png" alt="1536B: ___us; 2048B: ___us; 2560B: ___us; 3072B: ___us; 4096B: ___us; 5120B: ___us; Press left button to continue" width="150">
<img src="images/Mk4Screens/Option2Screen5.png" alt="6144B: ___us; 8192B: ___us; 10240B: ___us; 12288B: ___us; 16384B: ___us; 20480B: ___us; Press left button to continue" width="150">
<img src="images/Mk4Screens/Option2Screen6.png" alt="24576B: ___us; 32768B: ___us; 40960B: ___us; 49152B: ___us; 65536B: ___us; Press left button to continue" width="150">

- [ ] Repeatedly copy the times reported into the appropriate cells in the spreadsheet, using the left pushbutton to advance through the pages.
- [ ] When you have finished, use the left pushbutton to return to the main menu.
- [ ] Open the "Cache Size" tab.
<!--
- [ ] Answer question 7 in *answers.txt*.
  7. What is your estimate for the size of the RP2040's cache?
     - The maximum size for which the program runs "fast" is the size of the cache.
-->
- [ ] Take a screenshot of the "Cache Size" tab and paste it into the answer for question 7 in the Canvas assignment.
- [ ] Answer question 8 in the Canvas assignment.
  8. What is your estimate for the size of the RP2040's cache?
      - The maximum size for which the program runs "fast" is the size of the cache.

---

|           [⬅️](03-memory-speed.md)           |      [⬆️](../README.md)      |                 [➡️](05-cache-line.md)                 |
|:--------------------------------------------:|:----------------------------:|:------------------------------------------------------:|
| [Measuring Memory Speed](03-memory-speed.md) | [Front Matter](../README.md) | [Measuring the Size of a Cache Line](05-cache-line.md) |
