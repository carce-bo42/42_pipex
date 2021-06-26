# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n-- > 0 && (*s1 || *s2))
		if (*s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*output_str;
	int		i;

	output_str = (char *) malloc(sizeof (*src) * (ft_strlen(src) + 1));
	if (!output_str)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		output_str[i] = src[i];
		i++;
	}
	output_str[i] = '\0';
	return (output_str);
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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*aux_str;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) - 1)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start ;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	aux_str = str;
	while (len-- > 0 && *(s + start))
		*aux_str++ = *(s++ + start);
	*aux_str = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	char	*aux;

	aux = (char *)s;
	len = ft_strlen(s) + 1;
	while (len-- > 0)
	{
		if (*aux++ == (char)c)
			return (--aux);
	}
	return (NULL);
}

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

int		find_i_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

int main(int argc, char **argv, char **env)
{
	char	**exec_paths;
	char	*aux;
	char	*aux2;
	int		i_path;
	int		i = 0;

	i_path = find_i_path(env);
	aux = ft_strtrim(env[i_path], "PATH=");
	exec_paths = ft_split(aux, ':');
	i = 0;
	while (exec_paths[i])
	{
		aux2 = exec_paths[i];
		exec_paths[i] = ft_strjoin(exec_paths[i], "/");
		free(aux2);
		i++;
	}
	i = 0;
	while (exec_paths[i])
	{
		printf("%s\n", exec_paths[i]);
		i++;
	}
	system("leaks a.out");
	return (0);
}

