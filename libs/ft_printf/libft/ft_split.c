/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:49:59 by sbelomet          #+#    #+#             */
/*   Updated: 2023/11/29 13:28:57 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstrs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	ft_buildtab(char **tab, char const *s, char c)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	i = 0;
	end = 0;
	while (s[end])
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		if ((s[end] == c || s[end] == '\0') && start != end)
		{
			tab[i] = ft_substr(s, start, (end - start));
			i++;
			start = end;
		}
	}
	tab[i] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = ft_countstrs(s, c);
	res = (char **)malloc((str_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	ft_buildtab(res, s, c);
	return (res);
}

/*
int main(void) {
    char str[] = "lorem ipsum dolor sit    ";
    char delim = ' ';
    char** result = ft_split(str, delim);
    int i;

	i = 0;
	while (result[i] != NULL)
	{
        printf("|%s|\n", result[i]);
		i++;
    }
    return 0;
}*/
