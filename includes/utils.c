/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:10:10 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 22:23:52 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (i < (*data).num_cmds)
	{
		free((*data).cmds[i]);
		i++;
	}
	free((*data).cmds);
	i = 0;
	while ((*data).paths[i])
	{
		free((*data).paths[i]);
		i++;
	}
}

char	**path_exists(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

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

void	fill_commands(t_data *data, char *argv[], int first_cmd_index)
{
	int	i;

	i = 0;
	while (i < (*data).num_cmds)
	{
		(*data).cmds[i] = ft_split(argv[i + first_cmd_index], ' ');
		i++;
	}
	(*data).cmds[i] = NULL;
}
