/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:53:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/09 17:54:05 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int   p_env(void)
{
  int i;

  i = -1;
  while (g_env[++i])
    ft_printf("%s\n", g_env[i]);
  return (1);
}

void new_env(char *l)
{
  char **stock_env;
  int i;

  i = -1;
  while (g_env[++i]);

  if (!(stock_env = (char**)malloc(sizeof(char*) * (i + 2))))
    exit(EXIT_FAILURE);
  i = -1;
  while (g_env[++i])
    stock_env[i] = ft_strdup(g_env[i]);
  stock_env[i] = ft_strdup(l);
  i++;
  stock_env[i] = 0;
  g_env = stock_env;
}

int ft_setenv(char **line, t_env *v)
{
  int i;
  char **nline;
  char *l;
  char *res[3];

  i = 0;
  while (line[++i])
  {
    nline = ft_split(line[i], '=');
    if (get_env(nline[0]) != NULL && nline[1])
    {
      if (ft_strcmp(nline[0], "OLDPWD") == 0)
      {
        res[1] = ft_strdup("OLDPWD");
        res[2] = 0;
        ft_unsetenv(res);
        ft_setenv(line, v);
      }
      change_env(nline[1], nline[0], v);
    }
    else
    {
      l = ft_strjoin(nline[0], "=");
      l = ft_strjoin(l, nline[1]);
      new_env(l);
    }
  }
  return (1);
}
