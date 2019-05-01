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

void rm_last(void)
{
    int  i;
    int  j;

    j = 0;
    i = line_of_env("PWD");
    while (g_env[i][j])
      j++;
    j--;
    if (j == 4)
      return ;
    while (g_env[i][j] != '/')
      j--;
    g_env[i][j] = '\0';
}

void add_last(char *str)
{
  int i;

  i = line_of_env("PWD");
  g_env[i] = ft_strjoin(g_env[i], "/");
  g_env[i] = ft_strjoin(g_env[i], str);
}
