/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:15 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 22:05:46 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		ret;
	int		first_cmd_index;

	if (validate_args(argc, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data.paths = path_exists(envp);
	if (!data.paths)
	{
		ft_putstr_fd("Error: PATH not found\n", 2);
		return (EXIT_FAILURE);
	}
	data.num_cmds = argc - 3;
	first_cmd_index = 2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		handle_heredoc(argv[2]);
		data.num_cmds = argc - 4;
		first_cmd_index = 3;
	}
	data.cmds = malloc((data.num_cmds + 1) * sizeof(char **));
	fill_commands(&data, argv, first_cmd_index);
	ret = execute_commands(argv, &data);
	free_cmds(&data);
	return (ret);
}
