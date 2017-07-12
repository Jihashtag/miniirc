/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 13:26:00 by jbert             #+#    #+#             */
/*   Updated: 2016/01/10 13:26:21 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

int		ret_sock(int p, struct sockaddr_in *saddr)
{
	int					s;
	struct protoent		*prot;

	if (p <= 0)
		return (0);
	prot = getprotobyname("tcp");
	if (!prot)
		return (-1);
	s = socket(PF_INET, SOCK_STREAM, prot->p_proto);
	if (s == -1)
		return (0);
	saddr->sin_family = AF_INET;
	saddr->sin_port = htons(p);
	saddr->sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (const struct sockaddr *)saddr, sizeof(*saddr)) != 0)
		return (-2);
	if (listen(s, 42) != 0)
		return (-3);
	return (s);
}

int		sock_error(int i)
{
	if (i == 0)
		return (ft_putstr_fd("Error : could not create socket\n", 2));
	if (i == -1)
		return (ft_putstr_fd("Error : could not get protocol by name\n", 2));
	if (i == -2)
		return (ft_putstr_fd("Error : could not bind\n", 2));
	if (i == -3)
		return (ft_putstr_fd("Error : could not listen\n", 2));
	return (-1);
}
