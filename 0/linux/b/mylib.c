#define __LIBRARY__
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define	EINVAL	4

extern char ** environ;
#define	__environ	environ

char * ___strtok;
volatile int errno;

_syscall0(int,sync)
_syscall0(int,fork)
_syscall1(int,close,int,fildes)
_syscall1(int,setup,void *,BIOS)
_syscall1(int,chdir,const char *,filename)
_syscall3(int,write,int,fd,const char *,buf,off_t,count)
_syscall3(pid_t,waitpid,pid_t,pid,int *,wait_stat,int,options)
_syscall3(int,read,int,fd,char *,buf,off_t,count)
_syscall3(int,execve,const char *,file,char **,argv,char **,envp)


void * memcpy(void * dest,const void * src, int n)
{
__asm__("cld\n\t"
	"rep\n\t"
	"movsb"
	::"c" (n),"S" (src),"D" (dest)
	);
return dest;
}

int strlen(const char * s)
{
register int __res ;
__asm__("cld\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %0\n\t"
	"decl %0"
	:"=c" (__res):"D" (s),"a" (0),"0" (0xffffffff));
return __res;
}

volatile void exit(int exit_code)
{
	__asm__("int $0x80"::"a" (__NR_exit),"b" (exit_code));
	while(1); /* to avoid warning of compiler */
}

extern char _end;
void * ___brk_addr = &_end;

int brk(void * end_data_segment)
{
	long __res;
	__asm__ volatile ("int $0x80"
		: "=a" (__res)
		: "0" (__NR_brk),"b" ((long)(end_data_segment)));
	if (__res >= 0) {
		___brk_addr = end_data_segment;
		return (int) __res;
	}
	errno = -__res;
	return -1;
}

void * sbrk(ptrdiff_t increment)
{
	char *oldbrk;

	if (increment == 0)
		return ___brk_addr;

	oldbrk = ___brk_addr;
	if (brk(oldbrk + increment) < 0)
		return (char *) -1;

	return oldbrk;
}

/* Return the value of the environment variable NAME.  */
char * getenv(register const char *name)
{
  register const size_t len = strlen(name);
  register char **ep;

  for (ep = __environ; *ep != NULL; ++ep)
    if (!strncmp(*ep, name, len) && (*ep)[len] == '=')
      return &(*ep)[len + 1];

  return NULL;
}

pid_t wait(int * wait_stat)
{
	return waitpid(-1, wait_stat, 0);
}

int printf(const char *fmt, ...)
{
	return write(1, fmt, strlen(fmt));
}

void work_dirname(char* dirname, char* part)
{
	int i;
	int len = strlen(dirname);
	if (strcmp(part, ".") == 0)
		return;
	if (strcmp(part, "..") == 0)
		for (i = len - 1; i >= 0; i--)
			if (dirname[i] == '/')
			{
				dirname[i] = '\0';
				return;
			}
	for (i = len + 1; part[i - len - 1] != '\0'; i++)
		dirname[i] = part[i - len - 1];
	dirname[len] = '/';
	dirname[i] = '\0';
	return;
}

void change_dirname(char* dirname, char* path)
{
	char* p;
	char* part[80];
	int count = 0;
	int i;
	p = strtok(path, "/");
	while (p) 
	{
		part[count] = p;
		p = strtok(NULL, "/");
		count++;
	}
	part[count] = NULL;
	for (i = 0; i < count; i++)
		work_dirname(dirname, part[i]);
	return;
}

int open(const char * filename, int flag, ...)
{
	register int res;
	va_list arg;
	long __res;
	va_start(arg,flag);
	__asm__ volatile("int $0x80"
		:"=a" (__res)
		:"0" (__NR_open),"b" (filename),"c" (flag),
		"d" (va_arg(arg,int)));
	if (__res>=0)
		return (int)__res;
	errno = -__res;
	return -1;
}