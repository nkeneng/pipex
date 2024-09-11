/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:39:08 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 19:09:29 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"

/**
 * Function: execute_commands
 * --------------------------
 * Executes the commands passed as arguments to the pipex program.
 *
 * @param argv The command line arguments.
 * @param cmds A 2D array of commands to be executed.
 * @param num_cmds The number of commands.
 *
 * @return EXIT_SUCCESS if the commands are executed successfully, 
 * otherwise EXIT_FAILURE.
 *
 * This function first allocates resources for the pipes and process IDs.
 * If the allocation fails, it returns EXIT_FAILURE. 
 * It then creates the necessary pipes and forks the processes
 * to execute the commands. After the commands are executed, 
 * it closes the pipes and waits for all processes to finish.
 * Finally, it frees the allocated resources and returns EXIT_SUCCESS.
 */
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
