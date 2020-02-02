/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 08:33:07 by hbuisser          #+#    #+#             */
/*   Updated: 2019/12/18 16:07:28 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int get_next_line(int fd, char **line);
int ft_line_creation(char **stat, char **line, int idx);
char*ft_strnew(int end);
int ft_strnbr(char *stat);
int ft_free_stat(char **stat, int result);
int ft_strlen(const char *str);
char*ft_substr(char const *s, int start, int len);
char*ft_strdup(char *s1);
char*ft_strnjoin(char *s1, char *s2, int ret);

#endif
