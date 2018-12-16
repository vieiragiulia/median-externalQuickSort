# median-externalQuickSort
this takes a matrix of integers and gives you the average and median of each line, also the average of the whole matrix
to get the median I used external Quicksort.

Here the input needs to be ./tp3 input.txt output.txt LIM_M as LIM_M is the number of Mb available to use in the program
if you don't use LIM_M it will assume it can only fit 2 integers at a time and may take to long to process the input file needs to have, on it first line m and n for a matrix mxn. On the next m lines the n elements of it, separated by space.

The output is [average],[median] for each line, then [total average] on an extra line of the new file.

I chose externalQuickSort because it is more intuitive and simple than externalMergeSort. Also here I only use one auxiliar file, which is destroyed at the end of the program, so it won't occupy all of your file with trash. 

Even if you don't need the median or the average, the libraries used are independent enought to help you sort any file with little or no effort. If it is a matrix, you just need to call the external sorting for each line and save it on an extra auxiliar file, then sort it column by column. Using an external version of something like an insertion sort is enough, despite not so fast. 

The high level algorithm is to take the first column, and it's smaller number [j][0], then put [j][1] on the pile and pick the smaller one... and keep taking the next element of the lines you just used, until there are no more elements to be put on the pile.

this was a college project
