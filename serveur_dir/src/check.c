/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 10:43:01 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/05 11:50:54 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

int			check_channel(t_client *client, char *channel)
{
	if (!ft_strcmp(client->channel, channel))
		return (1);
	return (0);
}

int			srv_check_name(char *name, t_serveur *serveur)
{
	int		i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (serveur->clients[i].name)
		{
			if (!ft_strcmp(serveur->clients[i].name, name))
				return (-1);
		}
		i++;
	}
	return (0);
}

int			check_nick(t_serveur *serveur, t_client *client, char *buf)
{
	int		i;

	if (srv_check_name(buf, serveur) == -1)
	{
		write_client(client->sock, "\x1B[31mName already use.\033[0m\n");
		return (1);
	}
	if (ft_strlen(buf) == 0 || ft_strlen(buf) > 9)
	{
		write_client(client->sock, "\x1B[31mWrong name.\033[0m\n");
		return (1);
	}
	i = 0;
	while (buf[i])
	{
		if (ft_isprint(buf[i]) && buf[i] != ' ')
			i++;
		else
		{
			write_client(client->sock, "\x1B[31mWrong name.\033[0m\n");
			return (1);
		}
	}
	return (0);
}

int			is_not_in(char **channels, char *chan)
{
	int		i;

	i = 0;
	while (channels[i] && chan)
	{
		if (!ft_strcmp(channels[i], chan))
			return (0);
		i++;
	}
	return (1);
}
