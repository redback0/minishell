/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:25:44 by njackson          #+#    #+#             */
/*   Updated: 2024/08/07 16:41:58 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

// hidden function from `ft_env.c`
t_dict	**ft_get_env_list(void);

void	init_env(char **envp)
{
	t_dict	**env;
	t_dict	**new;
	size_t	equals;

	env = ft_get_env_list();
	new = env;
	while (*envp)
	{
		equals = (size_t)ft_strchr(*envp, '=');
		if (equals == 0)
		{
			++envp;
			continue ;
		}
		*new = malloc(sizeof(**new));
		equals -= (size_t)(*envp);
		(*new)->key = ft_substr(*envp, 0, equals);
		(*new)->value = ft_substr(*envp, equals + 1, -1);
		(*new)->next = 0;
		new = &((*new)->next);
		++envp;
	}
}

static char	*ft_dict_to_str(t_dict *dict)
{
	char	*out;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(dict->key) + ft_strlen(dict->value) + 2;
	out = malloc(len * sizeof(char));
	i = 0;
	j = 0;
	while (i < len && dict->key[j])
		out[i++] = dict->key[j++];
	if (i < len)
		out[i++] = '=';
	j = 0;
	while (i < len && dict->value[j])
		out[i++] = dict->value[j++];
	out[i] = 0;
	return (out);
}

char	**ft_full_env(void)
{
	t_dict	**env;
	t_dict	*tmp;
	char	**envp;
	int		ec;
	int		i;

	env = ft_get_env_list();
	tmp = *env;
	ec = 0;
	while (tmp)
	{
		tmp = tmp->next;
		++ec;
	}
	envp = malloc((ec + 1) * sizeof(char *));
	i = 0;
	while (i < ec)
	{
		envp[i] = ft_dict_to_str(*env);
		++i;
		env = &((*env)->next);
	}
	envp[i] = 0;
	return (envp);
}
