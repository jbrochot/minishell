/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:08:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/15 14:09:02 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  builtin(char *buf, t_env *v)
{
  char **line;

  line = parse_line(buf);
  if (!line)
    return (1);
  if (ft_strcmp(line[0], "exit") == 0)
    line[1] != NULL ? exit(ft_atoi(line[1])) : exit(0);
  if (ft_strcmp(line[0], "cd") == 0)
  {
    free(buf);
    return (ft_cd(line, v));
  }
  if (ft_strcmp(line[0], "setenv") == 0)
  {
    free(buf);
    ft_setenv(line, v);
    return (free_tab(line));
  }
  if (ft_strcmp(line[0], "env") == 0)
  {
    free(buf);
    free_tab(line);
    return (p_env());
  }
  if (ft_strcmp(line[0], "unsetenv") == 0)
  {
    free(buf);
    ft_unsetenv(line);
    return (free_tab(line));
  }
//  free_tab(line);
  return (0);
}
