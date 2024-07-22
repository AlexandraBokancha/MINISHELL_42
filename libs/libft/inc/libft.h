/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:51:19 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:17:33 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*##############
#      LIBS     #
 ##############*/

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdio.h>

/*##########################################################################
#                                                                           #
#                                   LIBFT                                   #
#                                                                           #
 ##########################################################################*/

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;

/*##############
#      LST      #
 ##############*/

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
	void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

/*##############
#      MEM      #
 ##############*/

void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *memoryblock, \
	int searchChar, size_t size);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t size);
void			*ft_memset(void *s, int c, size_t n);

/*##############
#      PUT      #
 ##############*/

void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_putlchar(char c);
int				ft_putlstr(char *str, int size);
int				ft_putlchar_fd(char c, int fd);
int				ft_putlstr_fd(char *str, int size, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putstr_fd(char *s, int fd);
void			ft_puttab(char **tab);

/*##############
#       IS      #
 ##############*/

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_ispath(char *str);

/*##############
#       TO      #
 ##############*/

int				ft_ctolower(int c);
int				ft_ctoupper(int c);
char			*ft_strtolower(char *str);
char			*ft_strtoupper(char *str);

/*##############
#     ALLOC     #
 ##############*/

void			*ft_calloc(size_t elementcount, size_t elementsize);
void			*ft_setalloc(size_t elementsize, size_t elementcount, int c);

/*##############
#    CONVERT    #
 ##############*/

int				ft_atoi(const char *nptr);
int				ft_atoi_base(const char *str, const char *base, int *i);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
char			*ft_argjoin(char **tab, char c);
long			ft_atolle(char *nptr, int *i);

/*##############
#      STR      #
 ##############*/

char			*ft_strchr(const char *s, int c);
void			*ft_strdcpy(char *src, char *dest, int dif);
char			*ft_strdup(const char *s);
int				ft_striteris(const char *str, int (is)(int));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *first, \
	const char *second, size_t length);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strremovec(char *str, char c);
char			*ft_firstword(char *str, char c);

/*##############
#     READ      #
 ##############*/

char			*gwf(int fd);
char			*gnl(int fd, int *error);

/*##############
#     COUNT     #
 ##############*/

int				ft_countword(char const *s, char c);

/*##############
#     FREE      #
 ##############*/

void			ft_freectab(char **tab);
void			ft_freeiarray(int **tab, int size);

/*##########################################################################
#                                                                           #
#                                  PRINTF                                   #
#                                                                           #
 ##########################################################################*/

/*##############
#  STRUCTURES  #
 ##############*/

typedef struct s_printfstruct
{
	int	hash;
	int	plus;
	int	space;
	int	minus;
	int	zero;
	int	v_width;
	int	precision;
	int	v_precision;
	int	specifier;
	int	flag_size;
}	t_printfstruct;

/*##############
#     MAIN     #
 ##############*/

void			ft_initstruct(t_printfstruct *new_struct);
int				ft_percentsign(t_printfstruct structure, va_list args);
void			ft_check_printf(const char *str, t_printfstruct *structure);
int				ft_isflag(const char c);
int				ft_isspec(const char c);
int				ft_printf(const char *str, ...);
int				ft_flen(size_t nbr);
int				ft_strread(const char *str, va_list args);

/*##############
#  SPECIFIERS  #
 ##############*/

int				ft_i(t_printfstruct structure, int nb);
char			*ft_ibis(t_printfstruct structure, int nb, char *str);
int				ft_zeri(t_printfstruct structure);
char			*ft_mini(t_printfstruct structure, char *src, int nb);
int				ft_c(t_printfstruct structure, int c);
int				ft_p(t_printfstruct structure, size_t nb);
char			*ft_pbis(t_printfstruct structure, char *str, char *prefix);
int				ft_s(t_printfstruct structure, char *s);
int				ft_u(t_printfstruct structure, unsigned int nb);
char			*ft_widthu(t_printfstruct structure, char *src);
int				ft_x(t_printfstruct structure, unsigned int nb);
char			*ft_xbis(t_printfstruct structure, char *str);
char			*ft_strxbis(t_printfstruct structure, \
	char *prefix, char *src, char *dest);

/*##########################################################################
#                                                                           #
#                                 PRINTF_FD                                 #
#                                                                           #
 ##########################################################################*/

/*##############
#     MAIN     #
 ##############*/

int				ft_percentsign_fd(t_printfstruct structure, \
	va_list args, int fd);
int				fd_printf(int fd, const char *str, ...);
int				ft_strread_fd(const char *str, va_list args, int fd);

/*##############
#  SPECIFIERS  #
 ##############*/

int				ft_i_fd(t_printfstruct structure, int nb, int fd);
int				ft_zeri_fd(t_printfstruct structure, int fd);
int				ft_c_fd(t_printfstruct structure, int c, int fd);
int				ft_p_fd(t_printfstruct structure, size_t nb, int fd);
int				ft_s_fd(t_printfstruct structure, char *s, int fd);
int				ft_u_fd(t_printfstruct structure, unsigned int nb, int fd);
int				ft_x_fd(t_printfstruct structure, unsigned int nb, int fd);

/*##########################################################################
#                                                                           #
#                              GET_NEXT_LINE                                #
#                                                                           #
 ##########################################################################*/

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 1
# endif

# ifndef GNL_ERROR
#  define GNL_ERROR -1
# endif

# ifndef GWF_BUFFER_SIZE
#  define GWF_BUFFER_SIZE 1000000
# endif

typedef struct s_gnl_struct
{
	int		size;
	int		nlpos;
	char	*str;
	int		read;
	char	*str_return;
	char	*str_static;
}	t_gnl_struct;

void			gnl_static(t_gnl_struct *stc, int fd, int *error);
void			gnl_read(t_gnl_struct *stc, int fd, int *error);
void			gnl_return(t_gnl_struct *stc, int *error);
void			gnl_error(t_gnl_struct *stc, int *error, char *emessage);

#endif