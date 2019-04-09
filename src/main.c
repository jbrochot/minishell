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

char *get_env_val(char *str)
{
	char *s;
	int i;
	int j;

	i = 0;
	while (str[i] != '=')
		i++;
	j = i + 1;
	while (str[i])
		i++;
	if (!(s = (char*)malloc(sizeof(char) * (i - j + 1))))
		return (NULL);
	i = j;
	j = 0;
	while (str[i])
	{
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	return (s);
}

char *get_env(char *str)
{
	char *s;
	int i;

	str = ft_strjoin (str, "=");
	i = 0;
	while (g_env[i])
	{
		s = ft_strstr(g_env[i], str);
		if (s != NULL)
			return (s = get_env_val(s));
		i++;
	}
	return (NULL);
}

char *first_whitespace(char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((buf[i] == ' '  || buf[i] == '\t' || buf[i] == '\n') && buf[i])
		i++;
	while (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' && buf[i])
		i++;
	if (!(tmp = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		tmp[j] = buf[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void rm_one(char *buf, int k)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	if (k == 1)
		j--;
	buf[j--] = '\0';
	if (k == 1)
		buf[j] = '\n';
}

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
	if (buf[0] == '"')
		line = parse_command(buf);
	else
		line = ft_split_whitespace(buf);
	pid = fork();
	while(exe[++i])
	{
		path = ft_strjoin(exe[i], "/");
		path = ft_strjoin(path, line[0]);
		if (pid == 0)
			execve(path, line, g_env);
	}
	if (pid == 0) {
		if (buf[0] != '\n')
			print_error(buf);
		exit(1);
	}
	if (pid > 0)
		wait(NULL);
	return (1);
}

void rm_whitespace(char *buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((buf[i] == ' ' || buf[i] == '\t') && buf[i])
		i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}

char *get_pwd(void)
{
	char *pwd;

	pwd = get_env("PWD");
	pwd = ft_strrchr(pwd, '/');
	rm_one(pwd, 0);
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
