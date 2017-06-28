void heapify(int arr[],int n,int i){
	int largest;
	int l;
	int r;

	largest = i;
	l = 2*i + 1;
	r = 2*i + 2;

	if(l < n)
		if(arr[l] > arr[largest])
			largest = l;

	if(r < n)
		if(arr[r] > arr[largest])
			largest = r;

	if(largest != i){
		int temp;
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;

		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n){
	int i;
	i = n/2 - 1;
	while(i >= 0){
		heapify(arr, n, i);
		i = i - 1;
	}

	i = n-1;
	while(i >= 0){
		int temp;
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		heapify(arr, i, 0);

		i = i - 1;
	}
}

void main(void){
	int array[10];
	int i;

	while(i < 10){
		array[i] = input();
		i = i + 1;
	}

	heapSort(array,10);

	while(i < 10){
		output(array[i]);
		i = i + 1;
	}
}
