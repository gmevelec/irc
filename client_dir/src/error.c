/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:43:30 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/06 16:43:30 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
#include "../../libft/libft.h"

void	exit_error(char *str)
{
	ft_putstr("\x1B[31m");
	ft_putstr(str);
	ft_putstr(" error\033[0m\n");
	exit(-1);
}
