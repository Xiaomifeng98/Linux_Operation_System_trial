int qiujie(void)
{
	int i,j,pro,sum;
	for(i = 1;i <= 6;i++)
	{
		pro = 1;
		sum = 0;
		for(j = 1;j <= i;j++ )
		{
			pro *= j;
		}
		sum += pro;
	}
	return sum;
}
