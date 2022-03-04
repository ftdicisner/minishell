/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:02:52 by dicisner          #+#    #+#             */
/*   Updated: 2022/01/24 18:45:56 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Pipe() and sharing data between processes
int test()
{
	int fd[2]; // f[0] read, f[1] write

	if (pipe(fd) != -1) {
		int id = fork();

		// Child process
		if (id == 0) 
		{
			int x;
			close(fd[0]);
			printf("Input a number: ");
			scanf("%d", &x);
			write(fd[1], &x, sizeof(int));
			close(fd[1]);
		}
		// Parente process
		else {
			int y;
			close(fd[1]);
			read(fd[0], &y, sizeof(y));
			printf("Received from child process %d\n", y);
			close(fd[0]);
		}
	}
	return (0);
}

// Fork and wait
// int main()
// {
// 	int id = fork();

// 	if (id == 0)
// 	{
// 		printf("Waiting for the child process to finish...\n");
// 		sleep(1);
// 	}
// 	printf("Process id %d\n", getpid());

// 	int res = wait(NULL);
// 	if (res == -1) {
// 		printf("There was a problem waiting for this process\n");
// 	}
// 	else {
// 		printf("Child process execution terminated\n");
// 	}

// 	return (0);
// }