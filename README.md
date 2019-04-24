# VIRTUAL-MEMORY-MANAGER
  
## Designing a Virtual Memory Manager  
### OS PROJECT FOR 4TH SEMESTER  
This project consists of writing a program that translates logical to physical addresses for a virtual address space of size 216 = 65,536 bytes. Your program will read from a file containing logical addresses and, using a TLB as well as a page table, will translate each logical address to its corresponding physical address and output the value of the byte stored at the translated physical address. The goal behind this project is to simulate the steps involved in translating logical to physical addresses.   
#### SPECIFICS  
Your program will read a file containing several 32-bit integer numbers that represent logical addresses. However, you need only be concerned with 16-bit addresses, so you must mask the rightmost 16 bits of each logical address. These 16 bits are divided into (1) an 8-bit page number and (2) 8-bit page offset
Other specifics include the following:  
•  28 entries on the page table   
•  Page size of 28 bytes   
•  16 entries in the TLB   
•  Frame size of 28 bytes   
•  256 frames   
•  Physical memory of 65,536 bytes (256 frames x 256-byte frame size)   
Additionally, your program need only be concerned with reading logical address and translating them to their corresponding physical addresses. You do not need to support writing to the logical address space.  
#### ADDRESS TRANSLATION  
Your program will translate logical to physical address using a TLB and page table as outlined in the course’s textbook Section 7.4. First, the page number is extracted from the logical address, and the TLB is consulted. In the case of a TLB-hit, the frame number is obtained from the TLB. In the case of a TLB-miss, the page table must be consulted. In the latter case, either the frame number is obtained from the page table or a page fault occurs.  
