/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:27:11 by mchemari          #+#    #+#             */
/*   Updated: 2025/07/16 16:36:45 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*remove_processed(char *stash);
char	*extract_line(char *stash);
char	*load_file_content(int fd, char *stash);
char	*get_next_line(int fd);
int		ft_strlen_n(char *str);
char	*ft_strjoin_n(char *s1, char *s2);
int		ft_strchr_n(char *str);

#endif
