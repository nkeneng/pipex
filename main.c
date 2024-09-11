/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:50:26 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 16:20:09 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	validate_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int		num_cmds;
	char	***cmds;
	int		ret;
	int		i;

	if (validate_args(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	num_cmds = argc - 3;
	cmds = malloc((num_cmds + 1) * sizeof(char **));
	i = 0;
	while (i < num_cmds)
	{
		cmds[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	cmds[i] = NULL;
	ret = execute_commands(argv, cmds, num_cmds);
	i = 0;
	while (i < num_cmds)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
	return (ret);
}
