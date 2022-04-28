/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:02:52 by dicisner          #+#    #+#             */
/*   Updated: 2022/04/27 20:15:49 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// Pipe() and sharing data between processes
// int test()
// {
// 	int fd[2]; // f[0] read, f[1] write

// 	if (pipe(fd) != -1) {
// 		int id = fork();

// 		// Child process
// 		if (id == 0) 
// 		{
// 			int x;
// 			close(fd[0]);
// 			printf("Input a number: ");
// 			scanf("%d", &x);
// 			write(fd[1], &x, sizeof(int));
// 			close(fd[1]);
// 		}
// 		// Parente process
// 		else {
// 			int y;
// 			close(fd[1]);
// 			read(fd[0], &y, sizeof(y));
// 			printf("Received from child process %d\n", y);
// 			close(fd[0]);
// 		}
// 	}
// 	return (0);
// }
void executor_test()
{
	int cmds = 2; // numero de comandos
	int isChild = 0;

	int fd1[2];
	int fd2[2];

	if (pipe(fd1) == -1)
		printf("Error al crear el pipe");
	if (pipe(fd2) == -1)
		printf("Error al crear el pipe");

	for (int i = 0; i < cmds ; i++) 
	{
		if (!isChild)
		{
			int id = fork();

			if (id == 0)
			{
				if (i == 0){
					dup2(fd1[1], 1);
					printf("Executando el comando %d...\n", i);
					// isChild = 1;
					// sleep(1);
					exit(0);
				}
				if (i == 1) {
					dup2(fd1[0], 0);
					dup2(fd2[1], 1);

					// We need to close from the pipe we are going to read
					close(fd1[1]);

					int bsize = 256;
					char buf[bsize+1];
					ssize_t n = 0;
					while ((n = read(0, buf, bsize)) > 0) {
						buf[n] = '\0';
						write(1, buf, n);
					}

					printf("Executando el comando %d...\n", i);
					// isChild = 1;
					// sleep(1);
					exit(0);
				}
			}
		}
	}
	if (!isChild)
	{
		close(fd2[1]);
		close(fd1[1]);
		
		int bsize = 256;
		char buf[bsize+1];
		ssize_t n = 0;
		while ((n = read(fd2[0], buf, bsize)) > 0) {
			buf[n] = '\0';
			write(1, buf, n);
		}
		close(fd2[0]);
		wait(NULL);
	}
	printf("-->End\n");
}

// Fork and wait
int main()
{
	executor_test();
	/// Logic
	printf("additional\n");
	return (0);
}