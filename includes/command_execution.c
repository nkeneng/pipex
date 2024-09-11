/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:39:08 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 16:11:47 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"

int	execute_commands(char *argv[], char ***cmds, int num_cmds)
{
	int		**pipes;
	pid_t	*pids;

	if (allocate_resources(num_cmds, &pipes, &pids) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	create_pipes(num_cmds, pipes);
	fork_processes(argv, cmds, pipes, pids);
	close_pipes(num_cmds, pipes);
	wait_for_processes(num_cmds, pids);
	free_resources(num_cmds, pipes, pids);
	return (EXIT_SUCCESS);
}
