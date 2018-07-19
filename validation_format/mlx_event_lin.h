/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_lin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:19:28 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/19 15:20:40 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EVENT_LIN_H
# define MLX_EVENT_LIN_H

/*
** for keypad int codes /usr/include/X11/keysymdef.h
*/

/*
**# define XK_KP_Space					0x0020
**# define XK_KP_Tab						0xff89 //?
**# define XK_KP_Enter					0xff8d
**# define XK_KP_Left						0xff51
**# define XK_KP_Up						0xff52
**# define XK_KP_Right					0xff53
**# define XK_KP_Down						0xff54
**# define XK_KP_PageUp					0xff55
**# define XK_KP_PageDown					0xff56
**# define XK_KP_Esc						0xff1b
**# define XK_KP_LCtrl					0xffe3
*/
# define L_CLICK		0x1
# define M_CLICK		0x2
# define R_CLICK		0x3
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

# define KEY_ESC		0xFF1B
# define KEY_SPACE		0x0020
# define KEY_LCTRL		0xFFE3

# define KEY_LEFT		0xFF51
# define KEY_UP			0xFF52
# define KEY_RIGHT		0xFF53
# define KEY_DOWN		0xFF54
# define KEY_PAGE_UP	0xFF55
# define KEY_PAGE_DN	0xFF56

# define KEY_HOME		0xFF50
# define KEY_END		0xFF57
# define KEY_INSERT		0xFF63
# define KEY_DELETE		0xFFFF

# define KEY_NUMPAD_0		0xFF9E
# define KEY_NUMPAD_1		0xFF9C
# define KEY_NUMPAD_2		0xFF99
# define KEY_NUMPAD_3		0xFF9B
# define KEY_NUMPAD_4		0xFF96
# define KEY_NUMPAD_5		0xFF9D
# define KEY_NUMPAD_6		0xFF98
# define KEY_NUMPAD_7		0xFF95
# define KEY_NUMPAD_8		0xFF97
# define KEY_NUMPAD_9		0xFF9A
# define KEY_NUMPAD_PERIOD	0xFF9F
# define KEY_NUMPAD_ENTER	0xFF8D
# define KEY_NUMPAD_ADD		0xFFAB
# define KEY_NUMPAD_SUB		0xFFAD
# define KEY_NUMPAD_MUL		0xFFAA
# define KEY_NUMPAD_DIV		0xFFAF

#endif
