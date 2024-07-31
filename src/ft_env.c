/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:22:42 by njackson          #+#    #+#             */
/*   Updated: 2024/07/31 15:28:27 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_dict	**ft_get_env_list(void)
{
	static t_dict	*env;

	return (&env);
}

char	*ft_get_env(char *key)
{
	t_dict	*env;

	env = *ft_get_env_list();
	while (env)
	{
		if (ft_strncmp(env->key, key, -1) == 0)
			return (env->value);
		env = env->next;
	}
	return (0);
}

void	ft_set_env(char *k, char *v)
{
	t_dict	**env;

	env = ft_get_env_list();
	while (*env)
	{
		if (ft_strncmp((*env)->key, k, -1) == 0)
		{
			(*env)->value = v;
			return ;
		}
		env = &((*env)->next);
	}
	*env = malloc(sizeof(**env));
	(*env)->key = k;
	(*env)->value = v;
	(*env)->next = 0;
}

void	ft_unset_env(char *k)
{
	t_dict	**env;
	t_dict	*tmp;

	env = ft_get_env_list();
	while (*env)
	{
		if (ft_strncmp((*env)->key, k, -1) == 0)
		{
			tmp = *env;
			*env = (*env)->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		env = &((*env)->next);
	}
}

void	ft_clear_env(void)
{
	t_dict	**env;
	t_dict	*tmp;
	t_dict	*next;

	env = ft_get_env_list();
	next = *env;
	while (next)
	{
		tmp = next;
		next = next->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*env = NULL;
}
