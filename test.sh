#!/usr/bin/env bash

## *------------------------------------*\
##   test with no col
## *------------------------------------*/
#./ft_ls__run -1 /Users/adpusel          > me.txt
#ls -1 /Users/adpusel                    > ls.txt
#diff me.txt ls.txt
#
## *------------------------------------*\
##    test with long format
## *------------------------------------*/
#./ft_ls__run -l /Users/adpusel          > me.txt
#ls -l /Users/adpusel                    > ls.txt
#diff me.txt ls.txt

## *------------------------------------*\
##    test with -R
## *------------------------------------*/
#time ./ft_ls__run -1R /Users/adpusel          > me.txt
#time ls -1R /Users/adpusel                    > ls.txt
#diff me.txt ls.txt


## *------------------------------------*\
##    test with -test
## *------------------------------------*/
#./ft_ls__run -l /Users/adpusel/Downloads          > me.txt
#ls -l /Users/adpusel/Downloads                    > ls.txt
#diff me.txt ls.txt

## *------------------------------------*\
##    test with /dev driver
## *------------------------------------*/
#./ft_ls__run -l /dev         > me.txt
#ls -l /dev                    > ls.txt
#diff me.txt ls.txt


## *------------------------------------*\
##    test with /var/run socket
## *------------------------------------*/
#./ft_ls__run -l /var/run          > me.txt
#ls -l /var/run                    > ls.txt
#diff me.txt ls.txt


## *------------------------------------*\
##    test with -t
## *------------------------------------*/
#./ft_ls__run -lt /Users/adpusel/Downloads          > me.txt
#ls -lt /Users/adpusel/Downloads                    > ls.txt
#diff me.txt ls.txt
#
#
## *------------------------------------*\
##    test with -rt
## *------------------------------------*/
#./ft_ls__run -lrt /Users/adpusel/Downloads          > me.txt
#ls -lrt /Users/adpusel/Downloads                    > ls.txt
#diff me.txt ls.txt

# *------------------------------------*\
#    test with -S
#    here to diff is same size between file.
# *------------------------------------*/
./ft_ls__run -lS /Users/adpusel/Downloads           > me.txt
ls -lS /Users/adpusel/Downloads                     > ls.txt
diff me.txt ls.txt
#
#./ft_ls__run -lrS /Users/adpusel/Downloads           > me.txt
#ls -lrS /Users/adpusel/Downloads                     > ls.txt
#diff me.txt ls.txt
#
#./ft_ls__run -1rS /Users/adpusel/Downloads           > me.txt
#ls -1rS /Users/adpusel/Downloads                     > ls.txt
#diff me.txt ls.txt

#./ft_ls__run -1S /Users/adpusel/Downloads           > me.txt
#ls -1S /Users/adpusel/Downloads                     > ls.txt
#diff me.txt ls.txt


# *------------------------------------*\
#    test_file_type
# *------------------------------------*/

mkdir directory
ln -s directory dir_link
touch file

