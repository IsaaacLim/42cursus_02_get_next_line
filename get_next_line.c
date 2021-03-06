#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str++ = '\0';
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mal;

	mal = (void *)malloc(count * size);
	if (!mal)
		return (NULL);
	ft_bzero(mal, count * size);
	return (mal);
}

int	line_sep(char **line, char **arr, int ret)
{	
	char	*temp;
	int		i;

	i = 0;
	while ((*arr)[i] != '\n' && (*arr)[i] != '\0')
		i++;
	if ((*arr)[i] == '\n')
	{
		*line = ft_substr(*arr, 0, i);
		temp = ft_strdup((*arr) + i + 1);
		free(*arr);
		*arr = temp;
	}
	else if ((*arr)[i] == '\0')
	{
		*line = ft_strdup(*arr);
		ft_bzero(*arr, ft_strlen(*arr));
		free(*arr);
		*arr = NULL;
	}
	if (ret == 0 && *arr == NULL)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*arr;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!arr)
		arr = (char *)ft_calloc(1, 1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0 )
	{
		buf[ret] = '\0';
		temp = ft_strjoin(arr, buf);
		free(arr);
		arr = temp;
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (ret < 0)
		return (-1);
	return (line_sep(line, &arr, ret));
}
