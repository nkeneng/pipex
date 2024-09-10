/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/10 18:42:12 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf/ft_printf.h"
#include "pipex.h"

void	split_and_execute_command(char **cmd, char *input_file,
		char *output_file)
{
	int	fd_in;
	int	fd_out;

	if (cmd != NULL)
	{
		fd_in = open(input_file, O_RDONLY);
		if (fd_in == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		// Redirect standard input to the file
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		// If output_file is not NULL, redirect standard output to the file
		if (output_file != NULL)
		{
			fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (dup2(fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		execvp(cmd[0], cmd);
		exit(127); // execvp will only return if it fails
	}
}

int	is_valid_cmd(char **cmd, char *input_file, char *output_file)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	pid = fork();
	if (pid == -1)
		return (0); // fork failed
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		while (cmd[i] != NULL)
			free(cmd[i++]);
		free(cmd);
		return (0);
		// if (WIFEXITED(status))
		// {
		// 	if (WEXITSTATUS(status) == 127)
		// 		return (0);
		// }
		// else
		// 	return (0);
	}
	else
	{
		split_and_execute_command(cmd, input_file, output_file);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	char	**cmd1;
	char	**cmd2;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	// make sure that file 1 exists and is readable
	// if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1)
	// {
	// 	ft_putstr_fd("Error: File 1 does not exist or is not readable\n", 2);
	// 	return (EXIT_FAILURE);
	// }
	cmd1 = ft_split(argv[2], ' ');
	if (cmd1 == NULL)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (EXIT_FAILURE);
	}
	// if (open("temp.out", O_CREAT | O_RDWR) == -1)
	// {
	// 	// perror("open");
	// 	return (EXIT_FAILURE);
	// }
	// check if cmd1 is a valid command
	// is_valid_cmd(cmd1, argv[1], "temp.out");
	// {
	// 	// ft_putstr_fd("Error: Invalid command 1\n", 2);
	// 	// return (EXIT_FAILURE);
	// }
	// create file 2
	// if (open(argv[4], O_CREAT | O_RDWR) == -1)
	// {
	// 	// perror("open");
	// 	// return (EXIT_FAILURE);
	// }
	cmd2 = ft_split(argv[3], ' ');
	is_valid_cmd(cmd2, "temp.out", argv[4]);
	// {
	// 	ft_putstr_fd("Error: Invalid command 2\n", 2);
	// 	return (EXIT_FAILURE);
	// }
	// delete temp.out
	unlink("temp.out");
	// {
	// 	perror("unlink");
	// 	return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}
