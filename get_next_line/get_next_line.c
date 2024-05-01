/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeepach <gyeepach@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:12:47 by gyeepach          #+#    #+#             */
/*   Updated: 2024/04/30 16:22:22 by gyeepach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->data[i] && last_node->data[i] != '\n')
		++i;
	while (last_node->data[i] && last_node->data[++i])
		buf[j++] = last_node->data[i];
	buf[j] = '\0';
	clean_node->data = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_new_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	connect_list(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		free(buf);
		return ;
	}
	last_node = find_last_node(*list);
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->data = buf;
	new_node->next = NULL;
}

char	create_list(t_list **list, int fd)
{
	int		already_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (0);
		already_read = read(fd, buf, BUFFER_SIZE);
		if (!already_read)
		{
			free(buf);
			buf = NULL;
			return (0);
		}
		if (already_read < 0)
		{
			free(buf);
			buf = NULL;
			return (1);
		}
		buf[already_read] = '\0';
		connect_list(list, buf);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	t_list			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (create_list(&list, fd))
	{
		while (list)
		{
			temp = list->next;
			free(list->data);
			free(list);
			list = temp;
		}
		return (NULL);
	}
	if (list == NULL)
		return (NULL);
	next_line = get_new_line(list);
	clean_list(&list);
	return (next_line);
}

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;
// 	int no = 1;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%i: %s", no, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		no++;
// 	}
// 	close(fd);
// 	return (0);
// }