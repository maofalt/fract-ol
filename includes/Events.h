/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 15:48:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define MINUS_PAD 65453
# define PLUS_PAD 65451
# define ONE_PAD 65436
# define TWO_PAD 65433
# define THREE_PAD 65435
# define FOUR_PAD 65430
# define FIVE_PAD 65437
# define SIX_PAD 65432
# define MINUS_KEY 45
# define PLUS_KEY 61
# define BRACE_L_KEY 91
# define BRACE_R_KEY 93
# define D_KEY 100
# define C_KEY 99
# define X_KEY 122
# define Z_KEY 120

# include "Structures.h"

/*############################################################################*/
/*                  	     BUTTON PRESS FUNCTIONS                           */
/*############################################################################*/

	/*Destroys Window by pressing Esc buttons*/
void		ft_destroy_window_button(int keysym, t_data *data);

int			ft_handle_keypress(int keysym, t_data *data);
int			ft_handle_boutonpress(int buttonsym, int x, int y, t_data *data);
int			ft_handle_keyrelease(int keysym, t_data *data);
int			ft_destroy_window(t_data *data);

#endif