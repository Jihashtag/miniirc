/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 17:21:33 by jbert             #+#    #+#             */
/*   Updated: 2016/01/11 14:28:31 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

int		init_for_sel(fd_set *fds, int master, t_pple *client)
{
	int	max_fds;
	int	i;

	FD_ZERO(&fds[0]);
	FD_ZERO(&fds[1]);
	FD_SET(master, &fds[0]);
	FD_SET(master, &fds[1]);
	max_fds = master;
	i = 0;
	while (i < 42)
	{
		if (client[i].fd > 0)
		{
			FD_SET(client[i].fd, &fds[0]);
			FD_SET(client[i].fd, &fds[1]);
		}
		if (client[i].fd > max_fds)
			max_fds = client[i].fd;
		i++;
	}
	return (max_fds + 1);
}

int		main(int ac, char **av)
{
	static t_clt		cl = {{0}, 0, {{0, 0, 0, 0}}};
	struct sockaddr_in	saddr;
	fd_set				fds[2];

	if (ac < 2)
		return (ft_putendl_fd("Usage : ./server <port> [opts]", 2));
	cl.mas_sock = ret_sock(ft_atoi(av[1]), &saddr);
	if (cl.mas_sock <= 0)
		return (sock_error(cl.mas_sock));
	while (1)
	{
		if (select(init_for_sel(fds, cl.mas_sock, cl.anon), \
				&fds[0], &fds[1], NULL, NULL) < 0)
			return (ft_putendl_fd("select error", 2));
		if (FD_ISSET(cl.mas_sock, &fds[0]))
			mas_act(cl.mas_sock, cl.anon, saddr, fds);
		client_act(fds, cl.anon);
	}
	return (0);
}
