/* Test C- Source Code (test.c) */
/* Purpose: BubbleSort Test				 */

int bubbleSort(int arr[],int size){
	int i;
	int j;
	
	i = 0;
	
	while(i < size){
		int temp;
		while(j <= size-1){
			int temp;
			j=i;
			if(arr[i] > arr[j]){
				int temp;
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j = j + 1;
		}
		i = i + 1;
	}

	/* nested if else shift/reduce conflict resolution example */
	if(i == 0){
		int lastj;
		lastj = j*100;
		return lastj;
	}
	else if(j != 0){
		int lasti;
		lasti = i / 500;
		return lasti;
	}
	else if(i >= j){
		int result;
		result = i - j;
		return result;
	}else
		return 0;
}

void main(void){
	int arr[100];
	int result;

	result = bubbleSort(arr,100);
}
