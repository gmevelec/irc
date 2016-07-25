/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:38:28 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/06 16:38:31 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

# define BUF_SIZE 		(1024)

typedef struct sockaddr_in		t_sockaddr_in;
typedef struct sockaddr			t_sockaddr;
typedef struct in_addr			t_in_addr;

/*
** check.c
*/
int			check_name(char *name);
char		*name(void);

/*
** read_write.c
*/
void		read_msg(char *buf);
int			read_serveur(int sock, char *buf);
void		write_server(int sock, char *buf);

/*
** error.c
*/
void		exit_error(char *str);

/*
** client.c
*/
void		ft_client(int sock, char *name);
int			create_client(char *addr, int port);

#endif
