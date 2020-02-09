322 Lab 0 README 
Created by Priya Singh

This README documents the process of the creation of Lab 0.
---

Feb 2, 2020

Program accepts command line arguments.

Added user input function if missing file name.

Added error checking if input file is missing.

Committed everything to GitHub.

Updated Notes in GitHub.
---

Feb 3, 2020

Double checked fopen function.

Tried using read, but mix with pointer caused trouble, so changed fopen to open and discarded all pointers.

Read works, cleaned up garbage at end of file.
---

Feb 4, 2020

Added padding to missing binary spaces.

Added functions for converting binary to decimal and ASCII. Code may seem redundant, but for now focusing on making it work.

Optimizing will come later if time.

Everything is committed to GitHub.
---

Feb 5, 2020

Added calc_parity function to calculate the parity bits.

Added function prototypes.

Learned the difference between using scanf("%s", char_array) and ("%s", &char_array). One gives a warning one doesn't.

Looking into using scanf() instead of read() to solve whitespace and newline issue.

Scrapped all scanf()s is exchange for fget to fulfill stdin requirement.

Confused as to if I need to somehow account for identifying if the second command line argument if a binary or filename inputs.
(E.g. ./demo input.txt vs. ./demo 101011100)  

Trying to follow assignment instructions, manually converting non-printable ASCII chars into mnemonic equivalent. Yay.

Technically today is now Feb 6, 2020

Scrapped entire function to get binary string and redid it. 
---

Feb 6, 2020
(After 6AM)

Fixed processing command arguments to be specific in what it is accepting. If there is a filename, all other arguments are ignored.

If it starts with binary, it will finish in binary unless there is something other than 0 or 1. Then it will abort.
---

Feb 8, 2020

Optimized function to convert to ASCII. Replaced if/else brute force with an array and lookup.

Reduced code where I could. Tried to see the easier patterns to exploit.
---
