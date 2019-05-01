/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:57:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/09 17:58:20 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


char **parse_line(char *buf)
{
	int i;
	char **line;

	i = -1;
	if (buf[0] == '"')
		line = parse_command(buf);
	else
		line = ft_split_whitespace(buf);
	i = detect_echo(line);
	if (i == 0)
		return (ft_echo(buf));
	return (line);
}

char *parse_arg(char *str)
{
	char **t;
	char *s;
	int  k;
	int	 j;
	int	 i;

	if (!str)
		return (NULL);
	i = -1;
	k = 0;
	j = 0;
	t = split_env(str);
	while (t[++i])
	{
		j += ft_strlen(t[i]);
		j += 1;
	}
	if (!(s = (char*)malloc(sizeof(char) * (j + 2))))
	 	return (NULL);
	if (str[0] == '/')
		s[k++] = '/';
	i = -1;
	while (t[++i])
	{
		j = -1;
		while (t[i][++j])
			s[k++] = t[i][j];
		s[k++] = '/';
	}
	s[k] = '\0';
	return (s);
}
