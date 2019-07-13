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


char   *get_env_val(char *str)
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

char   *get_env(char *str)
{
	char *s;
	int i;

	str = ft_strjoin (str, "=");
	i = 0;
	while (g_env[i])
	{
		s = ft_strstr(g_env[i], str);
		if (s != NULL)
		{
			free(str);
			return (get_env_val(s));
		}
		i++;
	}
	free(str);
	return (NULL);
}

int 	line_of_env(char *str)
{
	char *s;
	int i;

	str = ft_strjoin(str, "=");
	i = 0;
	while (g_env[i])
	{
		s = ft_strstr(g_env[i], str);
		if (s != NULL)
		{
			free(str);
			return (i);
		}
		i++;
	}
	free(str);
	return (-1);
}

void  change_env(char *str, char *selec, t_env *v)
{
  int i;
  int j;
  int k;

  k = 0;
  i = 0;
  j = line_of_env(selec);
  while (g_env[j][k] != '=')
    k++;
  k++;
//	free(g_env[j])
//	g_env[j] = ft_strdup(str[i]);
  while (str[i])
  {
    g_env[j][k] = str[i];
    k++;
    i++;
  }
  if (g_env[j][k - 1] == '/' && ft_strcmp(str, "/") != 0)
    k--;
  g_env[j][k] = '\0';
	if (ft_strcmp(selec, "PWD") == 0)
	{
		free(v->pwd);
		v->pwd = ft_strdup(g_env[line_of_env("PWD")]);
	}
	if (ft_strcmp(selec, "HOME") == 0)
	{
		free(v->home);
		v->home = ft_strdup(g_env[line_of_env("HOME")]);
	}
	if (ft_strcmp(selec, "PATH") == 0)
	{
		free(v->path);
		v->path = ft_strdup(g_env[line_of_env("PATH")]);
	}
}
