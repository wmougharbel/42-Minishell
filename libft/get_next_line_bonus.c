/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:52:31 by cmenke            #+#    #+#             */
/*   Updated: 2023/03/02 15:08:15 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//reads the file for BUFFER_SIZE and returns NULL on error.
static char	*ft_read_line(int fd, int *inf)
{
	char	*buffer;
	int		read_ret;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_ret = read(fd, buffer, BUFFER_SIZE);
	if (read_ret == -1)
	{
		free(buffer);
		return (NULL);
	}
	else if (read_ret == 0)
		*inf = 0;
	buffer[read_ret] = '\0';
	return (buffer);
}

//returns the line for either '\0' or '\n'.
static char	*ft_return_line(char **remainder, int *inf, char *spot)
{
	char	*line;
	char	*temp;

	line = NULL;
	temp = NULL;
	if (*remainder && *inf == 0)
		spot = ft_strchr(*remainder, '\0');
	line = ft_substr(*remainder, 0, spot - *remainder + *inf);
	if (line && *inf == 1)
		temp = ft_strjoin(spot + *inf, "");
	free(*remainder);
	*remainder = temp;
	return (line);
}

//checks the remainder for '\n' and if not found calls read.
//if a line was read it will be combined with the remainder and checked again.
//if EOF is reached the return line function gets called to check for '\0'.
static char	*ft_check_remainder(char **remainder, int fd, int *inf)
{
	char	*line;
	char	*temp;
	char	*spot;

	spot = NULL;
	if (*remainder && *inf == 1)
		spot = ft_strchr(*remainder, '\n');
	if (!spot && *inf == 1)
	{
		line = ft_read_line(fd, inf);
		if (!line)
			return (NULL);
		temp = ft_strjoin(*remainder, line);
		if (!temp)
			return (NULL);
		free(*remainder);
		free(line);
		*remainder = temp;
		line = ft_check_remainder(remainder, fd, inf);
	}
	else
		line = ft_return_line(remainder, inf, spot);
	return (line);
}

//checks if the remainder is empty and if so it will read a line.
//then calls check remainder and frees remainder in case of error.
//create a multidimensional array for the different fd_remainders
//remainder array of size [1024]
char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	int			inf;

	inf = 1;
	line = NULL;
	if (fd == -1 || fd > 1023)
		return (NULL);
	if (!remainder[fd])
		remainder[fd] = ft_read_line(fd, &inf);
	if (remainder[fd])
		line = ft_check_remainder(&remainder[fd], fd, &inf);
	if (!line)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
	}
	return (line);
}
