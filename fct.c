/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 13:26:32 by jbert             #+#    #+#             */
/*   Updated: 2016/01/11 15:36:14 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

char	*ft_strjoinfree(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*str;

	i = s1 ? ft_strlen(s1) : 0;
	j = s2 ? ft_strlen(s2) : 0;
	str = (char *)malloc(i + j + 1);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (n == 1 || n == 3)
		free(s1);
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	if (n == 2 || n == 3)
		free(s2);
	str[i + j] = '\0';
	return (str);
}

int		compare(char *s1, char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (1);
	if ((!s1 && s2) || (!s2 && s1))
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

char	*ft_strndup(char *str, int n)
{
	char	*s;
	int		i;

	i = str ? ft_strlen(str) : 0;
	if (i > n)
		i = n;
	s = (i != 0) ? (char *)malloc(i + 1) : NULL;
	i = 0;
	while (str && i < n && str[i])
	{
		s[i] = str[i];
		i++;
	}
	if (str)
		s[i] = 0;
	return (s);
}

int		ncomp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	if (!s1 && !s2)
		return (1);
	if ((!s1 && s2) || (!s2 && s1))
		return (0);
	i = 0;
	while (s1[i] && i < n && s1[i] == s2[i])
		i++;
	if (s1[i] && i < n)
		return (0);
	return (1);
}

int		j_b(t_pple *from, char *s)
{
	if (from->buff)
		from->buff = ft_strjoinfree(from->buff, s, 1);
	else
		from->buff = ft_strjoinfree(ft_strjoinfree(ft_strjoin("<", from->name)\
		, ">", 1), s, 1);
	if (ft_strchr(from->buff, '\n'))
		return (1);
	return (0);
}
