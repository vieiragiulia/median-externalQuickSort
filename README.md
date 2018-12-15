# median-externalQuickSort
this takes a matrix of integers and gives you the average and median of each line, also the average of the whole matrix
to get the median I used external Quicksort
here the input needs to be ./tp3 input.txt output.txt LIM_M as LIM_M is the number of Mb available to use in the program
if you don't use LIM_M it will assume it is 2 and may take to long to process
the input file needs to have, on it first line m and n for a matrix mxn. On the next m lines the n elements of it, separated by space.
the output is [average],[median] for each line, then [total average] on an extra line of the new file.
I chose externalQuickSort because it is more intuitive and simple than externalMergeSort. Also here I only use one auxiliar file, which is destroyed at the end of the program, so it won't occupy all of your file with trash. 
Even if you don't need the median or the average, the libraries used are independent enought to help you sort any file with little or no effort.
this was a college project
