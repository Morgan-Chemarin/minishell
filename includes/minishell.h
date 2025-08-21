/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:38 by dev               #+#    #+#             */
/*   Updated: 2025/08/20 21:57:13 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>

# include "struct.h"
# include "prototypes.h"
# include "colors.h"

extern int	g_last_status_exit;

#endif