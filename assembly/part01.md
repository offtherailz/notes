# [Assembly Language Primer for Hackers][alpfh]

[alpfh]: http://www.worldofhacker.com/Article-Assembly-Language-Primer-For-Hackers-Part-1-System-Organization

## Part 1

### System Organization Basics

There is a CPU (central processing unit), memory (RAM) where things are
stored during runtime and I/O devices. These three pieces communicate via
the system bus.

### The CPU

+ Control unit: retrieve and decode instructions; retrieve and store data
  in memory
+ Execution unit: actual execution of instructions happens here
+ Registers: internal memory locations used as "variables"
+ Flags: indicate various "events" when execution is happening

For example, the zero flag is set when any execution sets a value to zero.

### CPU registers

Four kinds of CPU registers:

+ General purpose registers: EAX EBX ECX EDX ESI EDI ESP EBP
+ Segment registers: CS DS SS ES FS GS
+ Instruction pointer register: EIP
+ Control registers: CR0 CR1 CR2 CR3 CR4

You use general purpose registers for most assembly programming.

### General purpose registers

+ EAX - accumulator register: used for storing operands and result data
+ EBX - base register: pointer to data
+ ECX - counter register: loop operations
+ EDX - data register: I/O pointer
+ ESI - data pointer register for memory operations (source index)
+ EDI - data pointer register for memory operations (destination index)
+ ESP - stack pointer register (always points to the top of the stack)
+ EBP - stack data pointer register

### Specifics of some general purpose registers

He didn't mention that general purpose registers are all 32 bits on this
architecture.

You can access to reference the first 16 bits of EAX by referring to it as
AX. Then you can get the first 8 bits of AX via AH and the second 8 bits
via AL.

The same goes for BX, CX, DX, BH and BL, CH and CL and DH and DL.

### Virtual Memory Model

+ Every process is laid out in the same virtual memory space, regardless of
  the actual memory location.
+ Each process feels that it is in the system alone and enjoys all the
  memory and that no other process exists.
+ The operating system and CPU work together to maintain this abstraction.

### Program memory

+ 0xBFFFFFF     Stack - used for storing function arguments and local vars
+               Unused memory
+               Heap - dynamic memory: malloc()
+               .bss - Uninitialized data
+               .data - Initialized data
+ 0x8048000     .text - Program code

Read from bottom to top. The .text portion is in the lowest bit of memory.
Notice that the stack is in the highest memory.

### Stack is a LIFO

+ 0xAAAAAAAA    High memory
+ 0x10203040        |
                    |
                    |
                    |
                    |
                    |               ESP should point to the top of the
                    |               stack.
                    v
                Low memory

Since the stack is a LIFO and it's laid out from high memory to low memory,
the stack grows down the memory. ESP points to the top of the stack.
A stack supports only two operations. Push adds an item to the top of the
stack. When you add an item, you must update ESP to point to the new top of
the stack. The second operation is pop which removes an item from the top
of the stack. Again, after you do this, ESP is updated to reflect the new
top.
