/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:15 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 19:23:08 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function: validate_args
 * -----------------------
 * Validates the command line arguments for the pipex program.
 *
 * @param argc The number of command line arguments.
 * @param file_here_doc A string representing the file for here document.
 *
 * @return EXIT_SUCCESS if the arguments are valid, otherwise EXIT_FAILURE.
 *
 * This function checks if the number of arguments is less than 5, and if so,
 * it prints an error message and returns EXIT_FAILURE. If the file_here_doc
 * argument is "here_doc", it checks if the number of arguments is less than 6,
 * and if so, it prints an error message and returns EXIT_FAILURE. If the
 * arguments are valid, it returns EXIT_SUCCESS.
 */
int	validate_args(int argc, char *file_here_doc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else if (ft_strncmp(file_here_doc, "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("Error: Invalid number of arguments\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * Function: handle_heredoc
 * ------------------------
 * Handles the here doc input for the pipex program.
 *
 * @param limiter A string representing the limiter for the here document.
 *
 * This function creates a temporary file and writes the input from the here
 * document into it until the limiter string is encountered. The input is read
 * line by line using the get_next_line function. Each line is written to the
 * temporary file, and the newline character at the end of the line is replaced
 * with a null character before writing. If an error occurs while opening the
 * temporary file, the function prints an error message and exits the program.
 */
void	handle_heredoc(char *limiter)
{
	int		fd;
	char	*line;
	char	*tmp_file;

	tmp_file = "/tmp/heredoc_tmp";
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(tmp_file);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		ft_putendl_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	close(fd);
}

void	free_cmds(char ***cmds, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

char	***fill_commands(char ***cmds, int num_cmds, char *argv[],
		int first_cmd_index)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		cmds[i] = ft_split(argv[i + first_cmd_index], ' ');
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

int	main(int argc, char *argv[])
{
	int		num_cmds;
	char	***cmds;
	int		ret;
	int		first_cmd_index;

	if (validate_args(argc, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	num_cmds = argc - 3;
	first_cmd_index = 2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		handle_heredoc(argv[2]);
		num_cmds = argc - 4;
		first_cmd_index = 3;
	}
	cmds = malloc((num_cmds + 1) * sizeof(char **));
	cmds = fill_commands(cmds, num_cmds, argv, first_cmd_index);
	ret = execute_commands(argv, cmds, num_cmds);
	free_cmds(cmds, num_cmds);
	return (ret);
}
