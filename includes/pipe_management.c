/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:50:05 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 15:54:04 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	create_pipes(int num_cmds, int **pipes)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		pipes[i] = malloc(2 * sizeof(int));
		pipe(pipes[i]);
		i++;
	}
}

void	close_pipes(int num_cmds, int **pipes)
{
	int	j;

	j = 0;
	while (j < num_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}
