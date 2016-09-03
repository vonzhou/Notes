


Collections:

public static <T> void sort(List<T> list, Comparator<? super T> c) {
	list.sort(c);
}

List:

default void sort(Comparator<? super E> c) {
	Object[] a = this.toArray();
	Arrays.sort(a, (Comparator) c);
	ListIterator<E> i = this.listIterator();
	for (Object e : a) {
		i.next();
		i.set((E) e);
	}
}


Arrays:

稳定排序，

public static <T> void sort(T[] a, Comparator<? super T> c) {
	if (c == null) {
		sort(a);
	} else { // 因为TimSort是jdk1.7引入的，使用了性能更好的Timsort，但是也是可以使用遗留的merge sort
		if (LegacyMergeSort.userRequested)
			legacyMergeSort(a, c);
		else
			TimSort.sort(a, 0, a.length, c, null, 0, 0);
	}
}




排序这个数组的给定区间，后面三个参数先忽略。待排序的个数如果小于32（MIN_MERGE），

static <T> void sort(T[] a, int lo, int hi, Comparator<? super T> c,
	T[] work, int workBase, int workLen) {
	assert c != null && a != null && lo >= 0 && lo <= hi && hi <= a.length;

	int nRemaining  = hi - lo;
	if (nRemaining < 2)
		 return;  // Arrays of size 0 and 1 are always sorted

    // If array is small, do a "mini-TimSort" with no merges      情况（1）
    if (nRemaining < MIN_MERGE) {  // 32
    	int initRunLen = countRunAndMakeAscending(a, lo, hi, c);
    	binarySort(a, lo, hi, lo + initRunLen, c);
    	return;
    }

    /**
     * March over the array once, left to right, finding natural runs,
     * extending short natural runs to minRun elements, and merging runs
     * to maintain stack invariant.							情况（2）
     */
    TimSort<T> ts = new TimSort<>(a, c, work, workBase, workLen);
    int minRun = minRunLength(nRemaining);
    do {
        // Identify next run
    	int runLen = countRunAndMakeAscending(a, lo, hi, c);

        // If run is short, extend to min(minRun, nRemaining)
    	if (runLen < minRun) {
    		int force = nRemaining <= minRun ? nRemaining : minRun;
    		binarySort(a, lo, lo + force, lo + runLen, c);
    		runLen = force;
    	}

        // Push run onto pending-run stack, and maybe merge
    	ts.pushRun(lo, runLen);
    	ts.mergeCollapse();

        // Advance to find next run
    	lo += runLen;
    	nRemaining -= runLen;
    } while (nRemaining != 0);

    // Merge all remaining runs to complete sort
    assert lo == hi;
    ts.mergeForceCollapse();
    assert ts.stackSize == 1;
}

先看看run的定义，翻译成趋向？一个run是从数组给定位置开始的最长递增活递减序列的长度，为了得到稳定的归并排序，这里的降序中使用的“>”，不包含"=",保证stability。代码中的原注释是：

* Returns the length of the run beginning at the specified position in
* the specified array and reverses the run if it is descending (ensuring
* that the run will always be ascending when the method returns).
*
* A run is the longest ascending sequence with:
*
*    a[lo] <= a[lo + 1] <= a[lo + 2] <= ...
*
* or the longest descending sequence with:
*
*    a[lo] >  a[lo + 1] >  a[lo + 2] >  ...
*
* For its intended use in a stable mergesort, the strictness of the
* definition of "descending" is needed so that the call can safely
* reverse a descending sequence without violating stability.

private static <T> int countRunAndMakeAscending(T[] a, int lo, int hi,
                                                Comparator<? super T> c) {
    assert lo < hi;
    int runHi = lo + 1;
    if (runHi == hi)
        return 1;

    // Find end of run, and reverse range if descending
    if (c.compare(a[runHi++], a[lo]) < 0) { // Descending
        while (runHi < hi && c.compare(a[runHi], a[runHi - 1]) < 0)
            runHi++;
        // 如果是递减序列，那么就得到最长的，然后逆序
        reverseRange(a, lo, runHi);
    } else {                              // Ascending
        while (runHi < hi && c.compare(a[runHi], a[runHi - 1]) >= 0)
            runHi++;
    }

    return runHi - lo;  // 这个run的最大长度
}

举个例子吧，如下图：



获得初始的run长度后，调用 binarySort(a, lo, hi, lo + initRunLen, c)，binarySort 当然不会浪费时间再去排序在求run长度时已经排好序的头部（lo->start），然后进行二分插入排序。


/**
* Sorts the specified portion of the specified array using a binary
* insertion sort.  This is the best method for sorting small numbers
* of elements.  It requires O(n log n) compares, but O(n^2) data
* movement (worst case).
*
*/
private static <T> void binarySort(T[] a, int lo, int hi, int start,
	Comparator<? super T> c) {
	assert lo <= start && start <= hi;
	if (start == lo)
		start++;
	for ( ; start < hi; start++) {
		T pivot = a[start];

        // Set left (and right) to the index where a[start] (pivot) belongs
		int left = lo;
		int right = start;
		assert left <= right;
        /*
         * Invariants:  排序过程的不变量
         *   pivot >= all in [lo, left).
         *   pivot <  all in [right, start).
         */
        while (left < right) {
        	int mid = (left + right) >>> 1; 
        	 // 如果 pivot >= a[mid] 那么就快进 left 指针
        	if (c.compare(pivot, a[mid]) < 0)
        		right = mid;
        	else
        		left = mid + 1;
        }
        assert left == right;

        /*
         * The invariants still hold: pivot >= all in [lo, left) and
         * pivot < all in [left, start), so pivot belongs at left.  Note
         * that if there are elements equal to pivot, left points to the
         * first slot after them -- that's why this sort is stable.
         * Slide elements over to make room for pivot.
         */
        int n = start - left;  // The number of elements to move
        // Switch is just an optimization for arraycopy in default case
        switch (n) {
        	case 2:  a[left + 2] = a[left + 1];
        	case 1:  a[left + 1] = a[left];
        	break;
        	default: System.arraycopy(a, left, a, left + 1, n);
        }
        a[left] = pivot;
    }
}



http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6804124























































