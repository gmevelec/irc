/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 10:56:35 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/05 11:03:13 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

# define MAX_CLIENTS 	(10)
# define MAX_CHANNELS 	(10)
# define BUF_SIZE 		(1024)

typedef struct sockaddr_in		t_sockaddr_in;
typedef struct sockaddr			t_sockaddr;
typedef struct in_addr			t_in_addr;

/*
** t_client
*/
typedef struct		s_client
{
	int			sock;
	char		*name;
	char		*channel;
}					t_client;

/*
** t_serveur
*/
typedef struct		s_serveur
{
	int			sock;
	int			max;
	fd_set		rdfs;
	t_client	clients[MAX_CLIENTS];
}					t_serveur;

typedef struct		s_ptr
{
	void	(*func)();
	char	*cmd;
	int		len;
}					t_ptr;

/*
** serveur.c
*/
int					get_socket(t_serveur *serveur, t_client *client,
						char *name);

/*
** check.c
*/
int					srv_check_name(char *name, t_serveur *serveur);
int					check_channel(t_client *client, char *channel);
int					check_nick(t_serveur *serveur, t_client *client, char *buf);
int					is_not_in(char **channels, char *chan);

/*
** msg.c
*/
void				write_client(int sock, char *buf);
void				serveur_to_chan(t_serveur *serveur, t_client *client,
							char *buf);
void				serveur_to_all(t_client *dest, t_client writer, int actual,
							char *buf);
void				client_to_all(t_client *dest, t_client writer, int actual,
							char *buf);
int					read_client(int sock, char *buf);

/*
** msg_2.c
*/
void				welcome(t_serveur serv, int n);
char				*get_msg(char *name, char *str, char *buf);
void				invite_msg(t_serveur *serveur, t_client *client,
					char *buf, int sock);
void				list_msg(int sock, char **channels, int j);

/*
** treat_client.c
*/
void				init_client(t_serveur *serveur, int actual,
							char *name, int csock);
int					new_client(t_serveur *serveur, int *actual, char *buf);
void				delete_client(t_serveur *serveur, int *actual, int i);
void				disconnect_client(t_serveur *serveur, int *actual, int i);
void				close_clients(t_client *clients, int actual);

/*
** cmd.c
*/
void				nick(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				msg(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				leave(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				join(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				who(t_serveur *serveur, t_client *client,
					char *buf, int actual);

/*
** cmd_2.c
*/
void				help(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				invite(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				me(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				list(t_serveur *serveur, t_client *client,
					char *buf, int actual);
void				quit(t_serveur *serveur, t_client *client,
					char *buf, int *actual);

static const t_ptr	g_ptr[10] =
{
	{&nick, "/nick ", 6},
	{&msg, "/msg ", 5},
	{&join, "/join ", 6},
	{&leave, "/leave ", 7},
	{&who, "/who\0", 5},
	{&invite, "/invite ", 8},
	{&me, "/me ", 4},
	{&list, "/list\0", 6},
	{&help, "/help\0", 6},
	{NULL, NULL, 0}
};

/*
** init.c
*/
void				init_fds(t_serveur *serveur, int actual);
void				init_serveur(t_serveur *serveur, int sock);
int					create_serveur(int port);

/*
** error.c
*/
void				exit_error(char *str);

#endif
