/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:45:36 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/13 18:38:38 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	allocate_resources(t_data *data)
{
	(*data).pipes = malloc(((*data).num_cmds - 1) * sizeof(int *));
	(*data).pids = malloc((*data).num_cmds * sizeof(pid_t));
	if (!(*data).pipes || !(*data).pids)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
