#include "philosopher.h"

static int	getbuf(int n)
{
	int	buf;

	buf = 1;
	if (n <= 0)
	{	
		buf ++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		buf ++;
	}
	return (buf);
}

char	*ft_itoa(int n)
{
	int		buf;
	long	temp;
	char	*ret;

	if (n >= 0)
		temp = n;
	else
		temp = -(long)n;
	ret = (char *)malloc(sizeof(char) * (buf = getbuf(n)));
	if (ret)
	{
		ret[(buf--) - 1] = 0;
		while (temp)
		{
			ret[(buf--) - 1] = temp % 10 + '0';
			temp /= 10;
		}
		if (n < 0)
			ret[buf - 1] = '-';
		else if (n == 0)
			ret[buf - 1] = '0';
	}
	return (ret);
}
