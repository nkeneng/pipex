/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:06:12 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/11 22:04:31 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/lib_ft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	***cmds;
	int		num_cmds;
	char	**paths;
}			t_data;

void		create_pipes(int num_cmds, int **pipes);
void		close_pipes(int num_cmds, int **pipes);

void		fork_processes(char *argv[], t_data *data, int **pipes,
				pid_t *pids);
void		wait_for_processes(int num_cmds, pid_t *pids);
void		handle_input(char *argv[], int i, int **pipes);
void		handle_output(char *argv[], int i, int num_cmds, int **pipes);
int			execute_commands(char *argv[], t_data *data);
int			allocate_resources(int num_cmds, int ***pipes, pid_t **pids);
void		free_resources(int num_cmds, int **pipes, pid_t *pids);
void		wait_for_processes(int num_cmds, pid_t *pids);
void		free_cmds(t_data *data);
char		**path_exists(char **envp);
void		fill_commands(t_data *data, char *argv[], int first_cmd_index);
int			validate_args(int argc, char *file_here_doc);
#endif
