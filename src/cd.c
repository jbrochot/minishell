/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:21:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/23 13:21:26 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_error(char **line)
{
  DIR *dir1;

  if (ft_strcmp(line[1], "~/") == 0)
  {
    line[1] = get_env("HOME");
    return (1);
  }
  if (ft_is_dir(line[1]) == 0)
  {
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd("no such file or directory: ", 2);
    ft_putstr_fd(line[1], 2);
    ft_putstr_fd("\n", 2);
    return (-1);
  }
  dir1 = opendir(line[1]);
  if (dir1 == NULL)
  {
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd("permission denied: ", 2);
    ft_putstr_fd(line[1], 2);
    ft_putstr_fd("\n", 2);
    return (-1);
  }
  return (0);
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

int   ft_cd(char **line)
{
  line[1] = parse_arg(line[1]);
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
