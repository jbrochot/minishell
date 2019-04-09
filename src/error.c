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


void print_error(char *buf)
{
  int i;

  i = ft_strlen(buf);
  i--;
  buf[i] = '\0';
  ft_printf("%s: Commande introuvable\n", buf);
}
