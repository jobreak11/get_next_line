/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeepach <gyeepach@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:15:04 by gyeepach          #+#    #+#             */
/*   Updated: 2024/04/30 11:39:29 by gyeepach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*get_new_line(t_list *list);
void	clean_list(t_list **list);
char	create_list(t_list **list, int fd);
int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	dealloc(t_list **list, t_list *clean_node, char *buf);

#endif