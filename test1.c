int arr[10];

void BubbleSort(int arr[],int size){
	int i;
	int j;
	i=0;
	j=0;

	while(i<size){
		j = 0;
		while(j<size-i-1){
			if(arr[j] > arr[j+1]){
				int temp;
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
			j = j + 1;
		}
		i = i + 1;
	}
}

void main(void){
	int idx;
	
	idx = 0;
	while(idx < 10){
		arr[idx] = input();
		idx = idx + 1;
	}

	BubbleSort(arr,10);

	idx = 0;
	while(idx < 10){
		output(arr[idx]);
		idx = idx + 1;
	}
}
