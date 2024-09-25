/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:06:12 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/13 18:38:08 by stevennke        ###   ########.fr       */
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
	int		**pipes;
	pid_t	*pids;
}			t_data;

void		create_pipes(int num_cmds, int **pipes);
void		close_pipes(int num_cmds, int **pipes);

void		fork_processes(char *argv[], t_data *data);
int			wait_for_processes(t_data *data, pid_t *pids);
void		handle_input(char *argv[], int i, t_data *data);
void		handle_output(char *argv[], int i, t_data *data);
int			execute_commands(char *argv[], t_data *data);
int			allocate_resources(t_data *data);
void		free_cmds(t_data *data);
void		path_exists(char **envp, t_data *data);
void		fill_commands(t_data *data, char *argv[], int first_cmd_index);
int			validate_args(int argc, char *file_here_doc, int bonus);
void		output_to_file(char *str);
#endif
