/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:35:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:28:18 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **parse_command(char *buf)
{
	char **line;
	char	*tmp;

	rm_one(buf, 1);
	tmp = first_whitespace(buf);
	line = ft_split_whitespace(buf);
	line[0] = tmp;
	return (line);
}

int exec_all(char **exe, char *buf)
{
	pid_t	pid;
	char	**line;
	char	*path;
	int		i;

	i = -1;
	line = parse_line(ft_strdup(buf));
	pid = fork();
	while(exe[++i])
	{
		path = ft_strjoin(exe[i], "/");
		path = ft_strjoin(path, line[0]);
		if (pid == 0)
			execve(path, line, g_env);
	}
	if (pid == 0)
	{
		if (buf[0] != '\n')
			print_error(buf);
		exit(1);
	}
	if (pid > 0)
		wait(NULL);
	return (1);
}

char *get_pwd(void)
{
	char *pwd;

	pwd = get_env("PWD");
	if (ft_strcmp(pwd, "/") != 0)
	{
		pwd = ft_strrchr(pwd, '/');
		rm_one(pwd, 0);
	}
	return (pwd);
}

int ft_read(void)
{
	char *path;
	char **exe;
	char buf[4096];

	path = get_pwd();
	ft_printf("[%s]-> ", path);
	ft_bzero(buf, 4096);
	if (read(0, &buf, 4096) == -1)
		return (-1);
	rm_whitespace(buf);
	if (builtin(buf) == 1)
		return (1);
	path = get_env("PATH");
	exe = ft_split(path);
	free(path);
	exec_all(exe, buf);
	return (1);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;

	g_env = env;
	while (ft_read() == 1)
	{
	}
	return (0);
}
