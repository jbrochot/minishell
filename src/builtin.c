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

void  change_env(char *str, char *selec)
{
  int i;
  int j;
  int k;

  k = 0;
  i = 0;
  j = line_of_env(selec);
  while (g_env[j][k] != '=')
    k++;
  k++;
  while (str[i])
  {
    g_env[j][k] = str[i];
    k++;
    i++;
  }
  if (g_env[j][k - 1] == '/' && ft_strcmp(str, "/") != 0)
    k--;
  g_env[j][k] = '\0';
}

void rm_last(void)
{
    int  i;
    int  j;

    j = 0;
    i = line_of_env("PWD");
    while (g_env[i][j])
      j++;
    j--;
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

void  new_path(char *path)
{
  int   i;
  char  **s;

  i = 0;
  if (path[i] == '/')
  {
    change_env(path, "PWD");
    return ;
  }
  s = split_env(path);
  while (s[i])
  {
    if (ft_strcmp(s[i], "..") == 0)
      rm_last();
    else if (s[i])
      add_last(s[i]);
    free(s[i]);
    i++;
  }
  free(s);
}

void home(void)
{
  int i;
  int j;
  int k;
  int l;

  l = 0;
  k = 0;
  i = line_of_env("HOME");
  j = line_of_env("PWD");
  while (g_env[j][k] != '=')
    k++;
  while (g_env[i][l] != '=')
    l++;
  while (g_env[i][l])
  {
    g_env[j][k] = g_env[i][l];
    k++;
    l++;
  }
  g_env[j][k] = '\0';
}

int check_error(char **line)
{
  DIR *dir1;

  if (ft_is_dir(line[1]) == 0)
  {
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(line[1], 2);
    perror(" ");
    return (-1);
  }
  dir1 = opendir(line[1]);
  if (dir1 == NULL)
  {
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(line[1], 2);
    perror(" ");
    return (-1);
  }
  return (0);
}

int  builtin(char *buf)
{
  char **line;

  line = parse_line(buf);
  if (!line)
    return (1);
  if (ft_strcmp(line[0], "exit") == 0)
    line[1] != NULL ? exit(ft_atoi(line[1])) : exit(0);
  if (ft_strcmp(line[0], "cd") == 0)
  {
    if (line[1])
    {
      if (check_error(line) == -1)
        return (1);
      new_path(line[1]);
    }
    else
      home();
    line[1] != NULL ? chdir(get_env("PWD")) : chdir(get_env("HOME"));
    return (1);
  }
  return (0);
}
