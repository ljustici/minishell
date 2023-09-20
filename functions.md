# Functions related to processes

## fork

`pid_t fork(void);`

fork() **creates a new process by duplicating the calling process**. The new process is referred to as the child process.  The calling process is referred to as the parent process.

The child process and the parent process run in separate memory spaces.  At the time of fork() both memory spaces have the same content.  Memory writes, file mappings (mmap(2)), and unmappings (munmap(2)) performed by one of the processes do not affect the other.

The child inherits copies of the parent's set of open file descriptors.  Each file descriptor in the child refers to the same open file description as the corresponding file descriptor in the parent.  This means that the two file descriptors share open file status flags, file offset, and signal-driven I/O attributes


**Return value:**
On success, parent -> PID of the child, child -> 0
On failure, -1 is returned in the parent, no child process is created, and errno is set to indicate the error


## wait

The wait() system call suspends execution of the calling thread until one of its children terminates.


## waitpid

The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state.
By default, waitpid() waits only for terminated children, but his behavior is modifiable via the options argument


## kill

`int kill(pid_t pid, int sig);`

The kill() system call can be used to send any signal to any process group or process.


## exevec

`int execve(const char *pathname, char *const _Nullable argv[], char *const _Nullable envp[]);`

execve() executes the process referred to by pathname.  This causes the process that is currently being run to be
replaced with a new process, with newly initialized stack, heap, and (initialized and uninitialized) data segments.


# Functions related to file descriptors

## dup

`int dup(int oldfd);`

The dup() system call allocates a new file descriptor.

The single most important thing about dup() is it returns the smallest integer available for a new file descriptor. That's the basis of redirection:

`int fd_redirect_to = open("file", O_CREAT);`
`close(1); /* stdout */`
`int fd_to_redirect = dup(fd_redirect_to); /* magically returns 1: stdout */`
`close(fd_redirect_to); /* we don't need this */`

After this anything written to file descriptor 1 (stdout), magically goes into "file".


## dup2

`int dup2(int oldfd, int newfd);`

The dup2() system call allocates a new file descriptor as an alias of oldfd.


## pipe

`int pipe(int pipefd[2]);`

pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication.  

The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe.  pipefd[1] refers to the write end of the pipe.  Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.

Return value: On success, zero is returned.  On error, -1 is returned, errno is set to indicate the error, and pipefd is left unchanged.


## issaty

The isatty() function tests whether fd is an open file descriptor referring to a terminal.

Return value: returns 1 if fd is an open file descriptor referring to a terminal; otherwise 0 is returned, and errno is set to indicate the error.


## ttyname

`char *ttyname(int fd);`

ttyname() returns a pointer to the pathname of the terminal device that is open on the file descriptor fd, or NULL on error if fd is not connected to a terminal.


## ttyslot

tba


# Functions related to files

## access

tba


## open

tba

## read

tba


## close

tba

## unlink

tba


# Functions related to directories

## getcwd

tba

## chdir

tba


## opendir

tba

## readdir

tba


## closedir

tba


# Functions related to files and directories

## stat

tba


## lstat

tba


## fstat

tba


# Functions related to inputs in the command line

## readline

`char *readline (const char *prompt);

readline will read a line from the terminal and return it, using prompt as a message to the user and waiting until the user inputs a line.
If prompt is NULL or the empty string, no prompt is issued.  


**!!!! The line returned is allocated with malloc(3); the caller must free it when finished.**

The line returned has the final newline removed, so only the text of the line remains.


## rl_clear_history

`void rl_clear_history(void);

It frees private data Readline saves in the history list.


## rl_on_new_line

Tell the update functions that we have moved onto a new (empty) line, usually after ouputting a newline.


## rl_replace_line

tba


## rl_redisplay

tba


## add_history

tba


# Functions related to signals

## signal

tba


## sigaction

tba