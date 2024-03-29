#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define FALSE       -1
#define SUCCESS      0
#define MAX_NUM   100000

int **train_array;
int **test_array;
float **knn_sqr;
float **knn_temp;
int **temp_prop;
int train_row = 0, train_column = 0, train_tmp = 0;
int test_row = 0, test_column = 0, test_tmp = 0;
int count,correct_count=0,wrong_count=0;

int readTrainingData(void)
{
    FILE *fTrain= NULL;
    char tmp[10000] = {0};
    char buffer[MAX_NUM] = {0};
    int i = 0, j = 0;
    
    
    if( (fTrain = fopen("sat.trn", "r")) == NULL )
        return FALSE;


    while( fgets(buffer, MAX_NUM, fTrain) != NULL )
    {
        train_row += 1;
        
        for(i=0, j=0; i<=(int)strlen(buffer); i++)
        {
           if( (buffer[i] == '\n') || (buffer[i] == '\t') )
           {
               train_tmp++;
               j = 0;
               memset(tmp, 0, sizeof(tmp));
           }
           else
           {
               tmp[j] = buffer[i];
               j++;
           }
        }
        
        if( train_tmp > train_column )
            train_column = train_tmp;
        
        train_tmp = 0;
        memset(buffer, 0, sizeof(buffer));
          
    }
    	
    train_array = (int **)malloc(train_row * sizeof(int *));
    
    for(i=0; i<train_row; i++)
        train_array[i] = (int *)malloc(train_column * sizeof(int));
    
    for(i=0; i<train_row; i++)
        for(j=0; j<train_column; j++)
            train_array[i][j] = 0;


    train_row = 0;
    train_column = 0;
    memset(tmp, 0, sizeof(tmp));
    memset(buffer, 0, sizeof(buffer));
    
    
    fseek(fTrain, 0, SEEK_SET);
    
    while( fgets(buffer, MAX_NUM, fTrain) != NULL )
    {
    
        for(i=0, j=0; i<=(int)strlen(buffer); i++)
        {
           if( (buffer[i] == '\n') || (buffer[i] == '\t') )
           {
               train_array[train_row][train_tmp] = atoi(tmp);
               
               train_tmp += 1;
               j = 0;
               memset(tmp, 0, sizeof(tmp));
           }
           else
           {
               tmp[j] = buffer[i];
               j++;
           }
        }
        
        train_row += 1;
        
        if( train_tmp > train_column )
            train_column = train_tmp;
            
        train_tmp = 0;
        memset(buffer, 0, sizeof(buffer));
        
    }
    
    fclose(fTrain);
}
int readTestData(void)
{
    FILE *fTest= NULL;
    char tmp[10000] = {0};
    char buffer[MAX_NUM] = {0};
    int i = 0, j = 0;
    
    
    if( (fTest = fopen("sat.tst", "r")) == NULL )
        return FALSE;


    while( fgets(buffer, MAX_NUM, fTest) != NULL )
    {
        test_row += 1;
        
        for(i=0, j=0; i<=(int)strlen(buffer); i++)
        {
           if( (buffer[i] == '\n') || (buffer[i] == '\t') )
           {
               test_tmp++;
               j = 0;
               memset(tmp, 0, sizeof(tmp));
           }
           else
           {
               tmp[j] = buffer[i];
               j++;
           }
        }
        
        if( test_tmp > test_column )
            test_column = test_tmp;
        
        test_tmp = 0;
        memset(buffer, 0, sizeof(buffer));
          
    }
    	
    test_array = (int **)malloc(test_row * sizeof(int *));
    
    for(i=0; i<test_row; i++)
        test_array[i] = (int *)malloc(test_column * sizeof(int));
    
    for(i=0; i<test_row; i++)
        for(j=0; j<test_column; j++)
            test_array[i][j] = 0;


    test_row = 0;
    test_column = 0;
    memset(tmp, 0, sizeof(tmp));
    memset(buffer, 0, sizeof(buffer));
    
    
    fseek(fTest, 0, SEEK_SET);
    
    while( fgets(buffer, MAX_NUM, fTest) != NULL )
    {
    
        for(i=0, j=0; i<=(int)strlen(buffer); i++)
        {
           if( (buffer[i] == '\n') || (buffer[i] == '\t') )
           {
               test_array[test_row][test_tmp] = atoi(tmp);
               
               test_tmp += 1;
               j = 0;
               memset(tmp, 0, sizeof(tmp));
           }
           else
           {
               tmp[j] = buffer[i];
               j++;
           }
        }
        
        test_row += 1;
        
        if( test_tmp > test_column )
            test_column = test_tmp;
            
        test_tmp = 0;
        memset(buffer, 0, sizeof(buffer));
        
    }
    
    fclose(fTest);
}

int runKNN1(int test_num )
{
	char cmd[50];
	count = 0;
	while(count < 1){
		if( temp_prop[test_num][0] == test_array[test_num][36]){
			correct_count++;
        }
		else{
			wrong_count++;
        }
		count++;
	}
	return correct_count;
}

int runKNN(int test_num,int KNN)
{
	char cmd[50];
    int num,count,i;
	int ans,curr_ans,max;
    int test[7];
    int cur_ans=0;
	int tmp_test=0;
    
		count =0;
		for (i = 0; i < 7; i++) {
			test[i]=0;
		}
		while(count < KNN){
			ans = temp_prop[test_num][count];
			switch (ans){
				case 1:
					test[0]++;
					break;
				case 2:
					test[1]++;
					break;
				case 3:
					test[2]++;
					break;
				case 4:
					test[3]++;
					break;
				case 5:
					test[4]++;
					break;
				case 6:
					break;
				case 7:
					test[6]++;
					break;
			}
			count++;
		}
		for (max=0; max < 7; max++) {
		    if(tmp_test == 0 || test[max]> tmp_test ) {
		        tmp_test = test[max];
			    cur_ans = max+1;
		    }
	        else if(test[max] == tmp_test){
                if(temp_prop[test_num][0] != cur_ans){
                    cur_ans = temp_prop[test_num][0]; 
                }
            }   
        }
		if( cur_ans == test_array[test_num][36])
			correct_count++;
		else
			wrong_count++;

   return correct_count;
}

int runTest()
{
    int test,train,prop_num,i,j,a,b,k,l;
    int prop_ans[36];
    int knn_value=0;

    char cmd[50];
    float temp;
    int tmp_prop;
    int ans[36];   
   
    knn_sqr = (float **)malloc(test_row * sizeof(float *));
    
    for(i=0; i<test_row; i++)
        knn_sqr[i] = (float *)malloc(train_row * sizeof(float));
         
    for(test = 0; test<test_row; test++)
    {
        for(train=0;train<train_row; train++)
        {
            knn_value = 0;                                 
            for (i = 0 ; i < 36 ; i++)
            {
                ans[i]= ((test_array[test][i]- train_array[train][i])*(test_array[test][i]- train_array[train][i]));
                knn_value = knn_value + ans[i];
                  
            }
            knn_sqr[test][train] = sqrt(knn_value);
            
        } 
    }     
}

int runKnn(int i,int KNN_num)
{
    int corrent;
        if(KNN_num == 1)
            corrent = runKNN1(i);
        else 
            corrent = runKNN(i,KNN_num);            
    return corrent;        
}

int runSequence(int KNN_num)/*TODO*/
{
    float temp_knn;
    int prop,corrent;
    int i,j,a,b,k,l,test,train;
    clock_t start, end;
    float time = 0;
    FILE *fp;
    fp = fopen("test.txt","w");
    
    knn_temp = (float **)malloc(test_row * sizeof(float *));
    temp_prop = (int **)malloc(test_row * sizeof(int *));
    for(i=0; i<test_row; i++){
        knn_temp[i] = (float *)malloc(train_row * sizeof(float));
        temp_prop[i] = (int *)malloc(train_row * sizeof(int));
    }
    for(i = 0; i <test_row;i++){
        for( j=0;j<train_row;j++){
            knn_temp[i][j] = knn_sqr[i][j]; 
            temp_prop[i][j] = train_array[j][36];	
        }
    } 

//	Jamie test   
           
	for (i = 0; i < test_row; i++) {   
		for (j = 1; j< train_row; j++) {                    //j = 0不需排序 
			for (k = 0; k < j; k++) { 
				if (knn_temp[i][j] < knn_temp[i][k]) {	//從knn_temp第一個比較，比到knn_temp[i][k] (k < j)大於knn_temp[i][j] (當前最後一個值) 
					temp_knn = knn_temp[i][j];	//記下最後一個值 
					prop = temp_prop[i][j];	     //屬性值，需跟著knn_temp一起移動 
					for (l = j; l > k; l--) {
						knn_temp[i][l] = knn_temp[i][l - 1];	//把數列向後挪 
						temp_prop[i][l]=temp_prop[i][l-1];	
                    }					
					knn_temp[i][k] = temp_knn;
                    temp_prop[i][k] = prop;                    
					break;
				}
			}
         
        }

/*        for (j = 0; j< 20; j++) {
           printf("knn_temp[%d][%d]=%.3f",i,j,knn_temp[i][j]);
           system("pause");
        }*/
        if(KNN_num == 1)
            corrent = runKNN1(i);
        else 
            corrent = runKNN(i,KNN_num); 
	}   
         
    printf("You test %d KNN\n", KNN_num);
    printf("corrent_rate = %.4f\n", corrent/2000.0);
            
  fclose(fp); 	
}

int main(int argc, char **argv)
{
    int KNN_num;
    clock_t start_time, end_time;
    clock_t train_start, train_end;
    clock_t test_start, test_end;
    clock_t run_start, run_end;
    clock_t seq_start, seq_end;
    float total_time = 0;
    float train_time = 0;
    float test_time = 0;
    float run_time = 0;
    float seq_time = 0;
    switch(argc){
       case 2:
            KNN_num = atoi(argv[1]);
            start_time = clock();
            train_start = clock();
            readTrainingData();  //loadTrainingData
            train_end = clock();
            test_start = clock();
            readTestData();      //load Testing Data
            test_end = clock();
            run_start = clock();
            runTest();           //計算距離值 
            run_end =clock();
            seq_start = clock();
            runSequence(KNN_num);   //排序並投票 
            seq_end = clock();      
            end_time = clock();
            break;
    default:
    	printf("usage: Weka.exe [KNN Num]\n");
	break;
    }
    total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    train_time = (float)(train_end - train_start)/CLOCKS_PER_SEC;
    test_time = (float)(test_end - test_start)/CLOCKS_PER_SEC;
    run_time = (float)(run_end - run_start)/CLOCKS_PER_SEC;
    seq_time = (float)(seq_end - seq_start)/CLOCKS_PER_SEC;
    printf("Time : %.4f sec \n", total_time);
    printf("TRAIN Time : %.4f sec \n", train_time);
    printf("TEST Time : %.4f sec \n", test_time);
    printf("RUN Time : %.4f sec \n", run_time);
    printf("SEQ Time : %.4f sec \n", seq_time);
    system("pause");
    return 0;
}
