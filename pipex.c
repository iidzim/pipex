/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:08:54 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/15 20:24:24 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse(char **argv, char **env)
{
	int fd1, fd2;

	// file1
	if (argv[1] && !access(argv[1], F_OK))
	{
		fd1 = open(argv[1], O_RDONLY, 0444);
		if (fd1 < -1)
			return (1);
	}
	else
	{
		printf("pipex: %s: No such file or directory\n", argv[1]);
		exit (1);
	}
	// cmd1
	// cmd2
	// file2
	if (argv[4])
		fd2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
		if (fd2 < -1)
			return (1);
	
}

int	main(int argc, char **argv, char **env)
{

	if (argc == 5)
	{
		parse(argv, env);
		execute();
	}
	else
	{
		printf("pipex: invalid argument\n");
		exit(1);
	}
	return (0);
}

//TODO
//* command:   < file1 cmd1 | cmd2 > file2
//? ./pipex file1 "cmd1" "cmd2" file2

// printf("error = %s\n", strerror(errno));
// perror("Error: ");

// check cmd path else cmd not found
// check if the file exists (<)
// n