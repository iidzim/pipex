/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:36:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/19 20:14:06 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int print_err(char *msg, char *cmd, int i)
{
	if (cmd && i == 1)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": *No such file or directory\n", 28);
		exit(1);
	}
	else if (cmd && i == 2)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": *command not found\n", 21);
	}
	else
	{
		write(2, msg, ft_strlen(msg));
		exit(1);
	}
	return (0);
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

char	*get_cmd_name(char	*s)
{
	int		i;
	int		is_absol_path;
	char	*cmd_name;

	i = 0;
	is_absol_path = 0;
	cmd_name = ft_strdup("");
	while (s[i] != '\0' && s[i] != 32)
	{
		if (s[i] == '/')
			is_absol_path = 1;
		cmd_name = ft_joinchar(cmd_name, s[i]);
		i++;
	}
	if (is_absol_path == 1 && access(cmd_name, R_OK))
		return (NULL);
	return (cmd_name);
}

char	*is_valid_cmd(char *cmd, char **env)
{
	char	*path;
	char	**path_var;
	char	*cmd_name;
	int		i;

	path_var = get_path(env);
	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (NULL);
	if (ft_strrchr(cmd_name, '/') && !access(cmd_name, R_OK))
		return (cmd_name);
	if (ft_strrchr(cmd_name, '/') && access(cmd_name, R_OK))
		return (NULL);
	i = -1;
	while (path_var[++i])
	{
		path = ft_strdup(path_var[i]);
		path = ft_strjoin(ft_strjoin(path, "/"), cmd_name);
		// printf("f:is_valid_cmd\tpath = [%s]\n", path);
		if (!access(path, R_OK))
			return (path);
		free(path);
	}
	print_err(NULL, cmd_name, 2);
	return (NULL);
}

int exec_cmd1(t_cmd *c, char **env, int fd[2])
{
	c->fd1 = open(c->f1, O_RDONLY);
	if (c->fd1 < -1)
		return (print_err("error while opening the file 1\n", NULL, 0));
	c->path_cmd1 = is_valid_cmd(c->cmd1, env);
	if (!c->path_cmd1)
		exit (1);
	// printf("f:exec_cmd1\tcmd1[%s]\n", c->cmd1);
	// printf("f:exec_cmd1\tpath_cmd1[%s]\n", c->path_cmd1);
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(c->fd1, 0);
	close(fd[1]);
	execve(c->path_cmd1, &c->cmd1, env);
	close(c->fd1);
	return (0);
}

int exec_cmd2(t_cmd *c, char **env, int fd[2])
{
	c->fd2 = open(c->f2, O_CREAT | O_WRONLY);
	if (c->fd2 < -1)
		return (print_err("error while opening the file 2\n", NULL, 0));
	c->path_cmd2 = is_valid_cmd(c->cmd2, env);
	if (!c->path_cmd2)
		exit(127);
	// printf("f:exec_cmd2\t[%s]\n", c->cmd2);
	// printf("f:exec_cmd2\tpath_cmd2[%s]\n", c->path_cmd2);
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(c->fd2, 1);
	close(fd[0]);
	execve(c->path_cmd2, &c->cmd2, env);
	close(c->fd2);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1, pid2;

	if (argc != 5)
		return (print_err("pipex: syntax error\n", NULL, 0));
	t_cmd c = {.f1 = argv[1], .f2 = argv[4], .cmd1 = argv[2],
		.cmd2 = argv[3], .ret_val = 0};
	// printf("argv[1] = [%s]\nargv[2] = [%s]\nargv[3] = [%s]\nargv[4] = [%s]\n",
	// 	c.f1, c.cmd1, c.cmd2, c.f2);
	if (access(c.f1, R_OK))
		return (print_err(NULL, c.f1, 1));
	if (pipe(fd) == -1)
		return (print_err("Pipe : fail\n", NULL, 0));
	pid1 = fork();
	if (pid1 < 0)
		return (print_err("Fork : fail\n", NULL, 0));
	else if (pid1 == 0) // child process
		exec_cmd1(&c, env, fd);
	pid2 = fork();
	if (pid2 < 0)
		return (print_err("Fork : fail\n", NULL, 0));
	else if (pid2 == 0)
	{
		wait(NULL);
		exec_cmd2(&c, env, fd);
	}
	// printf("file1 = [%s]\nfile2 = [%s]\ncmd1 = [%s]\ncmd2 = [%s]\n", c.f1, c.f2, c.cmd1, c.cmd2);
	return (0);
}
