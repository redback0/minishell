/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:47:11 by njackson          #+#    #+#             */
/*   Updated: 2024/08/10 17:23:54 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "libft.h"
# include <stdlib.h>

typedef struct s_dict
{
	struct s_dict	*next;
	char			*key;
	char			*value;
}	t_dict;

void	init_env(char **envp);
char	*ft_get_env(char *key);
void	ft_set_env(char *k, char *v);
void	ft_clear_env(void);
void	ft_unset_env(char *k);
char	**ft_full_env(void);

#endif
