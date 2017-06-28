int findIndex(int arr[],int size,int val){
	int i;

	i = 0;
	while(i < size){
		if(arr[i] == val){
			return i;
		}
		i = i + 1;
	}

	return size;
}

void main(void){
	int array[10];
	int i;
	int val;

	i = 0;
	while(i < 10){
		array[i] = input();
		i = i + 1;
	}
	
	val = input();

	output(findIndex(array,10,val));
}
