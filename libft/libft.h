/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:33:09 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/22 21:36:36 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <sys/types.h>

int		ft_abs(int n);

int		ft_atoi(const char *nbr);

void	ft_bzero(void *m, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

int		ft_isdigit(int c);

int		ft_isspace(int c);

void	*ft_memset(void *s, int c, size_t n);

char	*ft_ptoa_base(void *ptr, char *baseset);

ssize_t	ft_putchar_fd(char c, int fd);

ssize_t	ft_putchar(char c);

ssize_t	ft_putnchars_fd(char c, size_t n, int fd);

ssize_t	ft_putnchars(char c, size_t n);

ssize_t	ft_putnstr_fd(char *str, size_t n, int fd);

ssize_t	ft_putnstr(char *str, size_t n);

ssize_t	ft_putstr_fd(char *str, int fd);

ssize_t	ft_putstr(char *str);

size_t	ft_strlen(char *str);

size_t	ft_strnlen(char *str, size_t n);

char	*ft_utoa_base(unsigned int u, char *baseset);

#endif
