#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	ft_read(int fd)
{
	int bsize = 256;
	char buf[bsize+1];
	ssize_t n = 0;
	while ((n = read(fd, buf, bsize)) > 0) {
		buf[n] = '\0';
		write(1, buf, n);
	}
}

int ft_pipe(int *fd)
{
	pipe(fd);
	return (0);
}

int **init_pipes(int n)
{
	int **fds;
	int i;

	fds = malloc(sizeof (int *) * n);
	i = 0;
	while (i < n)
	{
		fds[i] = malloc(sizeof (int) * 2);
		i++;
	}
	i = 0;
	while (i < n)
	{
		ft_pipe(fds[i]);
		i++;
	}
	return fds;
}

void	close_pipes(int **pipes, int n)
{
	int i;

	i = 0;
	while (i < n + 1)
	{
		// printf("Closing pipes %i\n", i);
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int main(int argc, char* argv[], char **env) {
	int n = 2;
    int **pipes = init_pipes(n + 1);


	char *newenviron[] = { NULL };
	char cmd[] = "/bin/ping";
	char *newargv[] = { cmd, "-c", "1", "google.com" };
    
    int pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }

	int i = 0;
    
    if (pid1 == 0) {
        // Child process 1 (ping)
        dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(pipes, n);
		execve(cmd, newargv, newenviron);
		exit(0);
        // execlp("ping", "ping", "-c", "1", "google.com", NULL);
    }

    waitpid(pid1, NULL, 0);
    
    int pid2 = fork();
    if (pid2 < 0) {
        return 3;
    }
    
    if (pid2 == 0) {
        // Child process 2 (grep)
        dup2(pipes[i][0], STDIN_FILENO);
		dup2(pipes[i + 1][1], STDOUT_FILENO);
		close_pipes(pipes, n);
        execlp("grep", "grep", "rtt", NULL);
		exit(0);
    }

	dup2(pipes[i + 1][0], 0);
	close_pipes(pipes, n);
	waitpid(pid2, NULL, 0);
	ft_read(0);

	// 	int bsize = 256;
	// char buf[bsize+1];
	// ssize_t n = 0;
	// while ((n = read(fd, buf, bsize)) > 0) {
	// 	buf[n] = '\0';
	// 	write(1, buf, n);
	// }
    
    return 0;
}