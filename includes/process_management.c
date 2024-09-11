/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:40:36 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 16:21:34 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdio.h>

void	fork_processes(char *argv[], char ***cmds, int **pipes, pid_t *pids)
{
	int	i;
	int	num_cmds;

	num_cmds = get_commands_size(cmds);
	i = 0;
	while (i < num_cmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			handle_input(argv, i, pipes);
			handle_output(argv, i, num_cmds, pipes);
			close_pipes(num_cmds, pipes);
			execvp(cmds[i][0], cmds[i]);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	wait_for_processes(int num_cmds, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}
