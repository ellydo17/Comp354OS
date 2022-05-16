The bonus features that we have implemented in project 6 are:

1. Bonus 4
    We created a new shell command "find <file>" that tells the user if the file exists or not. In the shell program, if the user chooses to find a file, the OS will make a system call to the kernel to check if the file exists or not. This system call corresponds with the findFile method in the kernel.
    We also created a user program called "ffProg.c" that calls the findFile method from the kernel via the user library.
2. Bonus 5
    We created a menu-based interface that allows the user to select the OS service they want to use by entering the number that corresponds to the service. The choices for the OS service are:
    1. Read a file
    2. Execute a program
    3. Delete a file
    4. Copy a file
    5. View all files in directory
    6. View all processes running currently
    7. Kill a process
    8. Find a file