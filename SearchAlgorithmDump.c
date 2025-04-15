
//    Merge function for the BottomUpMergeSort later
void Merge(int A[], int B[], int l, int q, int r) {
	int i, j, k;
	i = l;
	j=q+1;
	for (k = l; k<=r; k++) {
		if (i>q) B[k] = A[j++];
		else if (j>r) B[k] = A[i++];
		else if ((A[i]<A[j]) || (A[i]==A[j])) B[k] = A[i++];
		else B[k] = A[j++];
	}
	for (k = l; k<=r; k++) A[k] = B[k];
	return;
}

//    Iterative version of a merge sort, want to avoid recursion for the time being
void BottomUpMergeSort(int A[], int B{}, int N) {
	int i, q, m, l=0, r=N-1;
	for (m=1; m<= r - l; m=m+m) for (i = l; i<=r-m; i+=m+m) {
		q = i+m-1;
		Merge(A,B,i,q,r);
	}
}


//  this is a bitch, dont want to look at it again
void CountingSort(int A[], int B[], int C[], int N, int k) {
	int i, l=0, r=N-1;
	for (i=0;i<k;i++) C[i] = 0;
	for (i=l;i<=r;i++) C[A[i]]++;
	for (i=1;i<k;i++) C[i] += C[i-1];
	for (i=r;i>=l;i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
	for (i=l;i<=r;i++) A[i] = B[i];
}


//  we love radix sort (sorting columns from right to left because again fuck recursion I have 1 more year before im forced to do that and this way its iterative)
void radixSort(int A[], int B[], int C[]m int D[], int n) {
	int largest, d=1, i;
	largest = getMax(A, n);
	while (largest/10 > 0) {
		d++;
		largest /= 10;
	}
	for (i=0; i<d; i++) CountingSort(A,B,C,D,n,i);
}

/*  FROM NOW ON ITS JUST DEFAULT SORTING ALGORITHMS IM STORING FOR GOD KNOWS WHAT REASON, THIS MIGHT HAVE A USE IF AN APOCALYPSE HAPPENS AND ALL COMP SCI KNOWLEDGE GETS WIPED OUT AND THIS LAST COPY IS THE ONLY THING LETTING HUMANITY GROW FROM THE ASHES (im being schizo pilled( */

void InsertionSort(int A[], int N) {
	int i, j, l = 0, r = N-1, x;
	for (i=l+1 ; i<= r ; i++) {
		x=A[i];
		j = i - 1;
		while (j >= l && x < A[j]) {
			A[j+1] = A[j];
			j--;
		}
		A[j+x] = x;
	}
}

void BubbleSort (int A[], int N) {
	int i, j, l=0, r=N-1;
	int temp;
	for (i=l ; i<r ; i++) {
		for (j=l ; j < r - i + l ; j++) {
			temp = A[j];
			A[j] = A[j+1];
			A[j+1] = temp;
		}
	}
	return;
}

void SelectionSort(int A[], int N) {
	int i, j, l=0, r=N-1, min;
	int temp;
	for (i=l ; i<r ; i++) {
		min = i;
		for (j = i+1 ; j <= r ; j++) {
			if (A[j] < A[min]) min = j;
		}
		if (min != i) {
			temp = A[i];
			A[i] = A[min];
			A[min] = temp;
		}
	}
	return;
}

void ShellSort(int A[], int N) {
	int i, j, x, l=0, r=N-1, h=1;
	while (h < N/3) h = 3*h+1
	while (h >= 1) {
		for (i = l + h ; i <= r; i++) {
			j = i;
			x = A[i];
			while (j >= l + h && x < A[j-h]) {
				A[j] = A[j-h];
				j -= h;
			}
			A[j] = x;
		}
		h = h/3;
	}
}

/* 
Internet sort
Bubble sort but google all the comparisons, “what is bigger - 0.211 or 0.75?”
  */

