/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:28:56 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/23 13:29:10 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void rm_echo(char *str)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
    i++;
  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
    i++;
  while (str[i])
  {
    str[j] = str[i];
    i++;
    j++;
  }
  str[j] = '\0';
}

int  detect_echo(char **line)
{
  int i;

  i = -1;
  if (ft_strcmp(line[0], "echo") == 0)
  {
    while (line[++i])
      free(line[i]);
    free(line);
    return (0);
  }
  return (1);
}

void rm_cote(char *line)
{
  int i;
  int j;
  int k;

  i = -1;
  while (line[++i])
  {
    if (line[i] == '"')
    {
      k = i;
      j = i + 1;
      while (line[j])
      {
        line[k] = line[j];
        k++;
        j++;
      }
      line[k] = '\0';
    }
  }
}

void parse_echo(char *line)
{
  int i;
  int id_cote;
  int new_id;
  int index;

  id_cote = 0;
  i = -1;
  while (line[++i])
  {
    if (line[i] == '"')
      id_cote += 1;
    if (id_cote % 2 == 0)
    {
      while (line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
      index = i + 1;
      new_id = index;
      while (line[i] && (line[new_id] == ' ' || line[new_id] == '\t'))
        new_id++;
      while (line[new_id])
      {
        line[index] = line[new_id];
        index += 1;
        new_id += 1;
      }
      line[index] = '\0';
    }
  }
  rm_cote(line);
}

char *other_str(char *str, int i)
{
  char *tmp;
  char *s;
  int j;
  int k;

  k = i;
  while (str[k] && str[k] != ' ' && str[k] != '\t' && str[k] != '\n')
    k++;
  if (!(s = (char*)malloc(sizeof(char) * (k - i))))
    return (NULL);
  j = k;
  while (str[k])
    k++;
  if (!(tmp = (char*)malloc(sizeof(char) * (k - j))))
    return (NULL);
  k = j;
  j = 0;
  while (str[k])
  {
    tmp[j] = str[k];
    j++;
    k++;
  }
  tmp[j] = '\0';
  j = 0;
  k = i;
  i++;
  while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
  {
    s[j] = str[i];
    j++;
    i++;
  }
  s[j] = '\0';
  str[k] = '\0';
  s = get_env(s);
  if (s != NULL)
  {
    str = ft_strjoin(str, s);
    str = ft_strjoin(str, tmp);
    return (str);
  }
  return (NULL);
}

char *stop_str(char *str, int i)
{
  char *tmp;
  int j;
  int k;

  j = i;
  while (str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
    i++;
  k = i;
  while (str[i])
    i++;
  if (!(tmp = (char*)malloc(sizeof(char) * (i - k))))
    return (NULL);
  i = k;
  k = 0;
  while (str[i])
  {
    tmp[k] = str[i];
    k++;
    i++;
  }
  tmp[k] = '\0';
  str[j] = '\0';
  str = ft_strjoin(str, tmp);
  return (str);
}

char *first_parse(char *str)
{

  int i;
  int id_cote;

  id_cote = 0;
  i = -1;
  while (str[++i])
  {
    if (str[i] == '$')
    {
      if (i == 0)
        str = other_str(str, i);
      else if (str[i - 1] == ' ' || str[i - 1] == '\t')
        str = other_str(str, i);
      else
        str = stop_str(str, i);
    }
    if (str[i] == '"')
      id_cote++;
    if (id_cote % 2 == 0)
    {
      if (str[i] == '\t')
        str[i] = ' ';
    }
  }
  return (str);
}

char **ft_echo(char *str)
{
  rm_echo(str);
  str = first_parse(str);
  parse_echo(str);
  ft_printf("%s", str);
  return (NULL);
}
