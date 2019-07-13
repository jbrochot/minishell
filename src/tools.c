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

char	*get_exp(char *stock, int index)
{
	int		i;
	char	*exp;
	char 	*s;

	i = 0;
	while (stock[index + i])
		i++;
	if (i == index + 1)
	{
		return ("$");
	}
	if (!(exp = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	index++;
	while (stock[index])
	{
		exp[i] = stock[index];
		i++;
		index++;
	}
	exp[i] = '\0';
	s = get_env(exp);
	free(exp);
	free(stock);
	return (s);
}

char	*parse_exp(char *stock, char *exp)
{
	int i;

	i = 0;
	while (stock[i] != '$' && stock[i])
		i++;
	stock[i] = '\0';
	return (ft_strjoin(stock, exp));
}

char	*expansions(char *buf)
{
	char **stock;
	char *exp;
	char save[255];
	int i;
	int j;
	int k;

	i = -1;
	stock = ft_split_whitespace_exp(buf);
	while (stock[++i])
	{
		j = -1;
		k = 0;
		while (stock[i][++j])
		{
			if (stock[i][j] == '$')
			{
				exp = get_exp(stock[i], j);
				if (exp != NULL)
						stock[i] = parse_exp(stock[i], exp);
				else
					stock[i][j] = '\0';
				free(exp);
			}
		  if (stock[i][j] == '~' && (stock[i][j + 1] == '/' || j == 0))
			{
				while (stock[i][++j])
					save[k++] = stock[i][j];
				save[k] = 0;
				free(stock[i]);
				stock[i] = get_env("HOME");
				stock[i] = ft_strjoin_free(stock[i], save, 0);
			}
		}
	}
	i = 0;
	buf = stock[0];
	while (stock[++i])
	{
		buf = ft_strjoin_free(buf, " ", 0);
		buf = ft_strjoin_free(buf, stock[i], 0);
		free(stock[i]);
	}
	free(stock);
	buf = ft_strjoin_free(buf, "\n", 0);
	return (buf);
}

char *rm_whitespace(char *buf)
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
	if (ft_strlen(buf) > 1)
		buf = expansions(buf);
	return (buf);
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

void parse_arg(char *str, char c, t_env *v)
{
	int	 j;
	int	 i;

	i = -1;
	j = 0;
	if (!str)
		return ;
	while (str[++i])
	{
		if ((str[i] == c && str[i + 1] != c) || str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = 0;
	if (str[j - 1] == '-' && ft_strlen(str) == 1)
		v->istir = 1;
}

char *parse_error(char *s)
{
	char **cpy;
	int i;
	int j;
	int save;

	i = -1;
	save = 0;
	cpy = ft_strsplit(s, '/');
	if (s[0] == '/')
	{
		while (s[++i]);

		if (i == 1)
		{
			free(cpy);
			return (ft_strdup("/"));
		}
		save = 1;
	}
	i = -1;
	while (cpy[++i])
	{
		if (ft_strcmp(cpy[i], "..") == 0 && i > 0)
		{
			j = i;
			while (cpy[j + 1])
			{
				cpy[j - 1] = cpy[j + 1];
				j++;
			}
			cpy[j - 1] = 0;
			if (j > i)
				i--;
		}
	}
	i = 0;
	if (save == 1)
		cpy[0] = ft_strjoin_free("/", cpy[0], 1);
	while (cpy[++i])
	{
		cpy[0] = ft_strjoin_free(cpy[0], "/", 0);
		cpy[0] = ft_strjoin_free(cpy[0], cpy[i], 2);
	}
	s = ft_strdup(cpy[0]);
	free(cpy[0]);
	free(cpy);
	return (s);
}
