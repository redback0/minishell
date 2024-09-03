/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:53:45 by njackson          #+#    #+#             */
/*   Updated: 2024/09/03 16:15:46 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var(char *argv, int *j, int status, char **var)
{
	*j = 0;
	if (*argv == '?')
	{
		*var = ft_itoa(status);
		++(*j);
		return (1);
	}
	else if (!ft_isdigit(*argv))
		while (ft_isalnum(argv[*j]) || argv[*j] == '_')
			++(*j);
	*var = ft_get_env(argv);
	return (0);
}

static char	*add_var(char *argv, int *i, int status)
{
	char	*old_arg;
	char	*var;
	int		j;
	int		alloced;

	alloced = get_var(argv + *i, &j, status, &var);
	argv[*i - 1] = 0;
	old_arg = argv;
	argv = ft_strnjoin(3, old_arg, var, old_arg + *i + j);
	free(old_arg);
	*i += ft_strlen(var) - 1;
	if (alloced)
		free(var);
	return (argv);
}

void	variable_expand(char **argv, int status)
{
	int		i;
	int		in_double_quotes;

	in_double_quotes = 0;
	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] == '"')
				in_double_quotes = !in_double_quotes;
			if (!in_double_quotes && (*argv)[i] == '\'')
				finish_quote(*argv, &i);
			else if ((*argv)[i++] == '$')
			{
				*argv = add_var(*argv, &i, status);
			}
		}
		++argv;
	}
}

static char	*rebuild_arg(char *argv, int *i)
{
	char	*new_parts[3];
	int		j;

	j = 0;
	finish_quote(argv + *i, &j);
	if (j > 1 && argv[*i + j - 1] == argv[*i])
	{
		new_parts[0] = argv;
		new_parts[1] = argv + *i + 1;
		new_parts[2] = argv + *i + j;
		argv[*i] = 0;
		argv[*i + j - 1] = 0;
		argv = ft_strnjoin(3, new_parts[0], new_parts[1], new_parts[2]);
		free(new_parts[0]);
		*i += j - 3;
	}
	return (argv);
}

void	remove_quotes(char **argv)
{
	int		i;

	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] == '\'' || (*argv)[i] == '"')
				*argv = rebuild_arg(*argv, &i);
			++i;
		}
		++argv;
	}
}
