/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:36:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/18 21:47:59 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int print_err(char *msg, char *cmd, int i)
{
	if (cmd && i == 1)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	else if (cmd && i == 2)
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
		if (s[i] != '/')
			is_absol_path = 1;
		cmd_name = ft_strjoin(cmd_name, s[i]);
		i++;
	}
	if (is_absol_path == 1 && access(cmd_name, R_OK))
		return (NULL);
	return (cmd_name);
}

char	*is_valid_cmd(t_cmd *c, char **env)
{
	char	**path;
	char	*cmd_name;
	int		i;

	path = get_path(env);
	cmd_name = get_cmd_name(c->cmd1);
	if (!cmd_name)
		return (NULL);
	if (!ft_strrchr(cmd_name, '/'))
		return (cmd_name);
	i = -1;
	while (path[++i])
	{
		path = ft_strdup(path[i]);
		path = ft_strjoin(ft_strjoin(path, "/"), cmd_name);
		if (!access(path, R_OK))
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}

int exec_cmd1(t_cmd *c, char **env, int fd[2])
{
	c->fd1 = open(c->f1, O_RDONLY);
	if (c->fd1 < -1)
		return (print_err("error while opening the file 1\n", NULL, 0));
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(c->fd1, 0);
	close(fd[1]);
	c->path_cmd1 = is_valid_cmd(c, env);
	if (!c->path_cmd1)
		return (print_err(NULL, c->path_cmd1, 2));
	execve(c->path_cmd1, c->cmd1, env);
	close(c->fd1);
}

int exec_cmd2(t_cmd *c, char **env, int fd[2])
{
	c->fd2 = open(c->f2, O_CREAT | O_WRONLY);
	if (c->fd2 < -1)
		return (print_err("error while opening the file 2\n", NULL, 0));
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(c->fd2, 1);
	close(fd[0]);
	c->path_cmd2 = is_valid_cmd(c, env);
	if (!c->path_cmd2)
	{
		print_err(NULL, c->path_cmd2, 2);
		exit(127);
	}
	execve(c->path_cmd2, c->cmd2, env);
	close(c->fd2);
}

int main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		return (print_err("pipex: syntax error\n", NULL, 0));
	t_cmd c = {.f1 = argv[1], .f2 = argv[4], .cmd1 = argv[2], .cmd2 = argv[3]};
	if (access(c.f1, R_OK))
		return (print_err(NULL, c.f1, 1));
	if (pipe(fd) == -1)
		return (print_err("Pipe : fail\n", NULL, 0));
	pid = fork();
	if (pid < 0)
		return (print_err("Fork : fail\n", NULL, 0));
	else if (pid == 0) // child process
		exec_cmd1(&c, env, fd);
	else // parent process
	{
		wait(NULL);
		exec_cmd2(&c, env, fd);
	}
	return (0);
}
