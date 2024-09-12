/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:15 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/12 19:51:24 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		ret;
	int		first_cmd_index;

	if (validate_args(argc, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	path_exists(envp, &data);
	if (!data.paths)
	{
		ft_putstr_fd("Error: PATH not found\n", 2);
		return (EXIT_FAILURE);
	}
	data.num_cmds = argc - 3;
	first_cmd_index = 2;
	data.cmds = malloc((data.num_cmds + 1) * sizeof(char **));
	fill_commands(&data, argv, first_cmd_index);
	ret = execute_commands(argv, &data);
	free_cmds(&data);
	return (ret);
}
