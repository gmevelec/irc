/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:39:57 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/06 16:39:59 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
#include "../../libft/libft.h"

static void		ft_connect(char *str)
{
	char	**tab;
	int		sock;

	tab = ft_strsplit(str, ' ');
	if (!tab[0] || !tab[1] || tab[2])
	{
		ft_putstr("Wrong usage\n");
		return ;
	}
	sock = create_client(tab[0], ft_atoi(tab[1]));
	ft_client(sock, name());
}

static void		do_select(int sock, fd_set *rdfs)
{
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(sock, rdfs);
	if (select(sock + 1, rdfs, NULL, NULL, NULL) == -1)
		exit_error("Select");
}

void			ft_client(int sock, char *name)
{
	char		buf[BUF_SIZE];
	fd_set		rdfs;

	write_server(sock, name);
	while (1)
	{
		do_select(sock, &rdfs);
		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			read_msg(buf);
			write_server(sock, buf);
			if (!ft_strncmp(buf, "/connect ", 9))
				ft_connect(buf + 9);
		}
		else if (FD_ISSET(sock, &rdfs))
		{
			if (read_serveur(sock, buf) == 0)
			{
				ft_putstr("Disconnected from serveur\n");
				break ;
			}
			ft_putstr(buf);
		}
	}
	close(sock);
}

int				create_client(char *addr, int port)
{
	int				sock;
	t_sockaddr_in	sin;
	struct hostent	*hostinfo;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		exit_error("Socket");
	hostinfo = gethostbyname(addr);
	if (hostinfo == NULL)
	{
		ft_putstr("Error: Unknow host ");
		ft_putstr(addr);
		ft_putstr(".\n");
		exit(-1);
	}
	sin.sin_addr = *(t_in_addr *)hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if (connect(sock, (t_sockaddr *)&sin, sizeof(t_sockaddr)) == -1)
		exit_error("Connect");
	return (sock);
}

int				main(int argc, char **argv)
{
	int		sock;

	if (argc != 3)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" <adress> <port>\n");
		exit(-1);
	}
	sock = create_client(argv[1], ft_atoi(argv[2]));
	ft_client(sock, name());
	return (0);
}
