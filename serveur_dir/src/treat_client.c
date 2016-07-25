/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 10:23:11 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/05 10:56:07 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

void		init_client(t_serveur *serveur, int actual, char *name, int csock)
{
	serveur->clients[actual].name = ft_strdup(name);
	serveur->clients[actual].sock = csock;
	serveur->clients[actual].channel = NULL;
}

int			new_client(t_serveur *serveur, int *actual, char *buf)
{
	int				csock;
	t_sockaddr_in	csin;
	socklen_t		sinsize;

	sinsize = sizeof(csin);
	csock = accept(serveur->sock, (t_sockaddr *)&csin, &sinsize);
	if (csock == -1)
		return (-1);
	if (read_client(csock, buf) == -1)
		return (-1);
	while (srv_check_name(buf, serveur) == -1)
	{
		write_client(csock, "\x1B[31mName already use.\033[0m\n");
		write_client(csock, "Enter your name: ");
		if (read_client(csock, buf) == -1)
			return (-1);
	}
	FD_SET(csock, &(serveur->rdfs));
	if (csock > serveur->max)
		serveur->max = csock;
	init_client(serveur, *actual, buf, csock);
	(*actual)++;
	return (csock);
}

void		delete_client(t_serveur *serveur, int *actual, int i)
{
	t_client	*clients;

	clients = serveur->clients;
	ft_memmove(clients + i, clients + i + 1,
		(*actual - i - 1) * sizeof(t_client));
	(*actual)--;
}

void		disconnect_client(t_serveur *serveur, int *actual, int i)
{
	char		*tmp;
	t_client	client;

	client = serveur->clients[i];
	serveur->clients[i].channel = NULL;
	close(serveur->clients[i].sock);
	delete_client(serveur, actual, i);
	if (client.name[0])
	{
		tmp = ft_strdup("\x1B[31m");
		tmp = ft_strjoin(tmp, client.name);
		tmp = ft_strjoin(tmp, " disconnected.\033[0m\n");
		i = 0;
		while (i < *actual)
		{
			if (!ft_strcmp(serveur->clients[i].channel, client.channel))
				write_client(serveur->clients[i].sock, tmp);
			i++;
		}
	}
	ft_bzero(client.name, 10);
}

void		close_clients(t_client *clients, int actual)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		close(clients[i].sock);
		i++;
	}
}
