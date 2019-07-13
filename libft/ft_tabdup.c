/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:37:51 by jebrocho          #+#    #+#             */
/*   Updated: 2019/07/13 15:46:02 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **t)
{
	char **tab2;
	int j;

	j = -1;
	while (t[++j]);
	
	if (!(tab2 = (char**)malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	j = -1;
	while(t[++j])
		tab2[j] = ft_strdup(t[j]);
	return (tab2);
}
