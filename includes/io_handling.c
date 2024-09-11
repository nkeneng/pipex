/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:39:45 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 18:55:19 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_input(char *argv[], int i, int **pipes)
{
	int	infile;

	if (i != 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	else
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
			infile = open("/tmp/heredoc_tmp", O_RDONLY);
		else
			infile = open(argv[1], O_RDONLY);
		if (infile < 0)
		{
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
}

void	handle_output(char *argv[], int i, int num_cmds, int **pipes)
{
	int	outfile;
	int	ac;

	ac = ft_strslen(argv);
	if (i != num_cmds - 1)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
			outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
		{
			perror(argv[4]);
			exit(EXIT_FAILURE);
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}
