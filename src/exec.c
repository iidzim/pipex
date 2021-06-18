/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:06:09 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/18 18:38:06 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_file(t_cmd *cmd)
{
	cmd->fd1 = open(cmd->file1, O_RDONLY);
	if (cmd->fd1 < -1)
		print_err("error while opening the file 1\n");
	cmd->fd2 = open(cmd->file2, O_CREAT | O_WRONLY);
	if (cmd->fd2 < -1)
		print_err("error while opening the file 2\n");
}

int execute(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];
	char	*buf = NULL;

	(void)cmd;
	if (pipe(fd) == -1)
	{
		write(2, "Pipe Failed\n", 12);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		write(2, "Fork Failed\n", 12);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("fd[0] = %d - fd[1]= %d\n", fd[0], fd[1]);
		printf("child processes\n");
		close(fd[1]);
		read(fd[0], buf, 17);
		close(fd[0]);
	}
	else
	{
		printf("parent processes\n");
		close(fd[0]);
		write(fd[1], "hello child\n", 12);
		close(fd[1]);
		wait(NULL);
	}
	// open_file(cmd);
	// dup2(cmd->fd1, 0);
	return (0);
}

// ? 1. Before calling `fork()` the parent creates a pipe object by calling pipe().
// ? 2. Next, it calls `fork()`.
// ? 3. After `fork()` the parent closes its copy of the read-only end and the child closes its copy of the write-only end.
// ? 4. Now the parent can pass information to the child.
