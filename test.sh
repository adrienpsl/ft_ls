#!/usr/bin/env

# *------------------------------------*\
#    bug
# *------------------------------------*/
# -- at /, the symlink witch link to private.. no working.

# *------------------------------------*\
#    Script Option
# *------------------------------------*/
declare showDiff=0;
declare showOk=1;
declare showKo=1;
declare showTitle=0;

# *------------------------------------*\
#    Variables use in that script
# *------------------------------------*/
declare     TITLE;
declare     COMMANDS;
declare     COMMAND;

declare     ERROR;
declare     DIFF;

declare     TEST_DIR="ft-ls-test";
declare     PATH_LOG="ft-ls-log";

declare     LS_LOG="${PATH_LOG}/our";
declare     YOUR_LOG="${PATH_LOG}/your";

# *------------------------------------*\
#    Functions
# *------------------------------------*/

function resetWorkingDir()
{
    # je reset le directory
    chmod -R 777 ${TEST_DIR} && rm -rf ${TEST_DIR} && mkdir ${TEST_DIR}
    # je met ls dedans
    make  > /dev/null && cp ./ft_ls ${TEST_DIR}
}

function printTitle()
{
    echo "# *------------------------------------* "
    echo "   $TITLE"
    echo "# *------------------------------------* "
}

function testLs()
{
    cd ${TEST_DIR} ; eval ${SETUP}
    # do test
    ERROR=$( {      /bin/ls -1 ${COMMAND}  > ../${LS_LOG} \
                &&  ./ft_ls ${COMMAND}  > ../${YOUR_LOG} ; } \
                2>&1 )
    cd ..;

    DIFF=$(  { diff --brief ${LS_LOG} ${YOUR_LOG} ; } 2>&1 )

#    if [[ -n ${ERROR} ]]; then
#        echo  "\033[31mNo test /the current error append:\033[37;1m $ERROR \033[0m"

    if [[ -n ${DIFF} ]]; then

        echo "Test ko  : ${COMMAND}"  >>  ${PATH_LOG}/err-log.txt;
        diff -y ${LS_LOG} ${YOUR_LOG} >>  ${PATH_LOG}/err-log-ls.txt;

        [[ ${showKo} -gt 0 ]] && echo "\r\033[31mTest ko  : ${COMMAND}\033[0m"
        [[ ${showDiff} -gt 0 ]] && diff -y ${LS_LOG} ${YOUR_LOG} | colordiff

    else
        [[ ${showOk} -gt 0 ]] && echo "\033[32mTest ok  : ${COMMAND} \033[0m"

    fi
}

function parseAndDo()
{
    [[ ${showTitle} -gt 0 ]] && printTitle;

    COMMAND=$1
    SETUP=$2

    [[ ${showTitle} -gt 0 ]] && printTitle;
    resetWorkingDir;
    testLs;
}

# if -l, the symlink is treat like a file.

# faire le check de nv.
# faire le test de l'usage.
# bien faire le test pour le trie des fichiers !

# je reset les logs
rm -rf  ${PATH_LOG} && mkdir ${PATH_LOG}

## *------------------------------------*\
##    test Error Handling
## *------------------------------------*/
#TITLE="Error Handling"
#
#parseAndDo  "-l . ." "mkdir oo"
#parseAndDo  "-1R 2>&1 | grep -v denied" "mkdir a b c ; chmod 000 b"
# test file too big


# *------------------------------------*\
#    No Option
# *------------------------------------*/
TITLE="No Option"

parseAndDo  "-1" "touch aaa bbb ccc"
parseAndDo  "-1" "touch - file"
parseAndDo  "-1 -- - dir" "mkdir - dir"

echo



# *------------------------------------*\
#    No Option
# *------------------------------------*/
TITLE="Option R"

parseAndDo  "-1R" "mkdir -p level1_{1..2}/level2_{1..2}/level3_{1..2}"
parseAndDo  "-1R" "mkdir -p level1_{1..3}/level2_{6..8}/level3_{11..13}"
parseAndDo  "-1R" "mkdir -p .a .b .c && mkdir -p a b c"
parseAndDo  "-1R A a" "mkdir A && touch A/file"
parseAndDo  "-1R A a rootFile rootFile" "mkdir A && touch A/file rootFile"

echo