/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palaca <palaca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:19:52 by palaca            #+#    #+#             */
/*   Updated: 2024/12/20 09:38:06 by palaca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *read_fd(int fd, char *buffer, char *buf)
{
	int i;

	i = 1;
	while(i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if(i < 0)
			return( NULL);
		if(i == 0)
			break;
		buffer[i] = '\0';
		if(!buf)
		{
			buf = malloc(sizeof(char) * 1);
			buf[0] = '\0';
		}
		buf = ft_strjoin(buf, buffer);
		if(ft_strchr(buffer, '\n'))
			break;
	}
	return(buf);
}
static char *find_line(char *tmp)
{
	int i;
	char *next_line;

	i = 0;
	while(tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	if(tmp[i] == '\0')
		return(NULL);
	next_line = ft_substr(tmp, i + 1, ft_strlen(tmp) - i);
	tmp[i + 1] = '\0';
	if(next_line[0] == '\0')
	{
		free(next_line);
		next_line = NULL;
	}
	return(next_line);
	
}

char *get_next_line(int fd)
{
	char *buffer;
	char *tmp[1024];
	static char *buf[1024];
	
	if(fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	if(!buffer)
		return(free(buffer), NULL);
	tmp[fd] = read_fd(fd, buffer, buf[fd]);
	free(buffer);
	if(!tmp[fd])
	{
		free(buf);
		return(NULL);
	}
	buf[fd] = find_line(tmp[fd]);
	if (!buf)
        free(tmp);
	return(tmp[fd]);
}