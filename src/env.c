/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:53:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/09 17:54:05 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char   *get_env_val(char *str)
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

char            *get_env(char *str)
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

int 	line_of_env(char *str)
{
	char *s;
	int i;

	str = ft_strjoin (str, "=");
	i = 0;
	while (g_env[i])
	{
		s = ft_strstr(g_env[i], str);
		if (s != NULL)
			return (i);
		i++;
	}
	return (-1);
}
