#include "../inc/cub3d.h"

static void	siginfo_handler(int sig, siginfo_t *info, void *context);

void	setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = siginfo_handler;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

static void	siginfo_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
	/*	write(1, "\n", 1);
		exit(EXIT_SUCCESS);*/
		printf("\nSIGINT received. Graceful exit not implemented yet.\n");
		// later when we have x to quit we are going to ignore SIGINT during gameplay
		// and only allow it to quit when in main menu
	}
}