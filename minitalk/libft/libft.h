/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:19:21 by oucan             #+#    #+#             */
/*   Updated: 2025/01/13 17:39:33 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <unistd.h>

void	ft_putstr(const char *s, unsigned int *counter);
void	ft_putnbr(int n, unsigned int *counter);
int		ft_isnull(const char *ptr, unsigned int *counter);
void	ft_putunbr(unsigned int n, unsigned int *counter);
void	ft_puthex(unsigned int hex, char uppercase, unsigned int *counter);
void	ft_puthexp(unsigned long hex, unsigned int *counter);
int		ft_printf(const char *str, ...);
int		ft_atoi(char *str);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
#endif
