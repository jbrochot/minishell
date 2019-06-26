/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:14:21 by jebrocho          #+#    #+#             */
/*   Updated: 2019/06/12 10:14:37 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int   ft_unsetenv(char **line)
{
  int i;
  int j;

  i = 0;
  while (line[++i])
  {
    j = line_of_env(line[i]);
    if (j == -1)
    {
      ft_putstr_fd("can not unset environment\n", 2);
      return (1);
    }
    while (g_env[j + 1])
    {
      g_env[j] = g_env[j + 1];
      j++;
    }
    g_env[j] = NULL;
    j = 0;
  }
  return (1);
}
