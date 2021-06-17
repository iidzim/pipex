/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:06:09 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/17 21:24:04 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_file(t_cmd *cmd)
{
	cmd->fd1 = open(cmd->file1, O_RDONLY, 0444);
	if (cmd->fd1 < -1)
		print_err(2, NULL);
	cmd->fd2 = open(cmd->file2, O_CREAT | O_WRONLY | O_TRUNC);
	if (cmd->fd2 < -1)
		print_err(2, NULL);
}

int execute(t_cmd *cmd)
{
	pid_t	pid1;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror('pipe');
		
	}
	pid1 = fork();
	open_file(cmd);
	dup2(cmd->fd1, 0);
	
}

// ? 1. Before calling `fork()` the parent creates a pipe object by calling pipe().
// ? 2. Next, it calls `fork()`.
// ? 3. After `fork()` the parent closes its copy of the read-only end and the child closes its copy of the write-only end.
// ? 4. Now the parent can pass information to the child.
