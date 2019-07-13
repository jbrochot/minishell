/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:28:09 by jebrocho          #+#    #+#             */
/*   Updated: 2019/06/28 23:28:38 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *ft_strjoin_free(char *s1, char *s2, int mod)
{
  int		i;
  int		j;
  char	*dest;

  if (!s1 || !s2)
    return (NULL);
  j = 0;
  i = ft_strlen(s1);
  i = i + ft_strlen(s2);
  if (!(dest = (char*)malloc(sizeof(char) * i)))
    return (NULL);
  while (s1[j])
  {
    dest[j] = s1[j];
    j++;
  }
  i = 0;
  while (s2[i])
  {
    dest[j] = s2[i];
    i++;
    j++;
  }
  dest[j] = '\0';
  if (mod == 0 || mod == 2)
    free(s1);
  if (mod == 1 || mod == 2)
    free(s2);
  return (dest);
}

int free_tab(char **t)
{
  int i;

  i = -1;
  while (t[++i])
    free(t[i]);
  free(t);
  return (1);
}
