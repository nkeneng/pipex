/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:15 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 19:31:08 by stevennke        ###   ########.fr       */
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
	cmds = malloc((num_cmds + 1) * sizeof(char **));
	cmds = fill_commands(cmds, num_cmds, argv, first_cmd_index);
	ret = execute_commands(argv, cmds, num_cmds);
	free_cmds(cmds, num_cmds);
	return (ret);
}
