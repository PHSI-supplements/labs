## Appendix A: Generating Instruction Encodings Using Tools

You can use `gcc` or `clang` as an assembler to turn the assembly code instructions for your attack into machine code.
You can then use `objdump` as a disassembler to obtain the bytes for those instructions.

[//]: # (TODO: Consider splitting this into ISA-specific pages)

### x86-64

For example, suppose that your attack for stage *N* were
```asm
movq  $0xC0DE, %rbx
addq  %rax, %rcx
pushq %rdx
```
Then you would place this in a file such as `stageN.s`.
Next, assemble and disassemble the file:
```shell
gcc -c stageN.s
objdump -d stageN.o > stageN.d
```

The `stageN.d` file now contains:
```text
stageN.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:   48 c7 c3 de c0 00 00    mov    $0xc0de,%rbx
   7:   48 01 c1                add    %rax,%rcx
   a:   52                      push   %rdx
```

The lines in the "text" section show
```
instruction-displacement : instruction-bytes      assembly-instruction      possible-comments
```

Copy the text section into your `stageN.hex` file, and comment-out the plain-text assembly instructions:
```text
   0:   48 c7 c3 de c0 00 00    // mov    $0xc0de,%rbx
   7:   48 01 c1                // add    %rax,%rcx
   a:   52                      // push   %rdx
```

After adding any necessary padding, addresses, and data, 
you can pass this file through `hex2raw` before sending it to `target`.


### A64

For example, suppose that your attack for stage *N* were
```asm
mov w3, #0xC0DE
add x1, x5, #0xB17
stp x2, x7, [sp, -16]!
```
Then you would place this in a file such as `stageN.s`.
Next, assemble and disassemble the file:
```shell
gcc -c stageN.s
objdump -d stageN.o > stageN.d
```

The `stageN.d` file now contains:
```text
stageN.o:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000000000 <.text>:
   0:   52981bc3        mov     w3, #0xc0de                     // #49374
   4:   912c5ca1        add     x1, x5, #0xb17
   8:   a9bf1fe2        stp     x2, x7, [sp, #-16]!
```

The lines in the "text" section show
```
instruction-displacement : instruction-bytes      assembly-instruction      possible-comments
```

Copy the text section into your `stageN.hex` file, and comment-out the plain-text assembly instructions:
```text
   0:   52981bc3        // mov     w3, #0xc0de                     // #49374
   4:   912c5ca1        // add     x1, x5, #0xb17
   8:   a9bf1fe2        // stp     x2, x7, [sp, #-16]!
```

After adding any necessary padding, addresses, and data,
you can pass this file through `hex2raw` before sending it to `target`.



---

|         [⬅️](12-grading.md)          |      [⬆️](../README.md)      |              [➡️](CC-x86-64-encoding.md)              |
|:------------------------------------:|:----------------------------:|:-----------------------------------------------------:|
| [Turn-In and Grading](12-grading.md) | [Front Matter](../README.md) | [x86-64 Instruction Encodings](CC-x86-64-encoding.md) |
