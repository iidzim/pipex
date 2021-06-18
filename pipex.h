/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:09:34 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/18 21:50:33 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>


typedef struct  s_cmd
{
	char    *file1; //!
	char    *f1;
	int     fd1;//!
	char    *file2;//!
	char    *f2;
	int     fd2;//!
	char    *cmd1;
	char    *path_cmd1;
	char    *cmd2;
	char    *path_cmd2;
	char    *path;//!
}               t_cmd;

typedef struct s_cmd
{
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*path_cmd1;
	char	*cmd2;
	char	*path_cmd2;
}

/*
** utils
*/
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, const char *s2);
char	*ft_joinchar(char *s, char c);
int     ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
size_t  ft_strlen(const char *s);


int execute(t_cmd *cmd);

#endif
