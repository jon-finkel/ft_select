/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:44:05 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/27 16:07:49 by nfinkel          ###   ########.fr       */
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
	int			pos;
	int			padding;
	int			x;
	int			y;
	int			curr_column;
	int			columns;
	int			rows;
	int			extra;
	size_t		width;
}				t_data;

int				display_files(t_data *data);
int				input_key(t_data *data, const char *const buff);
int				restore_configuration(t_data *data);
void			signal_handler(int signo);

#endif
