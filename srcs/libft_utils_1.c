#include "pipex.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, (int)*(s1 + start)) && *(s1 + start))
		start++;
	if (!*(s1 + start))
		return (ft_strdup(""));
	while (ft_strchr(set, (int)*(s1 + len - 1 - end)) && *(s1 + len - 1 - end))
		end++;
	return (ft_substr(s1, start, len - start - end));
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	char	*aux_str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	aux_str = str;
	while (*s1)
		*aux_str++ = *s1++;
	while (*s2)
		*aux_str++ = *s2++;
	*aux_str = '\0';
	return (str);
}

static int	ft_wordcount(char *str, char delimiter)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	if (*str != delimiter && *(str))
		i = 1;
	while (*(str + 1))
	{
		if (*str == delimiter && *(str + 1) != delimiter && *(str + 1) != '\0')
			i++;
		str++;
	}
	return (i);
}

static void	ft_subsplit(const char *s, char c, int n_words, char **out)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	while (n_words-- > 0)
	{
		while (*(s + i) == c && *(s + i))
			i++;
		j = i;
		while (*(s + i) != c && *(s + i))
			i++;
		*out = (char *)malloc(sizeof(char) * (i - j + 1));
		k = 0;
		l = j;
		while (k + l < i)
		{
			*(*(out) + k++) = *(s + j++);
			*(*out + k) = '\0';
		}
		out++;
	}
	*out = NULL;
}

char	**ft_split(const char *s, char c)
{
	size_t		n_words;
	char		**out;

	if (!s)
		return (NULL);
	n_words = ft_wordcount((char *)s, c);
	out = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!out)
		return (NULL);
	ft_subsplit(s, c, n_words, out);
	return (out);
}
