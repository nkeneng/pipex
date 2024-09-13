/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:39:08 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/13 18:41:03 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"

int	execute_commands(char *argv[], t_data *data)
{
	int		res;

	if (allocate_resources(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_pipes((*data).num_cmds, (*data).pipes);
	fork_processes(argv, data);
	close_pipes((*data).num_cmds, (*data).pipes);
	res = wait_for_processes(data, (*data).pids);
	return (res);
}
