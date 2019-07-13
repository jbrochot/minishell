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

void new_env(char *l, t_env *v)
{
  char **stock_env;
  int i;

  i = -1;
  while (g_env[++i]);

  if (!(stock_env = (char**)malloc(sizeof(char*) * (i + 2))))
    exit(EXIT_FAILURE);
  i = -1;
  while (g_env[++i])
  {
    stock_env[i] = ft_strdup(g_env[i]);
    if (v->freethis == 1)
      free(g_env[i]);
  }
  stock_env[i] = ft_strdup(l);
  i++;
  stock_env[i] = 0;
  g_env = stock_env;
  v->freethis = 1;
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
    res[1] = get_env(nline[0]);
    if (res[1] != NULL && nline[1])
    {
      free(res[1]);
      if (ft_strcmp(nline[0], "OLDPWD") == 0)
      {
        res[1] = ft_strdup("OLDPWD");
        res[2] = 0;
        ft_unsetenv(res);
        free(res[1]);
        ft_setenv(line, v);
      }
      change_env(nline[1], nline[0], v);
      free(nline[1]);
      free(nline[0]);
    }
    else
    {
      free(res[1]);
      l = ft_strjoin_free(nline[0], "=", 0);
      l = ft_strjoin_free(l, nline[1], 2);
      new_env(l, v);
      free(l);
    }
  }
  free(nline);
  return (1);
}
