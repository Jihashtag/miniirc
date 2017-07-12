/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 05:48:04 by jbert             #+#    #+#             */
/*   Updated: 2016/01/11 15:43:37 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf/printf.h"
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int		change_add(struct sockaddr_in *saddr, char *h)
{
	char	*new;

	if (h[0] == 'e' && h[2] == 'r' && ft_strchr(h, 'p'))
	{
		new = (char *)malloc(11);
		new[0] = '1';
		new[1] = '0';
		new[2] = '.';
		new[3] = '1';
		new[4] = h[1];
		new[5] = '.';
		new[6] = h[3];
		new[7] = h[4] == 'p' ? '.' : h[4];
		new[8] = h[4] == 'p' ? h[5] : '.';
		new[9] = h[6];
		new[10] = h[6] ? h[7] : '\0';
		new[11] = '\0';
		saddr->sin_addr.s_addr = inet_addr(new);
		free(new);
		return (1);
	}
	return (0);
}

int		ft_initall(char *host, int p)
{
	int					s;
	struct protoent		*prot;
	struct sockaddr_in	saddr;

	prot = getprotobyname("tcp");
	if (!prot)
		return (-1);
	s = socket(PF_INET, SOCK_STREAM, prot->p_proto);
	if (s == -1)
		return (-3);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(p);
	if (!ft_strncmp(host, "localhost", 9))
		saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	else if (!change_add(&saddr, host))
		saddr.sin_addr.s_addr = inet_addr(host);
	if (connect(s, (const struct sockaddr *)&saddr, sizeof(saddr)) != 0)
		return (-2);
	return (s);
}

int		print_all(int master, int s)
{
	char	buff[1025];
	int		ret;

	if (s == 1)
	{
		while ((ret = recv(master, buff, 1024, 0)) == 1024)
			write(1, buff, ret);
		if (ret == 0)
		{
			close(master);
			return (-1);
		}
		write(1, buff, ret);
	}
	if (s == 2)
	{
		ret = read(0, buff, 1024);
		if (ret >= 1024)
		{
			ft_putendl_fd("Line too long", 2);
			return (0);
		}
		ret == 0 ? send(master, "/quit\n", 5, 0) : send(master, buff, ret, 0);
	}
	return (master);
}

int		connect_again(void)
{
	int		m;
	int		ret;
	char	b[1025];

	ret = read(0, b, 1024);
	b[ret] = '\0';
	if (!ft_strcmp(b, "quit\n") || !ft_strcmp("exit\n", b) || ret == 0)
		exit(0);
	if (ft_strncmp("/connect ", b, 9))
	{
		ft_putendl_fd("Please connect first\nUsage: /connect <ip> <port>", 2);
		return (-1);
	}
	if (ft_strchr(b, ' ') && ft_strrchr(b, ' '))
		m = ft_initall(ft_strchr(b, ' ') + 1, ft_atoi(ft_strrchr(b, ' ') + 1));
	else
		m = -1;
	if (m > 0)
		return (m);
	ft_putendl_fd("Please connect first\nUsage: /connect <ip> <port>", 2);
	return (-1);
}

int		main(int ac, char **av)
{
	int		mas;
	fd_set	fds[2];

	mas = (ac >= 3) ? ft_initall(av[1], ft_atoi(av[2])) : -1;
	while (1)
	{
		FD_ZERO(&fds[0]);
		FD_ZERO(&fds[1]);
		if (mas > 0)
			FD_SET(mas, &fds[0]);
		if (mas > 0)
			FD_SET(mas, &fds[1]);
		FD_SET(0, &fds[0]);
		if (select(mas > 0 ? mas + 1 : 1, &fds[0], &fds[1], NULL, NULL) < 0)
			ft_putendl_fd("select Error", 2);
		if (mas > 0 && FD_ISSET(mas, &fds[0]))
			mas = print_all(mas, 1);
		if (mas > 0 && FD_ISSET(0, &fds[0]) && FD_ISSET(mas, &fds[1]))
			print_all(mas, 2);
		else if (FD_ISSET(0, &fds[0]))
			mas = connect_again();
	}
	return (0);
}
