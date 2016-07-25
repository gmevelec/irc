/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 10:49:52 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/05 11:12:08 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

int				get_socket(t_serveur *serveur, t_client *client, char *name)
{
	int		i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (serveur->clients[i].name)
		{
			if (!ft_strcmp(serveur->clients[i].name, name) &&
				!ft_strcmp(serveur->clients[i].channel,
					client->channel))
				return (serveur->clients[i].sock);
		}
		i++;
	}
	return (-1);
}

static void		cmd(t_serveur *serv, t_client *client, char *buf, int *actual)
{
	int		i;
	int		n;
	char	*msg;

	n = 0;
	i = -1;
	while (g_ptr[++i].cmd)
	{
		if (!ft_strncmp(g_ptr[i].cmd, buf, g_ptr[i].len))
		{
			g_ptr[i].func(serv, client, buf + g_ptr[i].len, *actual);
			n = 1;
		}
	}
	if (!ft_strcmp(buf, "/quit") || !ft_strncmp(buf, "/connect ", 9))
	{
		quit(serv, client, buf, actual);
		n = 1;
	}
	if (n == 0)
	{
		msg = ft_strdup("\x1B[32mCommand not found.\n");
		msg = ft_strjoin(msg, "Use /help to see help.\033[0m\n");
		write_client(client->sock, msg);
	}
}

static void		treat_data(t_serveur *serveur, int *n,
					char *buf)
{
	int		i;

	i = 0;
	while (i < *n)
	{
		if (FD_ISSET(serveur->clients[i].sock, &(serveur->rdfs)))
		{
			if (read_client(serveur->clients[i].sock, buf) == 0)
				disconnect_client(serveur, n, i);
			else if (buf[0] == '/')
				cmd(serveur, serveur->clients + i, buf, n);
			else
				client_to_all(serveur->clients, serveur->clients[i], *n, buf);
			break ;
		}
		i++;
	}
}

static void		serveur(int sock)
{
	char		buf[BUF_SIZE];
	t_serveur	serveur;
	int			actual;

	actual = 0;
	init_serveur(&serveur, sock);
	while (1)
	{
		init_fds(&serveur, actual);
		if (select(serveur.max + 1, &serveur.rdfs, NULL, NULL, NULL) == -1)
			exit_error("Select");
		if (FD_ISSET(STDIN_FILENO, &serveur.rdfs))
			break ;
		else if (FD_ISSET(serveur.sock, &serveur.rdfs))
		{
			if (new_client(&serveur, &actual, buf) == -1)
				continue ;
			else
				welcome(serveur, actual);
		}
		else
			treat_data(&serveur, &actual, buf);
	}
	close_clients(serveur.clients, actual);
	close(serveur.sock);
}

int				main(int argc, char **argv)
{
	int		sock;

	if (argc != 2)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" <port>\n");
		exit(-1);
	}
	sock = create_serveur(ft_atoi(argv[1]));
	serveur(sock);
	return (0);
}
