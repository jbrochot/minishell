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

int  builtin(char *buf)
{
  char **line;

  line = parse_line(buf);
  if (!line)
    return (1);
  if (ft_strcmp(line[0], "exit") == 0)
    line[1] != NULL ? exit(ft_atoi(line[1])) : exit(0);
  if (ft_strcmp(line[0], "cd") == 0)
    return (ft_cd(line));
  if (ft_strcmp(line[0], "setenv") == 0)
    return (ft_setenv(line));
  return (0);
}
