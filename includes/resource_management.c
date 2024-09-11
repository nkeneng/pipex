/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:45:36 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 15:49:16 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	allocate_resources(int num_cmds, int ***pipes, pid_t **pids)
{
	*pipes = malloc((num_cmds - 1) * sizeof(int *));
	*pids = malloc(num_cmds * sizeof(pid_t));
	if (!*pipes || !*pids)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_resources(int num_cmds, int **pipes, pid_t *pids)
{
	int	i;

	i = 0;
	free(pids);
	while (i < num_cmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
