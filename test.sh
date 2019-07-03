#!/usr/bin/env bash

OPTIONS='';
FILES='';
ERROR='';
DIFF='';
PATH_TEST_DIR="../test_dir/";
OUR="${PATH_TEST_DIR}our";
YOUR="${PATH_TEST_DIR}your";

# une options pour activer ou non les diffs pcq ca prends vite de la place cette merde !
# faire des titres en petit, ca sert a rien de faire le ouf avec des trucs de malades !
# voila voila ! :).
# demander sur le forum ce que pense les gens sur l'algo de trie de ls

# faire un test de segfault
# faire un test de vitesse
# prendre les test de truc et les applique a mon projet
  # rester simple c'est la clee, le 42filesheker est overkill je trouve, c'est un peu trop lours pour moi

# *------------------------------------*\
#    Functions
# *------------------------------------*/
function testLs()
{
    OPTIONS=$1;
    FILES=$2;
    # the { } catch the result, and I redirect it in error
    ERROR=$( { /bin/ls ${OPTIONS} ${FILES}  > ${OUR} && ./ft_ls ${OPTIONS} / ${FILES} > ${YOUR} ; } 2>&1 )
    DIFF=$(  { diff --brief ${OUR} ${YOUR} ; } 2>&1 )
}

function printRes()
{
    if [[ -n ${ERROR} ]]; then
        echo "$ERROR"
    elif [[ -n ${DIFF} ]]; then
        echo "\r\033[31mError:\t\t\033[0m\033[37;1m" \
             "options :   ${OPTIONS}  ${FILES}  " | tee -a err-log-ls.txt;
	    diff -y ${OUR} ${YOUR} >> err-log-ls.txt;
	else
	   echo "\033[32mtest ok:\t\t\033[0m\033[37;1m ${OPTIONS}  ${FILES}"
    fi
}

# *------------------------------------*\
#    build and create program
# *------------------------------------*/
make > logs
rm -rf ../test_dir 2> logs
mkdir ../test_dir 2> logs
rm err-log-ls.txt 2> logs

# faire le check de nv.
# faire le test de l'usage.
# bien faire le test pour le trie des fichiers !

# *------------------------------------*\
#    test error message
# *------------------------------------*/

# je fais un array pour chaque test
# je donne a cet array les bons tests
# je valide tout ca mon gars ! yeah yeah yeah ! faty fatou !


testLs "-l" "."
printRes




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
#./ft_ls__run -lS /Users/adpusel/Downloads           > me.txt
#ls -lS /Users/adpusel/Downloads                     > ls.txt
#diff me.txt ls.txt
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

#mkdir directory
#ln -s directory dir_link
#touch file

