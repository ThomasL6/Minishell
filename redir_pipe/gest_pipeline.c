/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:55:14 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/26 14:55:16 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_pipeline(char ***command, int nb_cmds, t_base *base)
{
	pid_t pid;
	int prev_pipe_read;
	int pipefd[2];
	int i;

	i = 0;
	prev_pipe_read = base->fd_in;
	while (i < nb_cmds)
	{
		if (i < nb_cmds - 1)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid	 = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (i != 0)
			{
				if (dup2(prev_pipe_read, base->fd_in) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(prev_pipe_read);
			}
			if (i < nb_cmds - 1)
			{
				if (dup2(pipefd[1], base->fd_out) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (is_there_redir(command[i]) != 0)
				gest_pipe_and_redir2(base, command, i);
			else
			{
				get_file_inpout(base, command[i], i);
				get_command(command, i, base);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			if (i < nb_cmds - 1)
			{
				close(pipefd[1]);
				prev_pipe_read = pipefd[0];
			}
		}
		i++;
	}
}