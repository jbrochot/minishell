/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:35:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:28:18 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

char	**ft_split(char *str);
char	**ft_split_whitespace(char *str);
char	**split_env(char *str);
void  print_error(char *buf);
char  *get_env(char *str);
char  *first_whitespace(char *buf);
void  rm_one(char *buf, int k);
void  rm_whitespace(char *buf);
char  **parse_command(char *buf);
char  **parse_line(char *buf);
int   builtin(char *buf);
void  new_path(char *path);
int 	line_of_env(char *str);
char  *parse_arg(char *str);
void  change_env(char *str, char *selec);
int   ft_cd(char **line);
void  add_last(char *str);
void  rm_last(void);
char  **ft_echo(char *line);
int  detect_echo(char **line);
char *other_str(char *str, int i);
char *stop_str(char *str, int i);

#endif
