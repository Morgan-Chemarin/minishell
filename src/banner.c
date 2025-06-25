/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:52:52 by dev               #+#    #+#             */
/*   Updated: 2025/06/24 18:59:18 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_line_centered(const char *line, int width)
{
	int	padding;
	int	i = 0;
	
	padding = (width - (int)ft_strlen(line)) / 2;
	if (padding < 0)
		padding = 0;
	while (i++ < padding)
		write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, line, ft_strlen(line));
	write(STDOUT_FILENO, "\n", 1);
}

void	print_ascii_banner(void)
{
	const char	*banner[] = {
		GREEN     " _____ _____    _    __  __        _   _    _    ____  ____    _    ____  " RESET,
		GREEN   "|_   _| ____|  / \\  |  \\/  |      | \\ | |  / \\  / ___||  _ \\  / \\  / ___| " RESET,
		GREEN  "  | | |  _|   / _ \\ | |\\/| |      |  \\| | / _ \\ \\___ \\| | | |/ _ \\ \\___ \\ " RESET,
		GREEN    "  | | | |___ / ___ \\| |  | |      | |\\  |/ ___ \\ ___) | |_| / ___ \\ ___) |" RESET,
		GREEN "  |_| |_____/_/   \\_\\_|  |_|      |_| \\_/_/   \\_\\____/|____/_/   \\_\\____/ " RESET,
		NULL
	};
	struct winsize	ws;
	int				i = 0;
	int				banner_lines = 5;
	int				total_padding;
	int				top_padding;
	int				bottom_padding;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		ws.ws_col = 80;
		ws.ws_row = 24;
	}
	total_padding = ws.ws_row - banner_lines;
	if (total_padding < 0)
		total_padding = 0;
	top_padding = total_padding / 2;
	bottom_padding = total_padding - top_padding;
	while (top_padding-- > 0)
		write(STDOUT_FILENO, "\n", 1);
	while (banner[i])
		print_line_centered(banner[i++], ws.ws_col);
	while (bottom_padding-- > 0)
		write(STDOUT_FILENO, "\n", 1);
}
