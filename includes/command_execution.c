/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:39:08 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 20:57:22 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"

int	execute_commands(char *argv[], t_data *data)
{
	int		**pipes;
	pid_t	*pids;

	if (allocate_resources((*data).num_cmds, &pipes, &pids) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	create_pipes((*data).num_cmds, pipes);
	fork_processes(argv, data, pipes, pids);
	close_pipes((*data).num_cmds, pipes);
	wait_for_processes((*data).num_cmds, pids);
	free_resources((*data).num_cmds, pipes, pids);
	return (EXIT_SUCCESS);
}
