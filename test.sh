#!/usr/bin/env bash

# *------------------------------------*\
#    bug
# *------------------------------------*/
# -- at /, the symlink witch link to private.. no working.

# *------------------------------------*\
#    Script Option
# *------------------------------------*/
declare showDiff=1;
declare showOk=1;
declare showTitle=0;

# *------------------------------------*\
#    Variables use in that script
# *------------------------------------*/
declare     TITLE;
declare     COMMANDS;
declare     COMMAND;

declare     ERROR;
declare     DIFF;

declare     PATH_DIR="ft-ls-test";
declare     PATH_LOG="ft-ls-log";

declare     LS_LOG="${PATH_LOG}/our";
declare     YOUR_LOG="${PATH_LOG}/your";

function resetWorkingDir()
{
    # je reset le directory
    chmod   -R 777 ${PATH_DIR} && rm -rf ${PATH_DIR} && mkdir ${PATH_DIR}
    # je met ls dedans
    make  > /dev/null && cp ./ft_ls ${PATH_DIR}
    echo
}

# *------------------------------------*\
#    build and create program
# *------------------------------------*/
# je reset les logs
rm -rf  ${PATH_LOG} && mkdir ${PATH_LOG}
resetWorkingDir

# *------------------------------------*\
#    Functions
# *------------------------------------*/

function testLs()
{
    # make set up
    cd ${PATH_DIR} ; ${SETUP}

    # do test
    ERROR=$( {  /bin/ls              ${COMMAND}  > ../${LS_LOG} \
                && ./ft_ls ${COMMAND}  > ../${YOUR_LOG} ; } \
                2>&1 )

    cd ..;

    DIFF=$(  { diff --brief ${LS_LOG} ${YOUR_LOG} ; } 2>&1 )

    if [[ -n ${ERROR} ]]; then
        echo  "\033[31mNo test the current error append:\033[37;1m $ERROR \033[0m"
    elif [[ -n ${DIFF} ]]; then
        echo "\r\033[31mTest ko  : ${COMMAND}\033[0m"  | tee -a ${PATH_LOG}/err-log.txt;
        [[ ${showDiff} -gt 0 ]]  && diff -y ${LS_LOG} ${YOUR_LOG} | colordiff >> ${PATH_LOG}/err-log-ls.txt; # you need to install that with brew ( in mac os )
        diff -y ${LS_LOG} ${YOUR_LOG} | colordiff
    else
        [[ ${showOk} -gt 0 ]] && echo "\033[32mTest ok  : ${COMMAND} \033[0m"
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

    COMMAND=$1
    SETUP=$2

#    echo "$COMMAND $SETUP"
    testLs;
    echo
}


# if -l, the symlink is treat like a file.


# faire le check de nv.
# faire le test de l'usage.
# bien faire le test pour le trie des fichiers !

# *------------------------------------*\
#    test Error Handling
# *------------------------------------*/
TITLE="Error Handling"

parseAndDo  "-l . ." "mkdir oo"