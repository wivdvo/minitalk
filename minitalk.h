/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:54:00 by wvan-der          #+#    #+#             */
/*   Updated: 2023/11/02 15:54:18 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

int		ft_printf(const char *str, ...);
void	ft_printf_c(int c, int *count);
void	ft_printf_s(char *s, int *count);
void	ft_printf_d(int n, int *count);
void	ft_printf_u(unsigned int nb, int *count);
void	ft_printf_x(unsigned int nb, int *count);
void	ft_printf_x_cap(unsigned int nb, int *count);
void	ft_printf_p(void *ptr, int *count);

#endif
