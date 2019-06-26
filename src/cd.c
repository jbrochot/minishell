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
  DIR  *dir1;
  char *cpy;

  cpy = parse_error(line[1]);
  if (ft_is_dir(cpy) == 0)
  {
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd("no such file or directory: ", 2);
    ft_putstr_fd(line[1], 2);
    ft_putstr_fd("\n", 2);
    return (-1);
  }
  dir1 = opendir(cpy);
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

void home(char **line, t_env *v)
{
  int k;
  int l;

  l = 0;
  k = 0;
  ft_setenv(line, v);
  while (v->pwd[k] != '=')
    k++;
  while (v->home[l] != '=')
    l++;
  while (v->home[l])
  {
    v->pwd[k] = v->home[l];
    k++;
    l++;
  }
  v->pwd[k] = '\0';
}

int  new_path(char *path, t_env *v)
{
  int   i;
  char  **s;

  i = -1;
  if (path[0] == '/')
    v->pwd = ft_strdup("PWD=/");
  if (path[0] == '-')
  {
    v->pwd = ft_strdup(g_env[line_of_env("OLDPWD")]);
    ft_printf("%s\n\n", v->pwd);
    change_env(get_env("PWD"), "OLDPWD");
    change_env(get_env_val(v->pwd), "PWD");
    v->pwd = ft_strdup(g_env[line_of_env("PWD")]);
    return (1);
  }
  s = ft_split(path, '/');
  while (s[++i])
  {
    if (ft_strcmp(s[i], "..") == 0)
      rm_last(v);
    else if (s[i])
      add_last(s[i], v);
    free(s[i]);
  }
  free(s);
  return (0);
}

int   ft_cd(char **line, t_env *v)
{
  char *l[3];

  parse_arg(line[1], '/');
  l[1] = ft_strjoin("OLDPWD=", get_env_val(v->pwd));
  l[0] = 0;
  l[2] = 0;
  if (line[1])
  {
    if (check_error(line) == -1)
      return (1);
    if (new_path(line[1], v) == 0)
      ft_setenv(l, v);
    parse_arg(v->pwd, '/');
  }
  else
    home(l, v);
  line[1] != NULL ? chdir(get_env_val(v->pwd)) : chdir(get_env_val(v->home));
  return (1);
}
