/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:38 by dev               #+#    #+#             */
/*   Updated: 2025/08/12 17:49:41 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <stdio.h>
# include <stdlib.h>
// # include <errno.h>
// # include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
// # include <sys/ioctl.h>

# include <unistd.h>
# include <fcntl.h>
// # include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "struct.h"
# include "prototypes.h"
# include "colors.h"

extern int	g_last_status_exit;

#endif