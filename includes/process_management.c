/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:40:36 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 22:01:06 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_execvp(t_data *data, int index)
{
	int		i;
	char	*path;

	i = 0;
	while ((*data).paths[i])
	{
		path = ft_strjoin((*data).paths[i], "/");
		path = ft_strjoin(path, (*data).cmds[index][0]);
		if (access(path, X_OK) == 0)
		{
			execve(path, (*data).cmds[index], NULL);
			free(path);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (path)
		free(path);
	perror("invalid command");
	return (EXIT_FAILURE);
}

void	fork_processes(char *argv[], t_data *data, int **pipes, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < (*data).num_cmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			handle_input(argv, i, pipes);
			handle_output(argv, i, (*data).num_cmds, pipes);
			close_pipes((*data).num_cmds, pipes);
			ft_execvp(data, i);
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
