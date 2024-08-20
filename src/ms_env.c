/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <bmilford@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:30:05 by bmilford          #+#    #+#             */
/*   Updated: 2024/08/20 17:58:31 by bmilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ms_env(char **argv)
{
	int		index;
	int		count;
	char	**env;

	index = 0;
	count = 0;
	env = get_full_env();
	while (env[index] != '\0')
		index++;
	while (count <= index)
	{
		printf(env[count];
		count++;
	}
	return (0);
}
