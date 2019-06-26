/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:26:48 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/21 18:37:04 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_dir(char *s)
{
	if (lstat(s, &st) < 0)
		return (-1);
	if (S_ISDIR(st.st_mode))
		return (-1);
	if (S_ISLNK(st.st_mode))
		return (1);
	return (0);
}
