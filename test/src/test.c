#include "libftprintf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE (8 << 15) /* 32KB */
#endif
#define ERROR(fmt, args...) fprintf(stderr, fmt, ##args)
#define FATAL_ERROR(fmt, args...) \
	ERROR(fmt, ##args); \
	exit(1);
#define LOG(fmt, args...) dprintf(stdout_backup, fmt, ##args)

// reference: https://stackoverflow.com/a/35249468

int	main(int argc, char *argv[])
{
	char	str_got[BUFFER_SIZE + 1];
	char	str_want[BUFFER_SIZE + 1];
	int		bonus;
	int		fail_cnt;
	int		i;
	int		pipe_fds[2];
	int		res_ok;
	int		ret_got;
	int		ret_ok;
	int		ret_want;
	int		stdout_backup;
	int		tests_cnt;
	ssize_t	read_cnt;

	bonus = 0;
	i = 1;
	while (i < argc && bonus == 0)
	{
		if (strcasecmp("-bonus", argv[i]) == 0)
			bonus = 1;
		i++;
	}

	tests_cnt = 0;
	fail_cnt = 0;
#define TEST(fmt, args...) { \
	stdout_backup = dup(fileno(stdout)); /* backup the stdout fd */ \
	if (pipe(pipe_fds) == -1) { /* initialize pipe */ \
		FATAL_ERROR("failed to create pipe\n"); \
	} \
	if (dup2(pipe_fds[1], fileno(stdout)) == -1) { /* copy stdout fd to pipe write end */ \
		FATAL_ERROR("failed to copy stdout to the pipe\n"); \
	} \
	ret_want = sprintf(str_want, fmt, ##args); \
	ret_got = ft_printf(fmt, ##args); \
	fflush(stdout); /* flush out the stdout buffer */ \
	close(pipe_fds[1]); /* close the pipe write end */ \
	if (dup2(stdout_backup, fileno(stdout)) == -1) { /* restore stdout */ \
		ERROR("failed to restore the stdout\n"); \
	} \
	read_cnt = read(pipe_fds[0], str_got, BUFFER_SIZE); /* read from pipe_fds */ \
	if (read_cnt == -1) { \
		FATAL_ERROR("failed to read from pipe\n"); \
	} \
	str_got[read_cnt] = '\0'; /* nul byte termination */ \
	ret_ok = ret_got == ret_want; \
	res_ok = strcmp(str_want, str_got) == 0; \
	tests_cnt++; \
	if (!ret_ok || !res_ok) { \
		fail_cnt++; \
		if (fail_cnt > 1) { \
			LOG("\n"); \
		} \
		LOG("Test #%d has failed (line %d):\n", tests_cnt, __LINE__); \
	} \
	if (!res_ok) { \
		LOG("unexpected result\n\twanted: \"%s\"\n\t   got: \"%s\"\n", str_want, str_got); \
	} \
	if (!ret_ok) { \
		LOG("unexpected return value\n\twanted: %d\n\t   got: %d\n", ret_want, ret_got); \
	} \
	close(pipe_fds[0]); /* close pipe read end */ \
}

	// simple tests:
	TEST("");
	TEST("lorem ipsum");
	TEST("\tlorem\n\tipsum\n");
	TEST("%c", 'a');
	TEST("alpha: %c\nbravo: %c\ncharlie: %c", 'a', 'b', 'c');
	TEST("%s", "\tlorem ipsum\n");
	TEST("\tlorem %s\n", "ipsum");
	TEST("%p", NULL);
	TEST("%p", (void *)1234567890);
	TEST("\talpha: %p\n\tbravo:%p\n", NULL, (void *)1234567890);
	TEST("%d", 0);
	TEST("%d", 42);
	TEST("%d", 1234567890);
	TEST("%d", -1234567890);
	TEST("\tfoo: %d\n\tbar: %d\n", 42, 1234567890);
	TEST("%i", 0);
	TEST("%i", 42);
	TEST("%i", 1234567890);
	TEST("%i", -1234567890);
	TEST("\tfoo: %i\n\tbar: %i\n", 42, 1234567890);
	TEST("%u", 0);
	TEST("%u", 42);
	TEST("%u", 57005);
	TEST("\tfoo: %u\n\tbar: %u\n", 42, 57005);
	TEST("%x", 0);
	TEST("%x", 42);
	TEST("%x", 57005);
	TEST("\tfoo: %x\n\tbar: %x\n", 42, 57005);
	TEST("%X", 0);
	TEST("%X", 42);
	TEST("%X", 57005);
	TEST("\tfoo: %X\n\tbar: %X\n", 42, 57005);
	TEST("%%");
	TEST("\t100%% eru iluvatar\n\t0%% marion aulendil\n");

	if (bonus)
	{
		// bonus tests:
		// c specifier tests:
		TEST("%c", 'a');
		TEST("%1c", 'a');
		TEST("%10c", 'a');
		TEST("%-10c", 'a');
		// d specifier tests:
		TEST("%d", -1234567890);
		TEST("%1d", -1234567890);
		TEST("%10d", -1234567890);
		TEST("%20d", -1234567890);
		TEST("%-1d", -1234567890);
		TEST("%-10d", -1234567890);
		TEST("%-20d", -1234567890);
		TEST("%020d", -1234567890);
		TEST("%-020d", -1234567890);
		TEST("%.20d", -123456790);

		TEST("%d %p", 42, NULL);
		TEST("%d %d %d", 10, 20, 30);
		TEST("%d %d %d", 10, 20, 30);
		TEST("%d %s %d", 10, "foobaru", 20);
		TEST("%s", "lorem ipsum");
		TEST("%s", "%.#deliberate_FATAL_ERROR");
	}

	LOG("%d/%d tests have succeeded\n", tests_cnt - fail_cnt, tests_cnt);

	if (fail_cnt == 0)
		return (0);
	return (1);
}
