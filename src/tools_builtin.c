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
  v->pwd = ft_strjoin(v->pwd, "/");
  v->pwd = ft_strjoin(v->pwd, str);
}
