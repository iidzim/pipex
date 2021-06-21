/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:36:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/21 11:59:55 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void print_err(char *msg, char *cmd)
{
	if (cmd)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	else
	{
		write(2, msg, ft_strlen(msg));
		exit(1);
	}
}

char	**get_path(char **env)
{
	char	**path;
	char	**env_var;
	int		i;

	i = -1;
	while (env[++i])
	{
		env_var = ft_split(env[i], '=');
		if (!ft_strcmp(env_var[0], "PATH"))
			break;
	}
	path = ft_split(env_var[1], ':');
	return (path);
}

char	*is_valid_cmd(char **cmd, char **env)
{
	char	*path;
	char	**path_var;
	char	*cmd_name;
	int		i;

	path_var = get_path(env);
	cmd_name = cmd[0];
	if (ft_strrchr(cmd_name, '/') && !access(cmd_name, R_OK))
		return (cmd_name);
	if (ft_strrchr(cmd_name, '/') && access(cmd_name, R_OK))
		return (NULL);
	i = -1;
	while (path_var[++i])
	{
		path = ft_strdup(path_var[i]);
		path = ft_strjoin(ft_strjoin(path, "/"), cmd_name);
		if (!access(path, R_OK))
			return (path);
		free(path);
	}
	print_err(NULL, cmd_name);
	return (NULL);
}

void exec_cmd1(t_cmd *c, char **env, int pipe[2])
{
	c->fd1 = open(c->f1, O_RDONLY);
	if (c->fd1 < -1)
	{
		perror("file1: ");
		exit(1);
	}
	c->path_cmd1 = is_valid_cmd(c->cmd1, env);
	if (c->path_cmd1 == NULL)
		exit (1);
	close(pipe[0]);
	dup2(pipe[1], 1);
	dup2(c->fd1, 0);
	close(pipe[1]);
	execve(c->path_cmd1, c->cmd1, env);
	close(c->fd1);
}

void exec_cmd2(t_cmd *c, char **env, int pipe[2])
{
	c->fd2 = open(c->f2, O_CREAT | O_WRONLY);
	if (c->fd2 < -1)
	{		
		perror("file2: ");
		exit(1);
	}
	c->path_cmd2 = is_valid_cmd(c->cmd2, env);
	if (c->path_cmd2 == NULL)
		exit(127);
	close(pipe[1]);
	dup2(pipe[0], 0);
	dup2(c->fd2, 1);
	close(pipe[0]);
	execve(c->path_cmd2, c->cmd2, env);
	close(c->fd2);
}

// ./pipex Makefile cat ls file2
// ./pipex pipex.h ls "cat -e"  file2
//  ./pipex makefile cat "grep void" file2
// < makefile sleep 500 | echo hey > bash

int main(int argc, char **argv, char **env)
{
	int		fd_pipe[2];
	pid_t	pid1, pid2;
	int status_ptr;

	if (argc != 5)
		print_err("pipex: syntax error\n", NULL);
	t_cmd c = {.f1 = argv[1], .f2 = argv[4], .cmd1 = ft_split(argv[2], 32),
		.cmd2 = ft_split(argv[3], 32), .ret_val = 0};
	if (access(c.f1, F_OK) || access(c.f1, R_OK))
	{
		perror("pipex: ");
		exit(1);
	}
	if (pipe(fd_pipe) == -1)
		print_err("Pipe : fail\n", NULL);
	pid1 = fork();
	if (pid1 < 0)
		print_err("Fork : fail\n", NULL);
	else if (pid1 == 0)
		exec_cmd1(&c, env, fd_pipe);
	pid2 = fork();
	if (pid2 < 0)
		print_err("Fork : fail\n", NULL);
	else if (pid2 == 0)
		exec_cmd2(&c, env, fd_pipe);
	// waitpid(pid1,&status_ptr,0);
	waitpid(pid2,&status_ptr,0);
	if (WIFEXITED(status_ptr))
		exit(WEXITSTATUS(status_ptr));
	// if (WIFEXITED(status_ptr))
		// exit(WIFEXITED(status_ptr));
	// system("leaks pipex");
	return (0);
}

// page 538