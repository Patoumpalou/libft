/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pihouvie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 20:10:42 by pihouvie          #+#    #+#             */
/*   Updated: 2017/12/20 19:13:23 by pihouvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_checkline(char *tab, char **bite, int ret)
{
	int	i;

//	printf("tab = |%s| ", tab);
	i = 0;
	while (tab[i] != '\n' &&ret--)
	{	
		i++;
//		printf("i = %i\n", i-1);
	}
	if (tab[i] && tab[i] == '\n')
	{
		*bite = ft_strsub(tab, i+1, BUFF_SIZE);// bite == ce quil reste dans le buffer qand on enleve line
	//	printf(" >>%s<< ", *bite);
		getchar();
		tab[i] = '\0';
		return(i+1) ;
	}
	if (ret < BUFF_SIZE)
	{
		printf("heeeeeeeeeeeeein\n");
		return(-1);
	}
	return(0);
}
// what if pas de \n dans le buff ? 
int		get_next_line(const int fd, char **line)
{
	static char	buff[BUFF_SIZE + 1];	
	int		 ret;
	char	*tmp;
	int		couille;
	char	*bite;

	ret = 0;
	bite = NULL;
	couille = 0;
	if (fd < 0 || fd > 12287 || !line)
		return (-1);
	if (buff[0])
	{
//		printf("buff = |%s|\n", buff);
		if((couille = ft_checkline(buff, &bite, ret)) > 0) //il y a un \n dans buff
		{
//			printf("couuuuuuuuu %i uuuuuuuuuu\n", couille);
			*line = ft_strndup(buff, couille); 
			ft_strcpy(buff, bite);// met se quil reste dans buff
	
			return (1);
		}
		else
			*line = ft_strdup(buff);
	}
	else
	{
		*line = ft_memalloc(1);
	}
	while(couille == 0 && ((ret = read(fd, buff, BUFF_SIZE)) > 0))
	{
		printf("ret = %i\n", ret);
		buff[ret] = '\0';
		couille = ft_checkline(buff, &bite, ret);
		tmp = ft_strjoin(*line, buff);
		free(*line);
		*line = tmp;
	if (couille > 0)
		{
	//		printf(" >>%s<< ", bite);
			ft_strcpy(buff, bite);
//			free(bite);
		}
	}
	if (ret == -1)
		return (-1);
	if (couille == -1)
	{
			ft_bzero(buff, BUFF_SIZE);
			return (1);
	}
	if (ret == 0 && buff[0] == '\0')
		return (0);
	return (1);
}
