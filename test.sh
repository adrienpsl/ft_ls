#!/usr/bin/env bash

# *------------------------------------*\
#    bug
# *------------------------------------*/
# -- at /, the symlink witch link to private.. no working.

# *------------------------------------*\
#    Script Option
# *------------------------------------*/
declare showDiff=1;
declare showOk=0;
declare showTitle=0;

# *------------------------------------*\
#    Variables use in that script
# *------------------------------------*/
declare     TITLE;
declare -a  ARRAY;
declare -a  COMMANDS;
declare     OPTIONS;
declare     FILES;

declare     ERROR;
declare     DIFF;

declare     PATH_TEST_DIR="../cmp_dir";
declare     PATH_WORKING="working_dir"
declare     OUR="${PATH_TEST_DIR}/our";
declare     YOUR="${PATH_TEST_DIR}/your";

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
    ERROR=$( {  /bin/ls ${OPTIONS} ${FILES}  > ${OUR} \
                && ${PATH_WORKING}/ft_ls ${OPTIONS} ${FILES} > ${YOUR} ; } 2>&1 )
    # brief test file, without print the diff
    DIFF=$(  { diff --brief ${OUR} ${YOUR} ; } 2>&1 )
}

function printRes()
{
    if [[ -n ${ERROR} ]]; then
        echo  "\033[31mNo test the current error append:\033[37;1m \n$ERROR ---------- \033[0m"
    elif [[ -n ${DIFF} ]]; then
        # tee write the data in the file ( append mode ), and show there in the console, \
        # 1i / 2o like -|- a T connector :)
        echo "\r\033[31mTest ko  : ${OPTIONS} ${FILES}\033[0m"  | tee -a err-log-ls.txt;
	   [[ ${showDiff} -gt 0 ]]  && diff -y ${OUR} ${YOUR} | colordiff >> err-log-ls.txt; # you need to install that with brew ( in mac os )
	else
	   [[ ${showOk} -gt 0 ]] && echo "\033[32mTest ok  : ${OPTIONS} ${FILES} \033[0m"
    fi
}

function printTitle()
{
    echo "# *------------------------------------* "
    echo "   $TITLE"
    echo "# *------------------------------------* "
}

function parseAndDo()
{
     [[ ${showTitle} -gt 0 ]] && printTitle;

    for command in "${COMMANDS[@]}"
    do
        # split the line and reset the original IFS
        ORIGINAL_IFS=${IFS}
        IFS='~'
        read -r -a argv <<< ${command};
        IFS=${ORIGINAL_IFS}

        OPTIONS=${argv[0]}
        FILES=${argv[1]}

        testLs;
        printRes;
    done
    echo
}


# if -l, the symlink is treat like a file.

# *------------------------------------*\
#    build and create program
# *------------------------------------*/
chmod   -R 777          ${PATH_WORKING}  > /dev/null
rm      -rf             ${PATH_WORKING}
mkdir                   ${PATH_WORKING}
make                                      > /dev/null
mv ./ft_ls              ${PATH_WORKING}

rm      -rf             ${PATH_TEST_DIR}  > /dev/null
mkdir                   ${PATH_TEST_DIR}  > /dev/null
rm -f  err-log-ls.txt
echo

# faire le check de nv.
# faire le test de l'usage.
# bien faire le test pour le trie des fichiers !

# *------------------------------------*\
#    test Error Handling
# *------------------------------------*/
TITLE="Error Handling"
COMMANDS=(
    "-l ~ /Users/adpusel  ~ " # ici je fais un truc pour set up l'env de test ?
    "-l ~ . ."
    "-l ~   "
    "-l ~ /"
)
parseAndDo






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

