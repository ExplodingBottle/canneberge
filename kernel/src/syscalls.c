/* Userland different syscalls for newlib */
#include <kernel/bugcheck.h>
#include <kernel/console.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>

#include <stdio.h>

/* Ability to change errno */
#include <errno.h>

#undef errno
extern int errno;

/* Possible environment variables */
char *__env[1] = {0};
char **_environ = __env;

/* Support for exit. Should probably display a death screen */
void _exit(int code)
{
    bugcheck();
}

int _close(int file)
{
    return -1;
}

int _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}

int _fork(void)
{
    errno = EAGAIN;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _getpid(void)
{
    return 1;
}

int _isatty(int file)
{
    return 1;
}

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

int _link(char *old, char *new)
{
    errno = EMLINK;
    return -1;
}
int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

int _read(int file, char *ptr, int len)
{
    return 0;
}

int _stat(char *file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _times(struct tms *buf)
{
    return -1;
}

int _unlink(char *name)
{
    errno = ENOENT;
    return -1;
}

int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}

int _write(int file, char *ptr, int len)
{
    if (file == 1 || file == 2) /* STDOUT and STDERR */
    {
        console_write(ptr, len);
        return len;
    }
    return 0;
}