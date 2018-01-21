#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<process.h>
#include<string.h>
#include<math.h>
#define IN 999999
#define N 45
#define ITERATIONS 1000.0

int dijkstra(int cost[][N], int source, int target,int cost_time[][N],int cost_dist[][N]);
int counter=0,count_in_list=0,c[50]={0},f1=0,f2=0,f3=0,f4=0,f5=0,f6=0,f7=0;
float sum_time[50]={0},sum_dist[50]={0};


int main()
{
	int i,j,k=0,p,q,path_length[68],speed_br[68],intersection[68],inters[68][6],traffic_signal[68],traffic[68][4],traffic_sum[68],cost[N][N],cost_time[N][N],
	w,ch,co,source=0, target=0,time_path,x,tod=0,dow=0,total_time[68],inters_sum_time[68],consolidated_time[68],traffic_vary,traffic_array[204]={0},traffic_c=0,
	random_count=0,traffic_index,other_arr[68][4],intersection_c=0,intersection_vary,random_intersection_count=0,intersection_index,
	other_intersection_arr[68][4],intersection_array[204]={0},cost_dist[N][N],count=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0,c7=0,i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0;
	char nk;
	float total_fuel[68],y[68][6],consolidated_fuel[68],time_factor,inters_sum_fuel[68],mileage=0.0,mil,traffic_vary_percent=0.0,intersection_vary_percent=0.0;
	clock_t t;
	t=clock();
	
	struct parameters
	{
		int source[5];
		int target[5];
		float mileage[5];
		int dow[5];
		int tod[5];
		float traffic_vary_percent[5];
		float intersection_vary_percent[5];
	};
	struct parameters k1;
	
	FILE *fp;	
	fp=fopen("input.csv","r");
	if(fp==NULL)
	{
	puts ( "Cannot open file" ) ;
	}
	
	while(fscanf(fp,"%c",&nk)!=EOF)
	{
		printf("%c",nk);
		if(nk==',')
		count++;
		if(f1>0)
		{
			if((f1>=2)||(c1>0))
			{
				k1.source[c1]=nk;
				f1=0;
				c1++;
			}
		}
		if(f2==1)
		{
			k1.target[c2]=nk;
			f2=-1;
			c2++;
		}
		if(f3==1)
		{
			k1.mileage[c3]=nk;
			f3=-1;
			c3++;
		}
		if(f4==1)
		{
			k1.dow[c4]=nk;
			f4=-1;
			c4++;
		}
		if(f5==1)
		{
			k1.tod[c5]=nk;
			f5=-1;
			c5++;
		}
		if(f6==1)
		{
			k1.traffic_vary_percent[c6]=nk;
			f6=-1;
			c6++;
		}
		if(f7==1)
		{
			k1.intersection_vary_percent[c7]=nk;
			f7=-1;
			c7++;
		}
		if(count==8)
		f1++;
		if(count==9)
		f2=1;
		if(count==10)
		f3=1;
		if(count==11)
		f4=1;
		if(count==12)
		f5=1;
		if(count==13)
		f6=1;
		if(count==14)
		f7=1;
	}
	
	c1--;	
	c2--;
	c3--;
	c4--;
	c5--;
	c6--;
	c7--;
	
	while(c1!=0)
	{
		c1--;
		source+=((k1.source[i1]-48)*pow(10,c1));
		i1++;
	}
	
	while(c2!=0)
	{
		c2--;
		target+=((k1.target[i2]-48)*pow(10,c2));
		i2++;
	}
	
	while(c3!=0)
	{
		c3--;
		mileage+=((k1.mileage[i3]-48)*pow(10,c3));
		i3++;
	}
	
	while(c4!=0)
	{
		c4--;
		dow+=((k1.dow[i4]-48)*pow(10,c4));
		i4++;
	}
	
	while(c5!=0)
	{
		c5--;
		tod+=((k1.tod[i5]-48)*pow(10,c5));
		i5++;
	}
	
	while(c6!=0)
	{
		c6--;
		traffic_vary_percent+=((k1.traffic_vary_percent[i6]-48)*pow(10,c6));
		i6++;
	}
	
	while(c7!=0)
	{
		c7--;
		intersection_vary_percent+=((k1.intersection_vary_percent[i7]-48)*pow(10,c7));
		i7++;
	}
		
	printf("Path length\tSpeed breakers\tIntersections\tTraffic Signals\n (in km)\n");
	
	srand(time(NULL));
	
	for (i=0; i<68;i++)
	{
	//FIXED PARAMETERS	
	//intersections >= traffic signals
	
	path_length[i]=1+rand()%4;
	speed_br[i]=rand()%7;
	traffic_signal[i]=rand()%4;
	intersection[i]=traffic_signal[i]+rand()%3;
	printf("\n%d\t\t\t%d\t\t%d\t\t%d\n",path_length[i],speed_br[i],intersection[i],traffic_signal[i]);
	}
 	
	mil=1/mileage;
 
	printf("\n\nSource : %d",source);
    printf("\nDestination : %d",target); 
	printf("\nMileage in kmpl : %0.1f",mileage);
    printf("\nDay of the week(Mon=1 Tue=2 & so on) : %d",dow);
    printf("\nTime of day(in 24-hr format) : %d",tod);
    printf("\nPercentage of traffic signals that vary pattern according to time of day : %.1f",traffic_vary_percent);
    printf("\nPercentage of time-varying intersections : %.1f",intersection_vary_percent);
    
        	
	FILE *fw;	
	fw=fopen("output.csv","w");
	if(fw==NULL)
	{
	puts ( "Cannot open file" ) ;
	}
	
	fprintf(fw,"Origin,Destination,Vehicle Mileage,Day of Week,Vehicle Departure time,Percentage of signals whose timings vary according to the time of the day,"); 
	fprintf(fw,"Percentage of intersections where delay vary according to the time of the day,Greenest path,Probability that the path is greenest,");
	fprintf(fw,"Average distance of the greenest path(km),Average travel time of the greenest path(sec.),Coefficient of variation of the average time,");
	fprintf(fw,"Normalized probability score,Normalized average travel time score,Normalized coefficient of variation path score,");
	fprintf(fw,"Combined score for the path\n");
	fprintf(fw,"%d,%d,%f,%d,%d,%f,%f,",source,target,mileage,dow,tod,traffic_vary_percent,intersection_vary_percent);
	
	fclose(fw);
	
	for(i=0;i<68;i++)
    {
    	for(j=0;j<traffic_signal[i];j++)
    	{
    		traffic_c++;
    	}
    }
       
    for(i=0;i<68;i++)
    {
    	for(j=0;j<intersection[i];j++)
    	{
    		intersection_c++;
    	}
    }
    //printf("\n%d\n",intersection_c);
    
    traffic_vary=(traffic_vary_percent*traffic_c)/100;
    intersection_vary=(intersection_vary_percent*intersection_c)/100;
    //printf("\n%d\n",intersection_vary);
    
    while(random_count!=traffic_vary)
    {
    	traffic_index=rand()%traffic_c;
    	traffic_array[traffic_index]=1;
    	random_count++;
    }
    
    for(i=0;i<68;i++)
    {
    	for(j=0;j<traffic_signal[i];j++)
    	{
    		other_arr[i][j]=traffic_array[k];
			k++;
    	}
    }
    
    while(random_intersection_count!=intersection_vary)
    {
    	intersection_index=rand()%intersection_c;
    	intersection_array[intersection_index]=1;
    	random_intersection_count++;
    }
    
    for(i=0;i<68;i++)
    {
    	for(j=0;j<intersection[i];j++)
    	{
    		other_intersection_arr[i][j]=intersection_array[k];
			k++;
    	}
    }
	
	//TIME-DEPENDENT
	
	for(k=0;k<ITERATIONS;k++)
	{
	
	for(i=0;i<68;i++)
	{	
		//printf("\n");
		for(j=0;j<intersection[i];j++)
		{
			if((other_intersection_arr[i][j]==0)||((other_intersection_arr[i][j]==1)&&(((dow<6)&&(tod>930)&&(tod<1630))||((dow<6)&&(tod>1900))||
			((dow>5)&&(tod<1100))||((dow>5)&&(tod>1830)))))	   														     //regular traffic hours
			inters[i][j]=rand()%21;
			else
			inters[i][j]=rand()%41;
			
			//printf("%d  ",inters[i][j]);
			
			if(inters[i][j]<=10)
			{
				x=6*(10-inters[i][j]);
				y[i][j]=0.005556*(577.2-((0.0006*x*x*x)-(0.114*x*x)+(14.3*x)))*inters[i][j];
				
			}
			else
			{
				y[i][j]=32.067+((inters[i][j]-10)*0.2167);
			}
			//printf("%f ",y[i][j]);
		}
		//printf("\t");
		for(q=0;q<traffic_signal[i];q++)
		{
			if((other_arr[i][j]==0)||((other_arr[i][j]==1)&&(((dow<6)&&(tod>930)&&(tod<1630))||((dow<6)&&(tod>1900))||((dow>5)&&(tod<1100))||
			((dow>5)&&(tod>1830)))))
			traffic[i][q]=rand()%121;
			else
			traffic[i][q]=rand()%241;
			//printf("%d  ",traffic[i][q]);
		}
	
	}
	
	//printf("\n");
	
	for(i=0;i<68;i++)
	{
		//Avg. speed = 60kph
		//Time for each speed breaker = 10 sec.
		//Total time computed in  seconds
		
		inters_sum_fuel[i]=0.0;
		inters_sum_time[i]=0;
		traffic_sum[i]=0;
		
		for(j=0;j<intersection[i];j++)
		{
			inters_sum_fuel[i]+=y[i][j];
			inters_sum_time[i]+=inters[i][j];
		}
		
		for(q=0;q<traffic_signal[i];q++)
		{
			traffic_sum[i]+=traffic[i][q];
		}
		
		//path_length * (1000/mileage kmpl) ml.
		//mil = 1/mileage
		//speed_br * (6.64 l/hr) * (1/60 min) * (1000/6)	[assuming each speed breaker causes a loss of 10 sec.)
						
		total_time[i]=(60*path_length[i])+(10*speed_br[i])+(inters_sum_time[i])+(traffic_sum[i]);
		total_fuel[i]=((1000*mil*path_length[i]))+(18.444*speed_br[i])+(inters_sum_fuel[i])+(traffic_sum[i]*0.2167);
		consolidated_fuel[i]=total_fuel[i]*1.0;
		consolidated_time[i]=total_time[i]*1.0;
		
		//printf("\nTotal time required for path %c (in sec.): %d",i+65,total_time[i]);
		//printf("\nConsolidated time required for path %c (in sec.): %d",i+65,consolidated_time[i]);
	}
	
	for(i=1;i< N;i++)
    for(j=1;j< N;j++)
    {
    	cost[i][j]=IN;
    	cost_time[i][j]=IN;
    	cost_dist[i][j]=IN;
    }
    
    cost[1][2]=cost[2][1]=consolidated_fuel[0];
    cost[1][22]=cost[22][1]=consolidated_fuel[1];
    cost[2][3]=cost[3][2]=consolidated_fuel[2];
    cost[2][22]=cost[22][2]=consolidated_fuel[3];
	cost[3][4]=cost[4][3]=consolidated_fuel[4];
	cost[3][23]=cost[23][3]=consolidated_fuel[5];
	cost[4][5]=cost[5][4]=consolidated_fuel[6];
    cost[4][23]=cost[23][4]=consolidated_fuel[7];
    cost[5][6]=cost[6][5]=consolidated_fuel[8];
    cost[5][24]=cost[24][5]=consolidated_fuel[9];
	cost[6][7]=cost[7][6]=consolidated_fuel[10];
	cost[6][24]=cost[24][6]=consolidated_fuel[11];
	cost[7][8]=cost[8][7]=consolidated_fuel[12];
    cost[7][25]=cost[25][7]=consolidated_fuel[13];
    cost[8][9]=cost[9][8]=consolidated_fuel[14];
    cost[8][26]=cost[26][8]=consolidated_fuel[15];
	cost[9][10]=cost[10][9]=consolidated_fuel[16];
	cost[9][27]=cost[27][9]=consolidated_fuel[17];
	cost[10][11]=cost[11][10]=consolidated_fuel[18];
    cost[10][29]=cost[29][10]=consolidated_fuel[19];
    cost[11][12]=cost[12][11]=consolidated_fuel[20];
    cost[11][28]=cost[28][11]=consolidated_fuel[21];
	cost[12][13]=cost[13][12]=consolidated_fuel[22];
	cost[13][14]=cost[14][13]=consolidated_fuel[23];
	cost[13][28]=cost[28][13]=consolidated_fuel[24];
    cost[14][15]=cost[15][14]=consolidated_fuel[25];
    cost[14][30]=cost[30][14]=consolidated_fuel[26];
    cost[15][16]=cost[16][15]=consolidated_fuel[27];
	cost[16][17]=cost[17][16]=consolidated_fuel[28];
	cost[16][33]=cost[33][16]=consolidated_fuel[29];
	cost[17][18]=cost[18][17]=consolidated_fuel[30];
    cost[17][34]=cost[34][17]=consolidated_fuel[31];
    cost[18][19]=cost[19][18]=consolidated_fuel[32];
    cost[18][44]=cost[44][18]=consolidated_fuel[33];
    cost[19][20]=cost[20][19]=consolidated_fuel[34];
	cost[19][36]=cost[36][19]=consolidated_fuel[35];
	cost[20][21]=cost[21][20]=consolidated_fuel[36];
	cost[20][37]=cost[37][20]=consolidated_fuel[37];
    cost[21][22]=cost[22][21]=consolidated_fuel[38];
    cost[23][37]=cost[37][23]=consolidated_fuel[39];
    cost[23][38]=cost[38][23]=consolidated_fuel[40];
	cost[24][25]=cost[25][24]=consolidated_fuel[41];
	cost[24][38]=cost[38][24]=consolidated_fuel[42];
	cost[25][41]=cost[41][25]=consolidated_fuel[43];
    cost[26][27]=cost[27][26]=consolidated_fuel[44];
    cost[26][42]=cost[42][26]=consolidated_fuel[45];
    cost[27][43]=cost[43][27]=consolidated_fuel[46];
	cost[28][29]=cost[29][28]=consolidated_fuel[47];
	cost[29][30]=cost[30][29]=consolidated_fuel[48];
	cost[30][31]=cost[31][30]=consolidated_fuel[49];
    cost[30][43]=cost[43][30]=consolidated_fuel[50];
    cost[31][32]=cost[32][31]=consolidated_fuel[51];
    cost[31][35]=cost[35][31]=consolidated_fuel[52];
	cost[31][42]=cost[42][31]=consolidated_fuel[53];
	cost[32][33]=cost[33][32]=consolidated_fuel[54];
	cost[32][35]=cost[35][32]=consolidated_fuel[55];
    cost[33][34]=cost[34][33]=consolidated_fuel[56];
    cost[34][35]=cost[35][34]=consolidated_fuel[57];
    cost[35][40]=cost[40][35]=consolidated_fuel[58];
	cost[36][37]=cost[37][36]=consolidated_fuel[59];
	cost[36][38]=cost[38][36]=consolidated_fuel[60];
	cost[38][39]=cost[39][38]=consolidated_fuel[61];
    cost[38][44]=cost[44][38]=consolidated_fuel[62];
    cost[39][40]=cost[40][39]=consolidated_fuel[63];
    cost[39][44]=cost[44][39]=consolidated_fuel[64];
	cost[40][41]=cost[41][40]=consolidated_fuel[65];
	cost[41][42]=cost[42][41]=consolidated_fuel[66];
	cost[42][43]=cost[43][42]=consolidated_fuel[67];
	
	
	cost_time[1][2]=cost_time[2][1]=consolidated_time[0];
    cost_time[1][22]=cost_time[22][1]=consolidated_time[1];
    cost_time[2][3]=cost_time[3][2]=consolidated_time[2];
    cost_time[2][22]=cost_time[22][2]=consolidated_time[3];
	cost_time[3][4]=cost_time[4][3]=consolidated_time[4];
	cost_time[3][23]=cost_time[23][3]=consolidated_time[5];
	cost_time[4][5]=cost_time[5][4]=consolidated_time[6];
    cost_time[4][23]=cost_time[23][4]=consolidated_time[7];
    cost_time[5][6]=cost_time[6][5]=consolidated_time[8];
    cost_time[5][24]=cost_time[24][5]=consolidated_time[9];
	cost_time[6][7]=cost_time[7][6]=consolidated_time[10];
	cost_time[6][24]=cost_time[24][6]=consolidated_time[11];
	cost_time[7][8]=cost_time[8][7]=consolidated_time[12];
    cost_time[7][25]=cost_time[25][7]=consolidated_time[13];
    cost_time[8][9]=cost_time[9][8]=consolidated_time[14];
    cost_time[8][26]=cost_time[26][8]=consolidated_time[15];
	cost_time[9][10]=cost_time[10][9]=consolidated_time[16];
	cost_time[9][27]=cost_time[27][9]=consolidated_time[17];
	cost_time[10][11]=cost_time[11][10]=consolidated_time[18];
    cost_time[10][29]=cost_time[29][10]=consolidated_time[19];
    cost_time[11][12]=cost_time[12][11]=consolidated_time[20];
    cost_time[11][28]=cost_time[28][11]=consolidated_time[21];
	cost_time[12][13]=cost_time[13][12]=consolidated_time[22];
	cost_time[13][14]=cost_time[14][13]=consolidated_time[23];
	cost_time[13][28]=cost_time[28][13]=consolidated_time[24];
    cost_time[14][15]=cost_time[15][14]=consolidated_time[25];
    cost_time[14][30]=cost_time[30][14]=consolidated_time[26];
    cost_time[15][16]=cost_time[16][15]=consolidated_time[27];
	cost_time[16][17]=cost_time[17][16]=consolidated_time[28];
	cost_time[16][33]=cost_time[33][16]=consolidated_time[29];
	cost_time[17][18]=cost_time[18][17]=consolidated_time[30];
    cost_time[17][34]=cost_time[34][17]=consolidated_time[31];
    cost_time[18][19]=cost_time[19][18]=consolidated_time[32];
    cost_time[18][44]=cost_time[44][18]=consolidated_time[33];
    cost_time[19][20]=cost_time[20][19]=consolidated_time[34];
	cost_time[19][36]=cost_time[36][19]=consolidated_time[35];
	cost_time[20][21]=cost_time[21][20]=consolidated_time[36];
	cost_time[20][37]=cost_time[37][20]=consolidated_time[37];
    cost_time[21][22]=cost_time[22][21]=consolidated_time[38];
    cost_time[23][37]=cost_time[37][23]=consolidated_time[39];
    cost_time[23][38]=cost_time[38][23]=consolidated_time[40];
	cost_time[24][25]=cost_time[25][24]=consolidated_time[41];
	cost_time[24][38]=cost_time[38][24]=consolidated_time[42];
	cost_time[25][41]=cost_time[41][25]=consolidated_time[43];
    cost_time[26][27]=cost_time[27][26]=consolidated_time[44];
    cost_time[26][42]=cost_time[42][26]=consolidated_time[45];
    cost_time[27][43]=cost_time[43][27]=consolidated_time[46];
	cost_time[28][29]=cost_time[29][28]=consolidated_time[47];
	cost_time[29][30]=cost_time[30][29]=consolidated_time[48];
	cost_time[30][31]=cost_time[31][30]=consolidated_time[49];
    cost_time[30][43]=cost_time[43][30]=consolidated_time[50];
    cost_time[31][32]=cost_time[32][31]=consolidated_time[51];
    cost_time[31][35]=cost_time[35][31]=consolidated_time[52];
	cost_time[31][42]=cost_time[42][31]=consolidated_time[53];
	cost_time[32][33]=cost_time[33][32]=consolidated_time[54];
	cost_time[32][35]=cost_time[35][32]=consolidated_time[55];
    cost_time[33][34]=cost_time[34][33]=consolidated_time[56];
    cost_time[34][35]=cost_time[35][34]=consolidated_time[57];
    cost_time[35][40]=cost_time[40][35]=consolidated_time[58];
	cost_time[36][37]=cost_time[37][36]=consolidated_time[59];
	cost_time[36][38]=cost_time[38][36]=consolidated_time[60];
	cost_time[38][39]=cost_time[39][38]=consolidated_time[61];
    cost_time[38][44]=cost_time[44][38]=consolidated_time[62];
    cost_time[39][40]=cost_time[40][39]=consolidated_time[63];
    cost_time[39][44]=cost_time[44][39]=consolidated_time[64];
	cost_time[40][41]=cost_time[41][40]=consolidated_time[65];
	cost_time[41][42]=cost_time[42][41]=consolidated_time[66];
	cost_time[42][43]=cost_time[43][42]=consolidated_time[67];
	
	   
	cost_dist[1][2]=cost_dist[2][1]=path_length[0];
    cost_dist[1][22]=cost_dist[22][1]=path_length[1];
    cost_dist[2][3]=cost_dist[3][2]=path_length[2];
    cost_dist[2][22]=cost_dist[22][2]=path_length[3];
	cost_dist[3][4]=cost_dist[4][3]=path_length[4];
	cost_dist[3][23]=cost_dist[23][3]=path_length[5];
	cost_dist[4][5]=cost_dist[5][4]=path_length[6];
    cost_dist[4][23]=cost_dist[23][4]=path_length[7];
    cost_dist[5][6]=cost_dist[6][5]=path_length[8];
    cost_dist[5][24]=cost_dist[24][5]=path_length[9];
	cost_dist[6][7]=cost_dist[7][6]=path_length[10];
	cost_dist[6][24]=cost_dist[24][6]=path_length[11];
	cost_dist[7][8]=cost_dist[8][7]=path_length[12];
    cost_dist[7][25]=cost_dist[25][7]=path_length[13];
    cost_dist[8][9]=cost_dist[9][8]=path_length[14];
    cost_dist[8][26]=cost_dist[26][8]=path_length[15];
	cost_dist[9][10]=cost_dist[10][9]=path_length[16];
	cost_dist[9][27]=cost_dist[27][9]=path_length[17];
	cost_dist[10][11]=cost_dist[11][10]=path_length[18];
    cost_dist[10][29]=cost_dist[29][10]=path_length[19];
    cost_dist[11][12]=cost_dist[12][11]=path_length[20];
    cost_dist[11][28]=cost_dist[28][11]=path_length[21];
	cost_dist[12][13]=cost_dist[13][12]=path_length[22];
	cost_dist[13][14]=cost_dist[14][13]=path_length[23];
	cost_dist[13][28]=cost_dist[28][13]=path_length[24];
    cost_dist[14][15]=cost_dist[15][14]=path_length[25];
    cost_dist[14][30]=cost_dist[30][14]=path_length[26];
    cost_dist[15][16]=cost_dist[16][15]=path_length[27];
	cost_dist[16][17]=cost_dist[17][16]=path_length[28];
	cost_dist[16][33]=cost_dist[33][16]=path_length[29];
	cost_dist[17][18]=cost_dist[18][17]=path_length[30];
    cost_dist[17][34]=cost_dist[34][17]=path_length[31];
    cost_dist[18][19]=cost_dist[19][18]=path_length[32];
    cost_dist[18][44]=cost_dist[44][18]=path_length[33];
    cost_dist[19][20]=cost_dist[20][19]=path_length[34];
	cost_dist[19][36]=cost_dist[36][19]=path_length[35];
	cost_dist[20][21]=cost_dist[21][20]=path_length[36];
	cost_dist[20][37]=cost_dist[37][20]=path_length[37];
    cost_dist[21][22]=cost_dist[22][21]=path_length[38];
    cost_dist[23][37]=cost_dist[37][23]=path_length[39];
    cost_dist[23][38]=cost_dist[38][23]=path_length[40];
	cost_dist[24][25]=cost_dist[25][24]=path_length[41];
	cost_dist[24][38]=cost_dist[38][24]=path_length[42];
	cost_dist[25][41]=cost_dist[41][25]=path_length[43];
    cost_dist[26][27]=cost_dist[27][26]=path_length[44];
    cost_dist[26][42]=cost_dist[42][26]=path_length[45];
    cost_dist[27][43]=cost_dist[43][27]=path_length[46];
	cost_dist[28][29]=cost_dist[29][28]=path_length[47];
	cost_dist[29][30]=cost_dist[30][29]=path_length[48];
	cost_dist[30][31]=cost_dist[31][30]=path_length[49];
    cost_dist[30][43]=cost_dist[43][30]=path_length[50];
    cost_dist[31][32]=cost_dist[32][31]=path_length[51];
    cost_dist[31][35]=cost_dist[35][31]=path_length[52];
	cost_dist[31][42]=cost_dist[42][31]=path_length[53];
	cost_dist[32][33]=cost_dist[33][32]=path_length[54];
	cost_dist[32][35]=cost_dist[35][32]=path_length[55];
    cost_dist[33][34]=cost_dist[34][33]=path_length[56];
    cost_dist[34][35]=cost_dist[35][34]=path_length[57];
    cost_dist[35][40]=cost_dist[40][35]=path_length[58];
	cost_dist[36][37]=cost_dist[37][36]=path_length[59];
	cost_dist[36][38]=cost_dist[38][36]=path_length[60];
	cost_dist[38][39]=cost_dist[39][38]=path_length[61];
    cost_dist[38][44]=cost_dist[44][38]=path_length[62];
    cost_dist[39][40]=cost_dist[40][39]=path_length[63];
    cost_dist[39][44]=cost_dist[44][39]=path_length[64];
	cost_dist[40][41]=cost_dist[41][40]=path_length[65];
	cost_dist[41][42]=cost_dist[42][41]=path_length[66];
	cost_dist[42][43]=cost_dist[43][42]=path_length[67];
	   
    co = dijkstra(cost,source,target,cost_time,cost_dist);
    //printf("\n\nFuel for Shortest Path(in ml.): %d",co);
	}
	t=clock()-t;
	double time_taken=((double)t)/1000.0;
	printf("\n\nExecution time : %.3f ms",time_taken);

	getch();
}

int dijkstra(int cost[][N],int source,int target,int cost_time[][N],int cost_dist[][N])
{
    FILE *fw;	
	fw=fopen("output.csv","a");
	if(fw==NULL)
	{
	puts ( "Cannot open file" ) ;
	}
	
	int dist[N],prev[N],selected[N]={0},i,m,min,start,d,j,largest=0,a,f=0,shortest_time[45][1000],sum_path_time,p=0,q,temp1,temp2,path_time=0,len,arr[50][1000],
	large_probab,best=0,path_int[45],green_length,best_length,space[50],large_space,path_dist=0,sum_path_dist,arr_dist[50][1000];
    char path[N],list_of_paths[50][45],greenest_path[45],best_path[45];
    float probab,mean_time[50],sq_diff[50][1000],sum_sq_diff[50],mean_sq_diff[50],standard_dev[50],cov[50],small_mean,small_cov,large_probab_float,
	product[50],mean_dist[50],zero_correct[50];
    
    FILE *shortest_time_plot;
	shortest_time_plot=fopen("shortest_time.dat","w");
    
    counter++;
     
    for(i=1;i< N;i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    
    while(selected[target]==0)							
    {	
    	min = IN;
        m = 0;
        for(i=1;i< N;i++)
        {
            d = dist[start] +cost[start][i];
            if((d< dist[i])&&(selected[i]==0))
            {
                dist[i] = d;
                prev[i] = start;
            }
            if((min>dist[i]) && (selected[i]==0))
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j++] = start;
        start = prev[start];
    }
    path[j]='\0';
    strrev(path);
    
    //printf("\n\nThe Shortest Path: %s", path);
        
    len=strlen(path);
       
	for(i=0;i<len-1;i++)
	{
		temp1=path[i];
    	temp2=path[i+1]; 
    	//printf("\n\n%d%d",temp1,temp2);											//1=49
    	path_time+=cost_time[temp1][temp2];	
    	path_dist+=cost_dist[temp1][temp2];
	}
	
    
    if(counter==1)
	{
		strcpy(list_of_paths[counter-1],path);
		c[count_in_list]++;
		arr[count_in_list][0]=path_time;
		arr_dist[count_in_list][0]=path_dist;
		sum_time[count_in_list]=arr[count_in_list][0];
		sum_dist[count_in_list]=arr_dist[count_in_list][0];
		count_in_list++;
	}
	else
	{
		for(i=0;i<count_in_list;i++)
		{
			a=strcmp(&list_of_paths[i][0],path) ;
			if(a==0)
			{
				f=1;
				arr[i][c[i]]=path_time;
				arr_dist[i][c[i]]=path_dist;
				sum_time[i]+=arr[i][c[i]];
				sum_dist[i]+=arr_dist[i][c[i]];
				c[i]++;
			}
		}
		
		if(f==0)
		{	
			strcpy(list_of_paths[count_in_list],path);	
			c[count_in_list]++;
			arr[count_in_list][0]=path_time;
			arr_dist[count_in_list][0]=path_dist;
			sum_time[count_in_list]+=arr[count_in_list][0];
			sum_dist[count_in_list]+=arr_dist[count_in_list][0];
			count_in_list++;	
		}
		
	}

	if(counter==ITERATIONS)	
	{
		printf("\n\nFrequency of:\n");
			
		/*
		for(i=0;i<c[0];i++)
		{
			//fprintf(shortest_time_plot,"%d\t %d\n",i+1,shortest_time[largest][i]);
			
		}
		*/
		
		for(i=0;i<count_in_list;i++)
		{
		printf("\n");
		j=0;
		while(list_of_paths[i][j]!='\0')
		{
			printf("%d-",list_of_paths[i][j]);	
			j++;		
		}
		
		/*
		for(j=0;j<6;j++)					
		{
			printf("%d",list_of_paths[i][j]);			
		}
		*/
		
		printf(" : %d",c[i]);
		}
		
		
		//printf("\n");
		
		for(i=0;i<count_in_list;i++)
		{
			for(j=0;j<c[i];j++)
			{
			//printf("\n%d",arr[i][j]);
			
			//printf("\nS:%0.1f",sum_time[i]);
			mean_time[i]=sum_time[i]/c[i];
			mean_dist[i]=sum_dist[i]/c[i];
			//printf("\tM:%0.4f",mean_time[i]);
			//printf("\n");
			}
		}
		
		
		//printf("\n\n");
		for(i=0;i<count_in_list;i++)
		{	
			sum_sq_diff[i]=0;
			for(j=0;j<c[i];j++)
			{
				sq_diff[i][j]=pow((arr[i][j]-mean_time[i]),2);
				//printf("%0.3f\t",sq_diff[i][j]);
				sum_sq_diff[i]+=sq_diff[i][j];
			}
			//printf("\n");
			mean_sq_diff[i]=sum_sq_diff[i]/c[i];
			standard_dev[i]=pow(mean_sq_diff[i],0.5);
			cov[i]=standard_dev[i]/mean_time[i];
			zero_correct[i]=cov[i];
		}
		
		printf("\n");
		for(i=0;i<count_in_list;i++)
		{
			printf("\nPATH:");
			j=0;
			while(list_of_paths[i][j]!='\0')
			{
			printf("%d-",list_of_paths[i][j]);	
			j++;		
			}
			printf("\nPROBAB:%0.3f  MEAN TIME:%0.4f sec.  MEAN DISTANCE:%0.1f km  COV:%0.4f\n",c[i]/ITERATIONS,mean_time[i],mean_dist[i],cov[i]);			
			
			/*
			if(i>0)
			{
				fprintf(fw,"321,,,456,");
			}
			fprintf(fw,"%f,%f,%f,%f,",c[i]/ITERATIONS,mean_dist[i],mean_time[i],cov[i]);
			*/
		}
		
		large_probab=c[0];
		small_mean=mean_time[0];
		small_cov=cov[0];
		
		for(i=1;i<count_in_list;i++)
		{
			if(large_probab<c[i])	
			large_probab=c[i];
			if(small_mean>mean_time[i])	
			small_mean=mean_time[i];
			if(small_cov>cov[i])	
			small_cov=cov[i];
		
		}
		
		large_probab_float=large_probab;

		//printf("\n\nBest:%0.3f\t%0.4f\t%0.4f",large_probab/ITERATIONS,small_mean,small_cov);
				
		printf("\n\nNORMALIZATION\n");		
				
		if(small_cov==0.0)								//to remove division by zero
		{
			for(i=0;i<count_in_list;i++)
		{
			if(cov[i]==0.0)
			cov[i]=0.0001;
		}
			small_cov=0.0001;
		}
		
		for(i=0;i<count_in_list;i++)
		{
			j=0;
			space[i]=0;
			while(list_of_paths[i][j]!='\0')
			{	
			j++;
			space[i]++;
			}
		}
		
		large_space=space[0];
		for(i=1;i<count_in_list;i++)
		{	
			if(large_space<space[i])	
			large_space=space[i];
		}
			
		
		printf("\n");
		for(i=0;i<count_in_list;i++)
		{
			printf("\nPATH:");
			j=0;
			if(i>0)
			fprintf(fw,",,,,,,,");
			while(list_of_paths[i][j]!='\0')
			{
			printf("%d-",list_of_paths[i][j]);	
			fprintf(fw,"%d-",list_of_paths[i][j]);
			j++;		
			}
			
			fprintf(fw,",");
			
			for(q=0;q<(large_space-space[i]);q++)
			printf("  ");
			
			printf(" %0.4f  %0.4f  %0.4f",c[i]/large_probab_float,small_mean/mean_time[i],small_cov/cov[i]);		
			product[i]=(c[i]/large_probab_float)*(small_mean/mean_time[i])*(small_cov/cov[i]);
			printf(" = %0.4f",product[i]);
			fprintf(fw,"%f,%f,%f,%f,",c[i]/ITERATIONS,mean_dist[i],mean_time[i],zero_correct[i]);
			fprintf(fw,"%f,%f,%f,%f\n",c[i]/large_probab_float,small_mean/mean_time[i],small_cov/cov[i],product[i]);
		}
		
		for(i=1;i<count_in_list;i++)
		{
			if(product[0]<product[i])	
			{
			product[0]=product[i];
			best=i;
			}
			
		}
		
		for(i=1;i<count_in_list;i++)
		{
			if(c[0]<c[i])	
			{
			c[0]=c[i];
			largest=i;
			}
			
		}
		
		switch(largest)
		{
			case 0:strcpy(greenest_path,list_of_paths[0]);break;
			case 1:strcpy(greenest_path,list_of_paths[1]);break;	
			case 2:strcpy(greenest_path,list_of_paths[2]);break;
			case 3:strcpy(greenest_path,list_of_paths[3]);break;
			case 4:strcpy(greenest_path,list_of_paths[4]);break;
			case 5:strcpy(greenest_path,list_of_paths[5]);break;
			case 6:strcpy(greenest_path,list_of_paths[6]);break;	
			case 7:strcpy(greenest_path,list_of_paths[7]);break;
			case 8:strcpy(greenest_path,list_of_paths[8]);break;
			case 9:strcpy(greenest_path,list_of_paths[9]);break;
			case 10:strcpy(greenest_path,list_of_paths[10]);break;
			case 11:strcpy(greenest_path,list_of_paths[11]);break;	
			case 12:strcpy(greenest_path,list_of_paths[12]);break;
			case 13:strcpy(greenest_path,list_of_paths[13]);break;
			case 14:strcpy(greenest_path,list_of_paths[14]);break;
			case 15:strcpy(greenest_path,list_of_paths[15]);break;
			case 16:strcpy(greenest_path,list_of_paths[16]);break;	
			case 17:strcpy(greenest_path,list_of_paths[17]);break;
			case 18:strcpy(greenest_path,list_of_paths[18]);break;
			case 19:strcpy(greenest_path,list_of_paths[19]);break;
			case 20:strcpy(greenest_path,list_of_paths[20]);break;
			case 21:strcpy(greenest_path,list_of_paths[221]);break;	
			case 22:strcpy(greenest_path,list_of_paths[22]);break;
			case 23:strcpy(greenest_path,list_of_paths[23]);break;
			case 24:strcpy(greenest_path,list_of_paths[24]);break;
			case 25:strcpy(greenest_path,list_of_paths[25]);break;
			case 26:strcpy(greenest_path,list_of_paths[26]);break;	
			case 27:strcpy(greenest_path,list_of_paths[27]);break;
			case 28:strcpy(greenest_path,list_of_paths[28]);break;
			case 29:strcpy(greenest_path,list_of_paths[29]);break;
			case 30:strcpy(greenest_path,list_of_paths[30]);break;
			case 31:strcpy(greenest_path,list_of_paths[31]);break;	
			case 32:strcpy(greenest_path,list_of_paths[32]);break;
			case 33:strcpy(greenest_path,list_of_paths[33]);break;
			case 34:strcpy(greenest_path,list_of_paths[34]);break;
			case 35:strcpy(greenest_path,list_of_paths[35]);break;
			case 36:strcpy(greenest_path,list_of_paths[36]);break;	
			case 37:strcpy(greenest_path,list_of_paths[37]);break;
			case 38:strcpy(greenest_path,list_of_paths[38]);break;
			case 39:strcpy(greenest_path,list_of_paths[39]);break;
			case 40:strcpy(greenest_path,list_of_paths[40]);break;
			case 41:strcpy(greenest_path,list_of_paths[41]);break;	
			case 42:strcpy(greenest_path,list_of_paths[42]);break;
			case 43:strcpy(greenest_path,list_of_paths[43]);break;
			case 44:strcpy(greenest_path,list_of_paths[44]);break;
			case 45:strcpy(greenest_path,list_of_paths[45]);break;
			case 46:strcpy(greenest_path,list_of_paths[46]);break;	
			case 47:strcpy(greenest_path,list_of_paths[47]);break;
			case 48:strcpy(greenest_path,list_of_paths[48]);break;
			case 49:strcpy(greenest_path,list_of_paths[49]);break;
			}
				
		switch(best)
		{
			case 0:strcpy(best_path,list_of_paths[0]);break;
			case 1:strcpy(best_path,list_of_paths[1]);break;	
			case 2:strcpy(best_path,list_of_paths[2]);break;
			case 3:strcpy(best_path,list_of_paths[3]);break;
			case 4:strcpy(best_path,list_of_paths[4]);break;
			case 5:strcpy(best_path,list_of_paths[5]);break;
			case 6:strcpy(best_path,list_of_paths[6]);break;	
			case 7:strcpy(best_path,list_of_paths[7]);break;
			case 8:strcpy(best_path,list_of_paths[8]);break;
			case 9:strcpy(best_path,list_of_paths[9]);break;
			case 10:strcpy(best_path,list_of_paths[10]);break;
			case 11:strcpy(best_path,list_of_paths[11]);break;	
			case 12:strcpy(best_path,list_of_paths[12]);break;
			case 13:strcpy(best_path,list_of_paths[13]);break;
			case 14:strcpy(best_path,list_of_paths[14]);break;
			case 15:strcpy(best_path,list_of_paths[15]);break;
			case 16:strcpy(best_path,list_of_paths[16]);break;	
			case 17:strcpy(best_path,list_of_paths[17]);break;
			case 18:strcpy(best_path,list_of_paths[18]);break;
			case 19:strcpy(best_path,list_of_paths[19]);break;
			case 20:strcpy(best_path,list_of_paths[20]);break;
			case 21:strcpy(best_path,list_of_paths[21]);break;	
			case 22:strcpy(best_path,list_of_paths[22]);break;
			case 23:strcpy(best_path,list_of_paths[23]);break;
			case 24:strcpy(best_path,list_of_paths[24]);break;
			case 25:strcpy(best_path,list_of_paths[25]);break;
			case 26:strcpy(best_path,list_of_paths[26]);break;	
			case 27:strcpy(best_path,list_of_paths[27]);break;
			case 28:strcpy(best_path,list_of_paths[28]);break;
			case 29:strcpy(best_path,list_of_paths[29]);break;
			case 30:strcpy(best_path,list_of_paths[30]);break;
			case 31:strcpy(best_path,list_of_paths[31]);break;	
			case 32:strcpy(best_path,list_of_paths[32]);break;
			case 33:strcpy(best_path,list_of_paths[33]);break;
			case 34:strcpy(best_path,list_of_paths[34]);break;
			case 35:strcpy(best_path,list_of_paths[35]);break;
			case 36:strcpy(best_path,list_of_paths[36]);break;	
			case 37:strcpy(best_path,list_of_paths[37]);break;
			case 38:strcpy(best_path,list_of_paths[38]);break;
			case 39:strcpy(best_path,list_of_paths[39]);break;
			case 40:strcpy(best_path,list_of_paths[40]);break;
			case 41:strcpy(best_path,list_of_paths[41]);break;	
			case 42:strcpy(best_path,list_of_paths[42]);break;
			case 43:strcpy(best_path,list_of_paths[43]);break;
			case 44:strcpy(best_path,list_of_paths[44]);break;
			case 45:strcpy(best_path,list_of_paths[45]);break;
			case 46:strcpy(best_path,list_of_paths[46]);break;	
			case 47:strcpy(best_path,list_of_paths[47]);break;
			case 48:strcpy(best_path,list_of_paths[48]);break;
			case 49:strcpy(best_path,list_of_paths[49]);break;
			
		}
		
		probab=c[0]/ITERATIONS;
		
		green_length=strlen(greenest_path);
		best_length=strlen(best_path);
		
		printf("\n\nGreenest path is ");
		for(i=0;i<green_length;i++)
		{
			printf("%d-",greenest_path[i]);
		}
		printf(" with probability %.3f",probab);
		
		printf("\n\nBest path is ",best_path);													
		for(i=0;i<best_length;i++)
		{
			printf("%d-",best_path[i]);
		}
	}
		
	fclose(shortest_time_plot);
	fclose(fw);
    return dist[target];
}
