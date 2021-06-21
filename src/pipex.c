/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:36:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/21 20:15:37 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_err(char *msg, char *cmd)
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
			break ;
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

char	*ft_joinchar(char *s, char c)
{
	int		i;
	char	*str;

	i = strlen(s);
	str = (char *)malloc(i + 2);
	if (!str)
		return (0);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
