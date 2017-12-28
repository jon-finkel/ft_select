/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:44:05 by nfinkel           #+#    #+#             */
/*   Updated: 2017/12/28 14:41:36 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <locale.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include "../libft/includes/libft.h"

typedef enum	s_flag
{
	E_ENABLE,
	E_DISABLE
}				t_flag;

typedef struct	s_data
{
	char		**argv;
	t_bool		*select;
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

int				color_output(t_data *data);
int				display_files(t_data *data);
int				display_help(t_data *data);
int				flag_reverse_video(t_flag flag);
int				flag_underline(t_flag flag);
void			get_coordinates(t_data *data);
int				input_arrow(t_data *data, const char *const buff);
int				loop(t_data *data);
int				restore_configuration(t_data *data);
void			signal_handler(int signo);

#endif
