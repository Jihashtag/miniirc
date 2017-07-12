/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 13:28:19 by jbert             #+#    #+#             */
/*   Updated: 2016/01/11 15:36:32 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

void	print_all(t_pple *from, t_pple *client)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin("Members in : ", from->chan);
	while (i < 42)
	{
		if (compare(client[i].chan, from->chan))
		{
			tmp = ft_strjoinfree(tmp, client[i].name, 1);
			tmp = ft_strjoinfree(tmp, "\n", 1);
		}
		i++;
	}
	send(from->fd, tmp, ft_strlen(tmp), 0);
	free(tmp);
}

void	print_lst(t_pple *from, t_pple *client)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("Channel list :\n");
	while (i < 42)
	{
		if (client[i].fd && !ft_strstr(tmp, client[i].chan))
			tmp = ft_strjoinfree(tmp, client[i].chan, 1);
		i++;
	}
	send(from->fd, tmp, ft_strlen(tmp), 0);
	free(tmp);
}

int		client_spec(char *buff, t_pple *client, int i, fd_set *fds)
{
	if (buff[0] == '*')
		s_to_all(ft_strjoinfree(ft_strjoin("*", client[i].name), buff + 1, 1), \
				client, fds, i);
	else if (!ft_strncmp(buff, "/nick ", 6))
		change_nick(&(buff[6]), client, i, fds);
	else if (!ft_strncmp(buff, "/join ", 6))
		change_channel(&(buff[6]), client, i, fds);
	else if (!ft_strncmp(buff, "/leave", 6))
		change_channel("General\n", client, i, fds);
	else if (!ft_strncmp(buff, "/msg ", 5))
		s_to_one(&(buff[5]), &(client[i]), client);
	else if (!ft_strncmp(buff, "/who", 4))
		print_all(&(client[i]), client);
	else if (!ft_strncmp(buff, "/list", 5))
		print_lst(&(client[i]), client);
	else if (!ft_strncmp(buff, "/quit", 5))
	{
		s_to_all(ft_strjoin(client[i].name, "disconnected\n"), \
				client, fds, i);
		close(client[i].fd);
		client[i].fd = 0;
	}
	else
		return (0);
	return (1);
}

void	client_act(fd_set *fds, t_pple *c)
{
	int		i;
	int		ret;
	char	buf[1025];

	i = 0;
	ret = 1025;
	while (i < 42)
	{
		if (FD_ISSET(c[i].fd, &fds[0]))
		{
			ft_bzero(buf, ret);
			if ((ret = recv(c[i].fd, buf, 1024, 0)) <= 0)
			{
				s_to_all(ft_strjoin(c[i].name, "disconnected\n"), c, fds, i);
				close(c[i].fd);
				c[i].fd = 0;
			}
			else if (!client_spec(buf, c, i, fds) && j_b(&c[i], buf))
			{
				s_to_all(c[i].buff, c, fds, i);
				c[i].buff = 0;
			}
		}
		i++;
	}
}

void	mas_act(int mas_sock, t_pple *cl, struct sockaddr_in saddr, fd_set *fd)
{
	int				i;
	int				nsock;
	unsigned int	fd_len;
	char			*tmp;

	if ((nsock = accept(mas_sock, (struct sockaddr *)&saddr, &fd_len)) < 0)
		ft_putendl_fd("Accept error", 2);
	else
	{
		i = 0;
		while (i < 42 && cl[i].fd != 0)
			i++;
		cl[i].fd = nsock;
		tmp = ft_itoa(nsock);
		cl[i].name = ft_strjoin("anon", tmp);
		free(tmp);
		tmp = ft_strjoin(cl[i].name, ": ");
		free(cl[i].name);
		cl[i].name = tmp;
		change_channel("General\n", cl, i, fd);
	}
}
