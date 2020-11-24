/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 00:43:33 by larosale          #+#    #+#             */
/*   Updated: 2020/08/25 19:22:50 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/*
** These defines are for event codes that are being listened to.
*/

# define EV_KEYPRESS 2
# define EV_KEYRELEASE 3
# define EV_MOUSEMOVE 6
# define EV_EXIT 17

/*
** The enum type "t_keys" describe key codes of all keyboard buttons.
*/

typedef enum	e_keys
{
	MOUSE = -1,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_F = 3,
	KEY_H = 4,
	KEY_G = 5,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8,
	KEY_V = 9,
	KEY_B = 11,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_R = 15,
	KEY_Y = 16,
	KEY_T = 17,
	KEY_ONE = 18,
	KEY_TWO = 19,
	KEY_THREE = 20,
	KEY_FOUR = 21,
	KEY_SIX = 22,
	KEY_FIVE = 23,
	KEY_NINE = 25,
	KEY_SEVEN = 26,
	KEY_EIGHT = 28,
	KEY_ZERO = 29,
	KEY_BRACE_R = 30,
	KEY_O = 31,
	KEY_U = 32,
	KEY_BRACE_L = 33,
	KEY_I = 34,
	KEY_P = 35,
	KEY_L = 37,
	KEY_J = 38,
	KEY_K = 40,
	KEY_SEMI = 41,
	KEY_N = 45,
	KEY_M = 46,
	KEY_TAB = 48,
	KEY_ESC = 53,
	KEY_PLUS = 69,
	KEY_MINUS = 78,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126
}				t_keys;

typedef enum	e_events
{
	EV_KEY_A = 1,
	EV_KEY_S = 2,
	EV_KEY_D = 4,
	EV_KEY_W = 8,
	EV_KEY_LEFT = 16,
	EV_KEY_RIGHT = 32,
	EV_KEY_DOWN = 64,
	EV_KEY_UP = 128
}				t_events;

#endif
