/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:44:05 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/26 23:45:18 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <locale.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>
# include "../libft/includes/libft.h"

typedef struct	s_data
{
	char		**argv;
	int			argc;
	int			rows;
	int			columns;
	size_t		width;
}				t_data;

int				display_files(t_data *data);
void			signal_handler(int signo);

#endif
