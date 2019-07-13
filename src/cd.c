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

int check_error(char **line, t_env *v)
{
  DIR  *dir1;
  char *cpy;

  cpy = parse_error(line[1]);
  if (lstat(cpy, &st) < 0 && v->istir != 1)
    return (error_cd(cpy, 0));
  if (ft_is_dir(cpy) == 0 && v->istir != 1)
    return (error_cd(cpy, 2));
  dir1  = opendir(cpy);
  if (dir1 == NULL && v->istir != 1)
    return (error_cd(cpy, 1));
  if (v->istir == 0)
    closedir(dir1);
  free(cpy);
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
  char  *tir;

  i = -1;
  if (path[0] == '/')
  {
    free(v->pwd);
    v->pwd = ft_strdup("PWD=/");
  }
  if (path[0] == '-')
  {
    free(v->pwd);
    v->pwd = ft_strdup(g_env[line_of_env("OLDPWD")]);
    tir = get_pwd();
    change_env(tir, "OLDPWD", v);
    tir = get_env_val(v->pwd);
    change_env(tir, "PWD", v);
    free(tir);
    v->istir = 0;
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

  parse_arg(line[1], '/', v);
  l[1] = ft_strjoin_free("OLDPWD=", get_env_val(v->pwd), 1);
  l[0] = 0;
  l[2] = 0;
  if (line[1])
  {
    if (check_error(line, v) == -1)
    {
      free(line[1]);
      free(line[0]);
      free(l[1]);
      return (1);
    }
    if (new_path(line[1], v) == 0)
      ft_setenv(l, v);
  }
  else
    home(l, v);
  free(l[1]);
  l[1] = get_env_val(v->pwd);
  l[0] = get_env_val(v->home);
  line[1] != NULL ? chdir(l[1]) : chdir(l[0]);
  free(l[1]);
  free(l[0]);
  free(line[0]);
  free(line[1]);
  free(line);
  return (1);
}
