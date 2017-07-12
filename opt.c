/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 13:27:44 by jbert             #+#    #+#             */
/*   Updated: 2016/01/11 15:17:40 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

void	s_to_all(char *s, t_pple *client, fd_set *fds, int from)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < 42)
	{
		if (FD_ISSET(client[i].fd, &fds[1]) && \
				compare(client[i].chan, client[from].chan))
			send(client[i].fd, s, len, 0);
		i++;
	}
	free(s);
}

void	change_channel(char *s, t_pple *cl, int i, fd_set *fds)
{
	char	*tmp;

	if (cl[i].chan && ft_strcmp(cl[i].chan, "General\n"))
	{
		tmp = ft_strjoinfree("*", \
				ft_strndup(cl[i].name, ft_strlen(cl[i].name) - 2), 2);
		tmp = ft_strjoinfree(tmp, " has left ", 1);
		tmp = ft_strjoinfree(tmp, cl[i].chan, 1);
		tmp = ft_strjoinfree(tmp, "\n", 1);
		s_to_all(tmp, cl, fds, i);
	}
	free(cl[i].chan);
	cl[i].chan = ft_strndup(s, 20);
	tmp = ft_strjoinfree("*", \
			ft_strndup(cl[i].name, ft_strlen(cl[i].name) - 2), 2);
	tmp = ft_strjoinfree(tmp, " has join ", 1);
	tmp = ft_strjoinfree(tmp, cl[i].chan, 1);
	tmp = ft_strjoinfree(tmp, "\n", 1);
	s_to_all(tmp, cl, fds, i);
}

void	change_nick(char *s, t_pple *cl, int i, fd_set *fds)
{
	char	*tmp;
	char	*msg;

	msg = ft_strjoin(cl[i].name, "is now known as : ");
	if (ft_strlen(s) >= 2)
	{
		free(cl[i].name);
		cl[i].name = ft_strndup(s, 9);
		cl[i].name[ft_strlen(cl[i].name) - 1] = ':';
		tmp = ft_strjoin(cl[i].name, " ");
		free(cl[i].name);
		cl[i].name = tmp;
	}
	msg = ft_strjoinfree(msg, ft_strndup(cl[i].name, \
				ft_strlen(cl[i].name) - 2), 1);
	msg = ft_strjoinfree(msg, "\n", 1);
	s_to_all(msg, cl, fds, i);
}

void	s_to_one(char *s, t_pple *f, t_pple *client)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while (i < 42 && \
			ncomp(client[i].name, s, ft_strlen(client[i].name) - 2) == 0)
		i++;
	if (i == 42)
		return ;
	tmp = ft_strjoin("[", f->name);
	tmp1 = ft_strjoin(tmp, "]");
	free(tmp);
	tmp = ft_strjoin(tmp1, &s[ft_strlen(client[i].name) - 2]);
	free(tmp1);
	send(client[i].fd, tmp, ft_strlen(tmp), 0);
	free(tmp);
}
