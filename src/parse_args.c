/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:53:45 by njackson          #+#    #+#             */
/*   Updated: 2024/08/09 00:11:22 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static char	*add_var(char *argv, int *i)
{
	char	*old_arg;
	char	*var;
	int		j;

	old_arg = argv;
	j = 0;
	if (!ft_isdigit(old_arg[*i]))
		while (ft_isalnum((old_arg)[*i + j]) || (old_arg)[*i + j] == '_')
			++j;
	if (argv[*i] == '?')
	{
		var = ft_get_env("?");
		++j;
	}
	else
		var = ft_get_env(old_arg + *i);
	argv[*i - 1] = 0;
	argv = ft_strnjoin(3, old_arg, var, old_arg + *i + j);
	free(old_arg);
	*i += ft_strlen(var) - 1;
	return (argv);
}

void	variable_expand(char **argv)
{
	int		i;

	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] == '\'')
				finish_quote(*argv, &i);
			else if ((*argv)[i++] == '$')
				*argv = add_var(*argv, &i);
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

void	finish_quote(const char *line, int *i)
{
	int	s;

	if (line[*i] != '\'' && line[*i] != '"')
	{
		++(*i);
		return ;
	}
	s = *i;
	++(*i);
	while (line[*i] && line[*i] != line[s])
		++(*i);
	if (line[*i] != '\0')
		++*i;
	else
		*i = s + 1;
}
