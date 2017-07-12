/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 13:22:44 by jbert             #+#    #+#             */
/*   Updated: 2016/01/11 15:36:30 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERV_H
# define SERV_H

# include "libftprintf/printf.h"
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <sys/time.h>

typedef struct	s_pple
{
	char		*name;
	int			fd;
	char		*chan;
	char		*buff;
}				t_pple;

typedef struct	s_clt
{
	int			client_fd[42];
	int			mas_sock;
	t_pple		anon[42];
}				t_clt;

int				ret_sock(int p, struct sockaddr_in *saddr);
int				sock_error(int i);

char			*ft_strjoinfree(char *s1, char *s2, int n);
int				compare(char *s1, char *s2);
char			*ft_strndup(char *str, int n);
int				ncomp(char *s1, char *s2, unsigned int n);
int				j_b(t_pple *from, char *s);

void			s_to_all(char *s, t_pple *client, fd_set *fds, int from);
void			change_channel(char *s, t_pple *cl, int i, fd_set *fds);
void			change_nick(char *s, t_pple *cl, int i, fd_set *fds);
void			s_to_one(char *s, t_pple *f, t_pple *client);

void			print_all(t_pple *from, t_pple *client);
void			print_lst(t_pple *from, t_pple *client);
int				client_spec(char *buff, t_pple *client, int i, fd_set *fds);
void			client_act(fd_set *fds, t_pple *client);
void			mas_act(int m, t_pple *cl, struct sockaddr_in s, fd_set *fd);

#endif
