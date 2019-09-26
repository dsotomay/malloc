
// #include "ft_malloc.h"
// #include <stdio.h>
// int main()
// {
// 	char *str1[1000];
// 	// struct block_meta *new;
// 	for (int i = 0; i < 1000; i++)
// 		str1[i] = malloc(sizeof(char) * 1000);
// 	char *str2 = malloc(sizeof(char) * 13);
// 	// char *str2 = malloc(sizeof(char) * 24);
// 	// str = (char*)mmap(0, psize, PROT_READ | PROT_WRITE,
// 	// MAP_ANON | MAP_PRIVATE, -1, 0);
// 	// _MMAP()
// 	strcat(str2, "hello world!");
// 	// printf("%s, %p\n", str2, str2);
// 	strcat(str1[0], "hello world!this is going to overwriteksjhdfkgjhs");
// 	printf("%s, %p\n", str1[0], (t_block*)str1[0] - 1);
// 	free(str1[0]);
// 	str1[0] = malloc(sizeof(char) * 1000);
// 	// printf("%s, %p\n", str1[0], (t_block*)str1[0] - 1);
// 	// printf("%s, %p\n", str1[0], str1[0]);
// 	// strcat(str1[99], "hello world!this is going to overwriteksjhdfkgjhs");
// 	// printf("%p\n", (((t_block*)str1[99])-1));
// 	void *tmp = malloc(-1);
// 	show_alloc_mem();
// 	// void *new1 = (void*)str2;
// 	// new = (struct block_meta*)new1 - 1;
// 	// printf("%c\n", (char)new->next);
// 	// printf("%c\n", (char)new->next);
// 	// printf("%s\n", (char*)new);
// 	// free(str2);
// 	// printf("%s\n", (char*)new);
// 	// munmap(str, psize);
// 	// strcpy(str, "hello world!\n");
// 	// printf("%s", str);
// 	// printf("%p\n", str);
// }

#include "ft_malloc.h"
#include <limits.h>
#include <stdarg.h>

/* TODO: split each test type in to separate files */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int errors = 0;

static void
merror (const char *msg)
{
	++errors;
	printf ("Error: %s\n", msg);
}


int
do_realloc_tests (void)
{
	void *p;
	unsigned char *c;
	int save, i, ok;

	errno = 0;
	
	/* realloc (NULL, ...) behaves similarly to malloc (C89).  */
	#pragma clang diagnostic push
	/* GCC 7 warns about too-large allocations; here we want to test
		that they fail.  */
	p = realloc (NULL, -1);
	#pragma clang diagnostic pop
	save = errno;
	
	if (p != NULL)
	merror ("realloc (NULL, -1) succeeded.");
	
	// /* errno should be set to ENOMEM on failure (POSIX).  */
	// printf("%i\n", save);
	// if (p == NULL && save != ENOMEM)
	// 	merror ("errno is not set correctly");


	errno = 0;
	
	/* realloc (NULL, ...) behaves similarly to malloc (C89).  */
	p = realloc (NULL, 10);
	save = errno;


	if (p == NULL)
		merror ("realloc (NULL, 10) failed.");

	free (p);

	p = calloc (20, 1); //need to check weird things that happen here
	if (p == NULL)
		merror ("calloc (20, 1) failed.");

	/* Check increasing size preserves contents (C89).  */
	p = realloc (p, 200);
	if (p == NULL)
		merror ("realloc (p, 200) failed.");

	c = p;
	ok = 1;

	for (i = 0; i < 20; i++)
	{
		if (c[i] != 0)
			ok = 0;
	}

	if (ok == 0)
		merror ("first 20 bytes were not cleared");

	free (p);

	p = realloc (NULL, 100);
	if (p == NULL)
		merror ("realloc (NULL, 100) failed.");

	memset (p, 0xff, 100);

	/* Check decreasing size preserves contents (C89).  */
	p = realloc (p, 16);
	if (p == NULL)
		merror ("realloc (p, 16) failed.");

	c = p;
	ok = 1;

	for (i = 0; i < 16; i++)
	{
		if (c[i] != 0xff)
			ok = 0;
	}

	if (ok == 0)
		merror ("first 16 bytes were not correct");

	/* Check failed realloc leaves original untouched (C89).  */
	#pragma clang diagnostic push
	/* GCC 7 warns about too-large allocations; here we want to test
		that they fail.  */
	c = realloc (p, -1);
	#pragma clang diagnostic pop
	if (c != NULL)
		merror ("realloc (p, -1) succeeded.");

	c = p;
	ok = 1;

	for (i = 0; i < 16; i++)
	{
		if (c[i] != 0xff)
			ok = 0;
	}

	if (ok == 0)
		merror ("first 16 bytes were not correct after failed realloc");
	
	/* realloc (p, 0) frees p (C89) and returns NULL (glibc).  */
	p = realloc (p, 0);
	if (p == NULL)
		merror ("realloc (p, 0) returned NULL.");

	/* realloc (NULL, 0) acts like malloc (0) (glibc).  */
	p = realloc (NULL, 0);
	if (p != NULL)
		merror ("realloc (NULL, 0) didn't return NULL.");

	free (p);

	return errors != 0;
}

int
basic_tests(void)
{
	void *p, *q;
	int save;

	errno = 0;

#pragma clang diagnostic push
	p = malloc (-1);
#pragma clang diagnostic pop
	save = errno;

	if (p != NULL)
		merror ("malloc (-1) succeeded.");
		
	// if (p == NULL && save != ENOMEM)
	// 	merror ("errno is not set correctly");

	p = malloc (10);
	if (p == NULL)
		merror ("malloc (10) failed.");

	/* realloc (p, 0) == free (p).  */
	p = realloc (p, 0);
	if (p == NULL)
		merror ("realloc (p, 0) failed.");

	p = malloc (0);
	if (p != NULL)
		merror ("malloc (0) failed.");

	p = realloc (p, 0);
	if (p != NULL)
		merror ("realloc (p, 0) failed.");

	p = malloc (513 * 1024);
	if (p == NULL)
		merror ("malloc (513K) failed.");

#pragma clang diagnostic push
	q = malloc (-512 * 1024);
#pragma clang diagnostic pop
	if (q != NULL)
		merror ("malloc (-512K) succeeded.");
		
	free (p);

	return errors != 0;
}

char *program_name;

extern void error (int status, int errnum, const char *message, ...)
	__attribute__ ((__format__ (__printf__, 3, 4)));
	
static void
print_errno_message (int errnum)
{
	char const *s;
	s = strerror (errnum);
	if (! s)
		s = "Unknown system error";
	fprintf (stderr, ": %s", s);
}

static void
error_tail (int status, int errnum, const char *message, va_list args)
{
	vfprintf (stderr, message, args);
	va_end (args);
	if (errnum)
		print_errno_message (errnum);
	fputc ('\n', stderr);
	fflush (stderr);
	if (status)
		exit (status);
}

void
__error_internal(int status, int errnum, const char *message,
		va_list args)
{
	fflush (stdout);
	fprintf (stderr, "%s: ", program_name);
	error_tail (status, errnum, message, args);
}

void
error (int status, int errnum, const char *message, ...)
{
	va_list ap;
	va_start (ap, message);
	__error_internal (status, errnum, message, ap);
	va_end (ap);
}

/* Number of samples per size.  */
#define N 50000

static void
fixed_test (int size)
{
	char *ptrs[N];
	int i;
	
	for (i = 0; i < N; ++i)
	{
		int j;

		ptrs[i] = (char *) calloc (1, size);
		
		if (ptrs[i] == NULL) {
			fprintf (stderr, "fixed_test ptrs[%d] == NULL, for size %d\n", i, size);
			break;
		}

		for (j = 0; j < size; ++j)
		{
			if (ptrs[i][j] != '\0')
				error (EXIT_FAILURE, 0,
					"byte not cleared (size %d, element %d, byte %d)",
					size, i, j);
			ptrs[i][j] = '\xff';
		}
	}

	while (i-- > 0)
		free (ptrs[i]);
}


static void
random_test (void)
{
	char *ptrs[N];
	int i;

	for (i = 0; i < N; ++i)
	{
		int j;
		int n = 1 + random () % 10;
		int elem = 1 + random () % 100;
		int size = n * elem;

		ptrs[i] = (char *) calloc (n, elem);

		if (ptrs[i] == NULL) {
			fprintf (stderr, "random_test ptrs[%d] == NULL, for size %d\n", i, size);
			break;
		}

		for (j = 0; j < size; ++j)
		{
			if (ptrs[i][j] != '\0')
			error (EXIT_FAILURE, 0,
				"byte not cleared (size %d, element %d, byte %d)",
				size, i, j);
			ptrs[i][j] = '\xff';
		}
	}

	while (i-- > 0)
		free (ptrs[i]);
}


static void
null_test (void)
{
  /* If the size is 0 the result is implementation defined.  Just make
	 sure the program doesn't crash.  The result of calloc is
	 deliberately ignored, so do not warn about that.  */
#pragma clang diagnostic push
	// DIAG_PUSH_NEEDS_COMMENT;
#pragma clang diagnostic ignored "-Wunused-result"
	// DIAG_IGNORE_NEEDS_COMMENT (10, "-Wunused-result");
	calloc (0, 0);
	calloc (0, UINT_MAX);
	calloc (UINT_MAX, 0);
	calloc (0, ~((size_t) 0));
	calloc (~((size_t) 0), 0);
#pragma clang diagnostic pop
}


int
do_calloc_test (void)
{
  /* We are allocating blocks with `calloc' and check whether every
	 block is completely cleared.  We first try this for some fixed
	 times and then with random size.  */
	fixed_test (15);
	fixed_test (5);
	fixed_test (17);
	fixed_test (6);
	fixed_test (31);
	fixed_test (96);

	random_test ();

	null_test ();

	return 0;
}


int
main (void)
{
	int ret = basic_tests ();
	// ret += do_calloc_test ();
	ret += do_realloc_tests();
	void *big = malloc(1 << 31);
	if (big != NULL)
	{
		perror("malloc(1 << 31) succeeded.");
		ret++;
	}
	show_alloc_mem();
	// pause();
	return ret;
}
