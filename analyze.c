/*************************************************************************
	> File Name: analyze.c
	> Author: luoweichui
	> Mail: luweichui@163.com 
	> Created Time: 2017年03月24日 星期五 19时05分09秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXLEN 1024
#define MAXSIZE 500000

char *tmp[8]= {NULL};
char *arr[MAXSIZE][3] = {NULL};		//0 type, 1 time, 2 clientip
int count = 0;
int truesize = 0;		//total size

void MySplit(char *Strline)
{
	if(Strline == NULL || *Strline == '\n')
	{
		printf("MySplit error");
		return;
	}
	char *p = Strline;
	while (*Strline != '\n')
	{
		Strline++;
	}
	*Strline = '\0';
	Strline = p;

	char *ptr = strtok(Strline," ");
	while (ptr != NULL)
	{
		tmp[count++] = ptr;
		ptr = strtok(NULL," ");
	}
}


void GetTime(char *stime,char **dtime)
{
	while (*stime != '=')
	{
		stime++;
	}
	*dtime = stime + 1;
}


void GetCliIp(char *sourceip,char **desip)
{
	
	while (*sourceip != '=')
	{
		sourceip++;
	}
	*desip = sourceip + 1;
}


void GetTypeTimeCliStr(char **type, char **time, char **clientip)
{

	if (strncmp(tmp[2],"type=v2.bufferStart",strlen("type=v2.bufferStart")) == 0)
	{
		*type = "t";
	}
	else
	{
		*type = "p";
	}
	GetTime(tmp[3],time);

	GetCliIp(tmp[5],clientip);

}


void GetMyString(char *Strline, char **type, char **time,char **clientip)
{
	MySplit(Strline);
	GetTypeTimeCliStr(type,time,clientip);
}


void ClearTmp()
{
	int i;
	for (i = 0; i < count; i++)
	{
		tmp[i] = NULL;
	}
	count = 0;
}


void GetPlace(char **p)
{
	*p = (char *)malloc(sizeof(char) * 30);
	if (*p == NULL)
	{
		printf("GetPlace error");
		return;
	}
	memset(*p,0,sizeof(char)*30);
}


void GetMyArr()
{
	int i = 0;
	char *path = "./momo-20170323.log";
	FILE *fr;
	FILE *fw;
	fr = fopen(path,"r");
	assert(fr != NULL);
//	fw = fopen(filename,"w");
//	assert(fw != NULL);

	char Strline[MAXLEN] = {0};

	char *type = NULL;
	char *time = NULL;
	char *clientip = NULL;

	while (!feof(fr))
	{
		fgets(Strline,MAXLEN,fr);
		if (*Strline == '\n')
		{
			break;
		}
        GetMyString(Strline,&type,&time,&clientip);
		
		GetPlace(&arr[i][0]);
		GetPlace(&arr[i][1]);
		GetPlace(&arr[i][2]);

		strcpy(arr[i][0],type);
		strcpy(arr[i][1],time);
        strcpy(arr[i][2],clientip);
        i++;
		truesize++;
//		fprintf(fw,"%c %s %s\n",type,time,clientip);
//		fflush(fw);
		
		time = NULL;
		clientip = NULL;
		type = NULL;
		memset(Strline,0,MAXLEN);
		ClearTmp();

	}
//	fclose(fw);
	fclose(fr);
}


void MyArrSort()
{
	int j;
	int i;
	char *tmp = NULL;
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	for (i = 0; i < truesize-1; i++)
	{
		for (j = 0; j < truesize-i-1; j++)
		{
			if (strcmp(arr[j][2],arr[j+1][2]) > 0)
			{
	 			tmp = arr[j][2];
				arr[j][2] = arr[j+1][2];
				arr[j+1][2] = tmp;

				tmp1 = arr[j][0];
				arr[j][0] = arr[j+1][0];
				arr[j+1][0] = tmp1;

				tmp2 = arr[j][1];
				arr[j][1] = arr[j+1][1];
				arr[j+1][1] = tmp2;
			}
		}
	}
}


char *arrtmp[MAXSIZE][3] = {NULL};		//0 type, 1 time, 2 clientip
static void Merge(int gap)
{
	int i = 0;
	int low1 = 0;
	int high1 = low1 + gap - 1;
	int low2 = high1 + 1;
	int high2 = low2 + gap - 1 < truesize - 1 ? low2 + gap - 1 : truesize - 1;

	while (low2 < truesize)
	{
		while (low1 <= high1 && low2 <= high2)
		{
			if (strcmp(arr[low1][2],arr[low2][2]) < 0)
			{
				arrtmp[i][2] = arr[low1][2];
				arrtmp[i][0] = arr[low1][0];
				arrtmp[i][1] = arr[low1][1];
				i++;
				low1++;
			}
			else
			{
				arrtmp[i][2] = arr[low2][2];
				arrtmp[i][0] = arr[low2][0];
				arrtmp[i][1] = arr[low2][1];
				i++;
				low2++;
				
			}
		}

		while (low1 <= high1)
		{
			arrtmp[i][2] = arr[low1][2];
			arrtmp[i][0] = arr[low1][0];
			arrtmp[i][1] = arr[low1][1];
			i++;
			low1++;
		}
		while (low2 <= high2)
		{
			arrtmp[i][2] = arr[low2][2];
			arrtmp[i][0] = arr[low2][0];
			arrtmp[i][1] = arr[low2][1];
			i++;
			low2++;
		}

		low1 = high2 + 1;
		high1 = low1 + gap -1;
		low2 = high1 + 1;
		high2 = low2 + gap - 1 < truesize - 1 ? low2 + gap - 1:truesize - 1;
	}

	while (low1 < truesize)
	{
		arrtmp[i][2] = arr[low1][2];
		arrtmp[i][0] = arr[low1][0];
		arrtmp[i][1] = arr[low1][1];
		i++;
		low1++;
	}

	for (i = 0; i < truesize; i++)
	{
		arr[i][0] = arrtmp[i][0];
		arr[i][1] = arrtmp[i][1];
		arr[i][2] = arrtmp[i][2];
	}
}

void MyMergeArrSort()
{
	int i;
	for (i = 1; i < truesize; i *= 2)
	{
		Merge(i);
	}
}


int GetCountDifIp()
{
	int i;
	int total = 0;
	for (i = 0; i < truesize-1;)
	{
		if (strcmp(arr[i][2],arr[i+1][2]) == 0)
		{
			i++;
		}
		else
		{
			total++;
			i++;
		}
	}
	return total;
}



int MyStrSub(char *a,char *b)
{
	if (a == NULL || b == NULL)
	{
		printf("MyStrSub error\n");
		exit(1);
	}

	int a_len;
	int b_len;
	int i;
	int cmd;
	int len;
    int j = 0;

	a_len = strlen(a);
	b_len = strlen(b);

	int *a_num = (int *)malloc(sizeof(int) * a_len);
	int *b_num = (int *)malloc(sizeof(int) * b_len);
	int des[100] = {0};
	char result[100];
	for (i = 0; i < a_len; i++)
	{
		a_num[a_len-i-1] = a[i]-'0';
	}
	for (i = 0; i < b_len; i++)
	{
		b_num[b_len-i-1] = b[i]-'0';
	}
	
	if (a_len > b_len)
	{
		cmd = 1;
	}
	else if (a_len < b_len)
	{
		cmd = -1;
	}
	else
	{
		cmd = strcmp(a,b);
	}
	
	len= a_len > b_len?a_len:b_len;

	if (cmd > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (a_num[i] < b_num[i])
			{
				a_num[i] += 10; 
				a_num[i+1] -= 1;
				des[j++] = a_num[i] - b_num[i];
			}
			else
			{
				des[j++] = a_num[i] - b_num[i];
			}
		}
	}
	else if (cmd < 0)
	{
		for(i = 0; i < len; i++)
		{
			if(b_num[i] < a_num[i])
			{
				b_num[i] += 10;
				b_num[i+1] -= 1;
				des[j++] = b_num[i] - a_num[i];
			}
			else
			{
				des[j++] = b_num[i] - a_num[i];
			}
		}
	}
	else
	{
		for (i = 0; i < len; i++)
		{
			des[j++] = b_num[i] - a_num[i];
		}
	}
	
	j = 0;
	i = len - 1;
	while(des[i] == 0)i--; //until des[i] not 0
	
	for(i; i >= 0; i--)
	{
		result[j++] = des[i] + '0';
	}
	result[j] = '\0';

	free(a_num);
	free(b_num);
	return atoi(result);
}


void GetMyTime(double *timearr,int *j,int *max) //Get every ip stop of second
{
	if (timearr == NULL)
	{
		printf("GetMyTime error\n");
		return;
	}

	int i;
	int thisinternum = 0;
	int intertotal = 0;
	int w = 0;
	
	for (i = 0; i < truesize - 1;)
	{
		if (strcmp(arr[i][2],arr[i+1][2]) != 0)
		{
			if (thisinternum != 0)
			{	
				if(*max < thisinternum) 
				{
					*max = thisinternum;
				}
				timearr[(*j)++] = (double)intertotal/(thisinternum * 1000); // ++ 优先级高
			}
			
			intertotal = 0;
			thisinternum = 0;
			i++;
		}
		else
		{
			if (strcmp(arr[i][0],arr[i+1][0]) == 0)
			{
				i++;
			}
			else
			{
			 	w = MyStrSub(arr[i][1],arr[i+ 1][1]);
				intertotal += w;
				i+=2;
				thisinternum++;
			}
		}
	}
}


void GetOneTime(double *onetimearr,int *z,int one_to_end)
{
	if (onetimearr == NULL)
	{
		printf("GetMyTime error\n");
		return;
	}

	int i;
	int thisinternum = 0;
	int intertotal = 0;
	int w = 0;
	
	for (i = 0; i < truesize - 1;)
	{
		if (strcmp(arr[i][2],arr[i+1][2]) != 0)
		{
			if (thisinternum == one_to_end)
			{
				onetimearr[(*z)++] = (double)intertotal/(thisinternum * 1000);
			}
			intertotal = 0;
			thisinternum = 0;
			i++;
		}
		else
		{
			if (strcmp(arr[i][0],arr[i+1][0]) == 0)
			{
				i++;
			}
			else
			{
			 	w = MyStrSub(arr[i][1],arr[i+1][1]);
				intertotal += w;
				i+=2;
 				thisinternum++; 
			}
		}
	}
}


int main()
{
	int count_dif_ip = 0;
	double intetimearr[MAXSIZE] = {0};
	double oneinter[MAXSIZE] = {0};			
	int i = 0;
	int k = 0;
	
	int totalipj = 0;
	int internumz = 0;
	int total = 0;
	int one_to_end = 0;
	int tmp = 0;
	int max = 0;
	GetMyArr();
    MyMergeArrSort();
	
//	for(i = 0; i < truesize; i++)
//	{
//		printf("%s %s %s\n",arr[i][0],arr[i][1],arr[i][2]);
//	}

	count_dif_ip = GetCountDifIp(); 
//	printf("%d\n",count_dif_ip);	

	GetMyTime(intetimearr,&totalipj,&max);
	for (one_to_end = 1; one_to_end <= 50; one_to_end++)
	{
		printf("卡顿%d次\n",one_to_end);
		GetOneTime(oneinter,&internumz,one_to_end);
		for (k = 0; k < 15; k++)
		{
			for (i = 0; i < internumz; i++)
			{
				if (oneinter[i] <= k+ 1 && oneinter[i] >= k)
				{
					total++;
				}
			}
			printf("%ds<时间<%ds  %f%\n",k,k+1,(double)total*100/totalipj);
			total = 0;
		}
		total = 0;
		for (i = 0; i < internumz; i++)
		{
			if(oneinter[i] > 15)
			{
				total++;
			}
		}
		printf("时间>15s %f%\n",(double)total*100/totalipj);
		internumz = 0;
	}


//	for (k = 0; k < 15; k++)
//	{
//		for(i = 0; i < j; i++)
//		{
//			if (intetimearr[i] <= k+1 && intetimearr[i] >= k)
//			{
//				total++;	
//			}
//		}
//		printf("%ds<时间<%ds %f%\n",k,k+1,(double)total*100/j);
//		total = 0;
//	}
//
//	total = 0;
//	for (i = 0; i < j; i++)
//	{
//		if (intetimearr[i] > 15)
//		{
//			total++;
//		}
//	}
//	printf("时间>15s %f%\n",(double)total*100/j);
//
//	printf("----------------------------------------");
//	
//	total = 0;
//	for (k = 0; k < 15; k++)
//	{
//		for(i = 0; i < z; i++)
//		{
//			if (oneinter[i] <= k+1 && oneinter[i] >= k)
//			{
//				total++;	
//			}
//		}
//		printf("%ds<时间<%ds %f%\n",k,k+1,(double)total*100/j);
//		total = 0;
//	}
//
//	total = 0;
//	for (i = 0; i < z; i++)
//	{
//		if (oneinter[i] > 15)
//		{
//			total++;
//		}
//	}
//	printf("时间>15s %f%\n",(double)total*100/j);
	
//	printf("总的ip=%d\n",j);

	for (i = 0;i < truesize; i++)
	{
		free(arr[i][0]);
		free(arr[i][1]);
		free(arr[i][2]);
	}

	return 0;
}
