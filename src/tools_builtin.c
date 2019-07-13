/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:26:21 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/23 13:26:24 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void rm_last(t_env *v)
{
    int  j;

    j = 0;
    while (v->pwd[j])
      j++;
    if (j == 4)
      return ;
    while (v->pwd[j] != '/')
      j--;
    if (j > 4)
      v->pwd[j] = '\0';
    else
      v->pwd[++j] = '\0';
}

void add_last(char *str, t_env *v)
{
  v->pwd = ft_strjoin_free(v->pwd, "/", 0);
  v->pwd = ft_strjoin_free(v->pwd, str, 0);
}

int	ft_reset(t_env *v)
{
	if (line_of_env("PWD") > -1)
  {
    free(g_env[line_of_env("PWD")]);
		g_env[line_of_env("PWD")] = ft_strdup(v->pwd);
  }
	if (line_of_env("HOME") > -1)
  {
    free(g_env[line_of_env("HOME")]);
		g_env[line_of_env("HOME")] = ft_strdup(v->home);
  }
	if (line_of_env("PATH") > -1)
  {
    free(g_env[line_of_env("PATH")]);
		g_env[line_of_env("PATH")] = ft_strdup(v->path);
  }
	return (1);
}
