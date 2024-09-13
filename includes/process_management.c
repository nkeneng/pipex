/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:40:36 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/13 18:42:36 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_execvp(t_data *data, int index)
{
	int		i;
	char	*path1;
	char	*path;

	i = 0;
	while ((*data).paths[i])
	{
		path1 = ft_strjoin((*data).paths[i], "/");
		path = ft_strjoin(path1, (*data).cmds[index][0]);
		free(path1);
		if (access(path, X_OK) == 0)
		{
			execve(path, (*data).cmds[index], NULL);
			free(path);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		i++;
		free(path);
	}
	perror("invalid command");
	free_cmds(data);
	exit(127);
}

void	fork_processes(char *argv[], t_data *data)
{
	int	i;

	i = 0;
	while (i < (*data).num_cmds)
	{
		(*data).pids[i] = fork();
		if ((*data).pids[i] == 0)
		{
			handle_input(argv, i, data);
			handle_output(argv, i, data);
			close_pipes((*data).num_cmds, (*data).pipes);
			ft_execvp(data, i);
		}
		i++;
	}
}

int	wait_for_processes(t_data *data, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < (*data).num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				if (i == (*data).num_cmds - 1)
				{
					return (WEXITSTATUS(status));
				}
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
