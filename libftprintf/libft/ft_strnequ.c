/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 12:03:59 by jbert             #+#    #+#             */
/*   Updated: 2015/03/05 13:15:01 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strnequ(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i < n && s1[i] != s2[i])
		return (0);
	return (1);
}
