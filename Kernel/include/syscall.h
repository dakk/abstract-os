#ifndef SYSCALL_H
#define SYSCALL_H

/* Posix syscalls */
#define SYSCALL_POSIX_EXIT			0x01
#define SYSCALL_POSIX_EXECVE		0x02
#define SYSCALL_POSIX_GETPID		0x03
#define SYSCALL_POSIX_FORK			0x04
#define SYSCALL_POSIX_KILL			0x05
#define SYSCALL_POSIX_WAIT			0x06
#define SYSCALL_POSIX_ISATTY		0x07
#define SYSCALL_POSIX_CLOSE			0x08
#define SYSCALL_POSIX_LINK			0x09
#define SYSCALL_POSIX_LSEEK			0x0A
#define SYSCALL_POSIX_OPEN			0x0B
#define SYSCALL_POSIX_READ			0x0C
#define SYSCALL_POSIX_FSTAT			0x0D
#define SYSCALL_POSIX_STAT			0x0E
#define SYSCALL_POSIX_UNLINK		0x0F
#define SYSCALL_POSIX_SBRK			0x10
#define SYSCALL_POSIX_GETTIMEOFDAY	0x11


/* System syscalls */
#define SYSCALL_GET_SINGLETON		0xA0
#define SYSCALL_PUTS				0xA1

#endif
