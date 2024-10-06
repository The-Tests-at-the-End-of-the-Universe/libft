#include <libft_tester.h>

int	chrcmp(char *org, char *ft, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (org[i] != ft[i])
			return (1);
		i++;
	}
	return (0);
}
