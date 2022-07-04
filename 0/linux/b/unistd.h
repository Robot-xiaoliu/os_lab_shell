#ifndef _UNISTD_H
#define _UNISTD_H

/* ok, this may be a joke, but I'm working on it */
#define _POSIX_VERSION 198808L

#define _POSIX_CHOWN_RESTRICTED	/* only root can do a chown (I think..) */
#define _POSIX_NO_TRUNC		/* no pathname truncation (but see in kernel) */
#define _POSIX_VDISABLE '\0'	/* character to disable things like ^C */
/*#define _POSIX_SAVED_IDS */	/* we'll get to this yet */
/*#define _POSIX_JOB_CONTROL */	/* we aren't there quite yet. Soon hopefully */

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#ifndef NULL
#define NULL    ((void *)0)
#endif

/* access */
#define F_OK	0
#define X_OK	1
#define W_OK	2
#define R_OK	4

/* lseek */
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

/* _SC stands for System Configuration. We don't use them much */
#define _SC_ARG_MAX		1
#define _SC_CHILD_MAX		2
#define _SC_CLOCKS_PER_SEC	3
#define _SC_NGROUPS_MAX		4
#define _SC_OPEN_MAX		5
#define _SC_JOB_CONTROL		6
#define _SC_SAVED_IDS		7
#define _SC_VERSION		8

/* more (possibly) configurable things - now pathnames */
#define _PC_LINK_MAX		1
#define _PC_MAX_CANON		2
#define _PC_MAX_INPUT		3
#define _PC_NAME_MAX		4
#define _PC_PATH_MAX		5
#define _PC_PIPE_BUF		6
#define _PC_NO_TRUNC		7
#define _PC_VDISABLE		8
#define _PC_CHOWN_RESTRICTED	9

#include <sys/stat.h>
#include <sys/times.h>
#include <sys/utsname.h>
#include <utime.h>

#ifdef __LIBRARY__

#define __NR_uselib	0
#define __NR_setup	1	/* used only by init, to get system going */
#define __NR_exit	2	
#define __NR_fork	3
#define __NR_read	4
#define __NR_write	5
#define __NR_open	6
#define __NR_close	7
#define __NR_waitpid	8
#define __NR_creat	9
#define __NR_link	10
#define __NR_unlink	11
#define __NR_execve	12
#define __NR_chdir	13
#define __NR_time	14
#define __NR_mknod	15
#define __NR_chmod	16
#define __NR_chown	17
#define __NR_break	18
#define __NR_stat	19
#define __NR_lseek	20
#define __NR_getpid	21
#define __NR_mount	22
#define __NR_umount	23
#define __NR_setuid	24
#define __NR_getuid	25
#define __NR_stime	26
#define __NR_ptrace	27
#define __NR_alarm	28
#define __NR_fstat	29
#define __NR_pause	30
#define __NR_utime	31
#define __NR_stty	32
#define __NR_gtty	33
#define __NR_access	34
#define __NR_nice	35
#define __NR_ftime	36
#define __NR_sync	37
#define __NR_kill	38
#define __NR_rename	39
#define __NR_mkdir	40
#define __NR_rmdir	41
#define __NR_dup	42
#define __NR_pipe	43
#define __NR_times	44
#define __NR_prof	45
#define __NR_brk	46
#define __NR_setgid	47
#define __NR_getgid	48
#define __NR_signal	49
#define __NR_geteuid	50
#define __NR_getegid	51
#define __NR_acct	52
#define __NR_phys	53
#define __NR_lock	54
#define __NR_ioctl	55
#define __NR_fcntl	56
#define __NR_mpx	57
#define __NR_setpgid	58
#define __NR_ulimit	59
#define __NR_uname	60
#define __NR_umask	61
#define __NR_chroot	62
#define __NR_ustat	63
#define __NR_dup2	64
#define __NR_getppid	65
#define __NR_getpgrp	66
#define __NR_setsid	67
#define __NR_sigaction	68
#define __NR_sgetmask	69
#define __NR_ssetmask	10
#define __NR_setreuid	71
#define __NR_setregid	72
#define __NR_sigsuspend	73
#define __NR_sigpending	74
#define __NR_sethostname 75
#define __NR_setrlimit	76
#define __NR_getrlimit	77
#define __NR_getrusage	78
#define __NR_gettimeofday	79
#define __NR_settimeofday	80
#define __NR_getgroups	81
#define __NR_setgroups  82
#define __NR_select	83
#define __NR_symlink	84
#define __NR_lstat	85
#define __NR_readlink	86
#define _syscall0(type,name) \
type name(void) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name)); \
if (__res >= 0) \
	return (type) __res; \
errno = -__res; \
return -1; \
}

#define _syscall1(type,name,atype,a) \
type name(atype a) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(a))); \
if (__res >= 0) \
	return (type) __res; \
errno = -__res; \
return -1; \
}

#define _syscall2(type,name,atype,a,btype,b) \
type name(atype a,btype b) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(a)),"c" ((long)(b))); \
if (__res >= 0) \
	return (type) __res; \
errno = -__res; \
return -1; \
}

#define _syscall3(type,name,atype,a,btype,b,ctype,c) \
type name(atype a,btype b,ctype c) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(a)),"c" ((long)(b)),"d" ((long)(c))); \
if (__res>=0) \
	return (type) __res; \
errno=-__res; \
return -1; \
}

#endif /* __LIBRARY__ */

extern int errno;

int access(const char * filename, mode_t mode);
int acct(const char * filename);
int alarm(int sec);
int brk(void * end_data_segment);
void * sbrk(ptrdiff_t increment);
int chdir(const char * filename);
int chmod(const char * filename, mode_t mode);
int chown(const char * filename, uid_t owner, gid_t group);
int chroot(const char * filename);
int close(int fildes);
int creat(const char * filename, mode_t mode);
int dup(int fildes);
int execve(const char * filename, char ** argv, char ** envp);
int execv(const char * pathname, char ** argv);
int execvp(const char * file, char ** argv);
int execl(const char * pathname, char * arg0, ...);
int execlp(const char * file, char * arg0, ...);
int execle(const char * pathname, char * arg0, ...);
volatile void exit(int status);
volatile void _exit(int status);
int fcntl(int fildes, int cmd, ...);
int fork(void);
int getpid(void);
int getuid(void);
int geteuid(void);
int getgid(void);
int getegid(void);
int ioctl(int fildes, int cmd, ...);
int kill(pid_t pid, int signal);
int link(const char * filename1, const char * filename2);
int lseek(int fildes, off_t offset, int origin);
int mknod(const char * filename, mode_t mode, dev_t dev);
int mount(const char * specialfile, const char * dir, int rwflag);
int nice(int val);
int open(const char * filename, int flag, ...);
int pause(void);
int pipe(int * fildes);
int read(int fildes, char * buf, off_t count);
int setpgrp(void);
int setpgid(pid_t pid,pid_t pgid);
int setuid(uid_t uid);
int setgid(gid_t gid);
void (*signal(int sig, void (*fn)(int)))(int);
int stat(const char * filename, struct stat * stat_buf);
int fstat(int fildes, struct stat * stat_buf);
int stime(time_t * tptr);
int sync(void);
time_t time(time_t * tloc);
time_t times(struct tms * tbuf);
int ulimit(int cmd, long limit);
mode_t umask(mode_t mask);
int umount(const char * specialfile);
int uname(struct utsname * name);
int unlink(const char * filename);
int ustat(dev_t dev, struct ustat * ubuf);
int utime(const char * filename, struct utimbuf * times);
pid_t waitpid(pid_t pid,int * wait_stat,int options);
pid_t wait(int * wait_stat);
int write(int fildes, const char * buf, off_t count);
int dup2(int oldfd, int newfd);
int getppid(void);
pid_t getpgrp(void);
pid_t setsid(void);

#define __always_inline inline __attribute__((always_inline))

#endif
