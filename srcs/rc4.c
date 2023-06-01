#include "woody.h"

bool		init = false;
uint8_t		S[256];
uint8_t		T[256];

static void		swap(uint8_t *a, uint8_t *b)
{
	uint8_t		res;

	res = *a;
	*a = *b;
	*b = res;
}

static int		check_array(uint8_t *array)
{
	int		found;

	for (int j = 0; j < 256; j++)
	{
		found = 0;
		for (int i = 0; i < 256; i++)
		{
			if (array[i] == j)
			{
				found = 1;
				break ;
			}
		}
		if (found == 0)
		{
			printf("%d not found\n", j);
			return (-1);
		}
	}
	return (0);
}

static void		print_array(uint8_t *array)
{
	for (int i = 0; i < 256; i++)
		printf("%s%3d ", i % 8 == 0 ? "\n" : "", array[i]);
	printf("\n");
}

static void		init_array(uint8_t *key, int key_len)
{
	int j = 0;

	for (int i = 0; i < 256; i++)
	{
		S[i] = i;
		T[i] = key[i % key_len];
	}
	for (int i = 0; i < 256; i++)
	{
		
//		printf("j = %d ", j);
		j = (j + S[i] + T[i]) % 256;
//		printf("+ %d + %d : [%d]\n", S[i], T[i], j);
		swap(&S[i], &S[j]);
	}
}

uint8_t			*rc4(const char *plain, int plain_len, uint8_t *key, int key_len)
{
	int			k;
	uint8_t		*cypher;
	int			i;
	int			j;
	int			t;

	i = 0;
	j = 0;
	if (!init)
	{
		init = true;
		init_array(key, key_len);
	}
	cypher = (uint8_t *)malloc(sizeof(uint8_t) * plain_len);
	printf("\n ------------ \n");
	for (int idx = 0; idx < plain_len; idx++)
	{
		i = (i + 1) % 256;
	//	printf("i = %d\n", i);
		j = (j + S[i]) % 256;
	//	printf("j = %d\n", j);
		//if (idx < 10)
		//	printf("A[%d] %d %d\n", idx, i, j);
		swap(&S[i], &S[j]);
		//if (idx < 10)
		//	printf("B[%d] %x %x\n", idx, S[i], S[j]);
		//print_array(S);
		t = (S[i] + S[j]) % 256;
		k = S[t];
	//	printf("k = %d\n", k);
		cypher[idx] = k ^ plain[idx];
		printf("%d ", cypher[idx]);
	}
	printf("\n");
	/*for (int idx = 0; idx < plain_len; idx++)
		printf("%x ", cypher[idx]);
	printf("\n");*/
	//for (int x = 0; x < 256; x++)
	//	printf("%d\n", S[x]);
	return (cypher);
}
