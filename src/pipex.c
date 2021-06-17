/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:08:54 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/17 21:31:06 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_err(int error_num, char *s)
{
	if (error_num == 127)
	{
		printf("pipex: %s: command not found\n", s);
		exit(127);
	}
	else if (error_num == 1)
	{
		printf("pipex: %s: No such file or directory\n", s);
		exit(1);
	}
	else if (error_num == 2)
		printf("error while opening the file\n");
	else if (error_num == 3)
	{
		printf("pipex: syntax error\n");
		exit(1);
	}
}

void	get_path(t_cmd *cmd, char **env)
{
	int		i;
	char	**env_var;

	i = 0;
	while (env[i])
	{
		env_var = ft_split(env[i], '=');
		if (!ft_strcmp(env_var[0], "PATH"))
		{
			cmd->path = env_var[1];
			break ;
		}
		else
			i++;
	}
}

char	*find_path(char *path, char *cmd_name)
{
	int		i;
	char	**p;
	char	*test;

	i = 0;
	p = ft_split(path, ':');
	while (p[i])
	{
		test = ft_strdup("");
		test = ft_strjoin(test, p[i]);
		test = ft_strjoin(test, "/");
		test = ft_strjoin(test, cmd_name);
		if (!access(test, R_OK))
			return (test);
		i++;
		free(test);
	}
	print_err(127, cmd_name);
	return (NULL);
}

void	get_cmd_path(char *path, char *str, t_cmd *c)
{
	int	i;
	int absolute_path;

	i = 0;
	absolute_path = 0;
	path = ft_strdup("");
	while (str[i] != '\0' && str[i] != 32)
	{
		if (str[i] == '/')
			absolute_path = 1;
		path = ft_joinchar(path, str[i]);
		i++;
	}
	printf("f:egt_cmd_path >>>> path_cmd2 = [%s] \n", c->path_cmd2);
	if (absolute_path == 1 && access(path, F_OK))
	{
		printf("in\n");	
		print_err(127, path);
	}
	else if (absolute_path == 0)
		c->path_cmd1 = find_path(c->path, path);
	else
		c->path_cmd1 = path;
}

int	parse(t_cmd *cmd, char **env)
{
	if (!cmd)
		return (0);
	if (access(cmd->file1, F_OK))
		print_err(1, cmd->file1);
	get_path(cmd, env);
	get_cmd_path(cmd->path_cmd1, cmd->cmd1, cmd);
	get_cmd_path(cmd->path_cmd2, cmd->cmd2, cmd);
	return (1);
}

// t_cmd	*init_struct(char **argv)
// {
	// t_cmd	cmd;
	// cmd = malloc(sizeof(t_cmd));
	// if (!cmd)
	// 	return (NULL);
	// t_cmd cmd = {.file1 = argv[1], .cmd1 = argv[2], .cmd2 = argv[3], .file2 = argv[4],
		// .fd1 = 0, .fd2 = 0, .path = NULL, .path_cmd1 = NULL, .path_cmd2 = NULL};
	// return (&cmd);
// }

int	main(int argc, char **argv, char **env)
{
	if (argc == 5)
	{
		t_cmd cmd = {.file1 = argv[1], .cmd1 = argv[2], .cmd2 = argv[3], .file2 = argv[4],
		.fd1 = 0, .fd2 = 0, .path = NULL, .path_cmd1 = NULL, .path_cmd2 = NULL};
		// cmd = init_struct(argv);
		parse(&cmd, env);
		printf("file1 -> [%s]\ncmd1 -> [%s]\n", cmd.file1, cmd.cmd1);
		printf("file2 -> [%s]\ncmd2 -> [%s]\n", cmd.file2, cmd.cmd2);
		// execute(cmd);
	}
	else
		print_err(3, NULL);
	return (0);
}

//TODO
//* command:   < file1 cmd1 | cmd2 > file2
//? ./pipex file1 "cmd1" "cmd2" file2

// printf("error = %s\n", strerror(errno));
// perror("Error: ");
