/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:46:26 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/19 15:43:01 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# define HEX_UP "0123456789ABCDEF"
# define HEX_LOW "0123456789abcdef"

int		ft_printf(const char *str, ...);
void	ft_printf_c(char c, size_t *count);
void	ft_printf_s(char *str, size_t *count);
void	ft_printf_p(void *ptr, size_t *count);
void	ft_printf_d(int num, size_t *count);
void	ft_printf_i(int num, size_t *count);
void	ft_printf_u(unsigned int num, size_t *count);
void	ft_printf_xx(unsigned int num, size_t *count, char *base);
char	*ft_aux_pf(unsigned long long n, char *base);

#endif
