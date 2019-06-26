/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:04:27 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/02 10:37:17 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ctrl(int signal)
{
  (void)signal;
  char *path;

  write(0, "\n", 1);
  path = get_pwd();
  ft_printf("[%s]-> ", path);
}

void print_error(char *buf)
{
  int i;

  i = ft_strlen(buf);
  i--;
  buf[i] = '\0';
  ft_printf("%s: Commande introuvable\n", buf);
}

int   error_env(void)
{
  ft_putstr_fd("environment not found\n", 2);
  return (-1);
}

int   ft_error_path(void)
{
  ft_putstr_fd("PATH not found\n", 2);
  return (-1);
}
