#!/usr/bin/env

# *------------------------------------*\
#    bug
# *------------------------------------*/
# -- at /, the symlink witch link to private.. no working.

# *------------------------------------*\
#    Script Option
# *------------------------------------*/
declare showDiff=1;
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
#    echo ${SETUP}
    cd ${TEST_DIR} ; eval ${SETUP}
    # do test
    ERROR=$( {      /bin/ls -1 ${COMMAND}  > ../${LS_LOG} \
                &&  ./ft_ls ${COMMAND}  > ../${YOUR_LOG} ; } \
                2>&1 )
    cd ..;

    DIFF=$(  { diff --brief ${LS_LOG} ${YOUR_LOG} ; } 2>&1 )

    if [[ -n ${ERROR} ]]; then
        echo  "\033[31mError: \033[37;1m $ERROR \033[0m"

    elif [[ -n ${DIFF} ]]; then

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
#
#
## *------------------------------------*\
##    No Option
## *------------------------------------*/
#TITLE="No Option"
#
#parseAndDo  "-1" "touch aaa bbb ccc"
#parseAndDo  "-1" "touch - file"
#parseAndDo  "-1 -- - dir" "mkdir - dir"
#echo
#
#
#
## *------------------------------------*\
##    Option R
## *------------------------------------*/
#TITLE="Option R"
#
#parseAndDo  "-1R" "mkdir -p level1_{1..2}/level2_{1..2}/level3_{1..2}"
#parseAndDo  "-1R" "mkdir -p level1_{1..3}/level2_{6..8}/level3_{11..13}"
#parseAndDo  "-1R" "mkdir -p .a .b .c && mkdir -p a b c"
#parseAndDo  "-1R A a" "mkdir A && touch A/file"
#parseAndDo  "-1R A a rootFile rootFile" "mkdir A && touch A/file rootFile"
#echo
#
## *------------------------------------*\
##    Sorted Directory
## *------------------------------------*/
#TITLE="Sorted Directory"
#parseAndDo "-1" "touch a b c AA BB CC"
#parseAndDo "-1" "mkdir -p a b c AA BB CC"
#parseAndDo "-1" "mkdir -p da db dc dAA dBB dCC && touch fa fb fc fAA fBB fCC"
#echo
#
## *------------------------------------*\
##    Multiple Dir
## *------------------------------------*/
#TITLE="Multiple Dir"
#parseAndDo "-1 mydir mydir2" "mkdir mydir mydir2 && touch mydir/{aaa,bbb,ccc} && touch mydir2/{111,222,333}"
#parseAndDo "-1 mydir mydir2" "mkdir mydir mydir2 && touch mydir/file{10..20} && touch mydir2/file{30..40}"
#tmp=`echo mydir{1..7}`
#parseAndDo "-1 $tmp" "mkdir mydir{1..7} && touch mydir{1..7}/file{1..11}"
#parseAndDo "-1 mydir" "mkdir mydir && touch mydir/a"
#parseAndDo "-1 ./mydir" "mkdir ./mydir && touch ./mydir/{a,b,c}"
#echo
#
## *------------------------------------*\
##    Option a
## *------------------------------------*/
#TITLE="Option a"
#parseAndDo "-1a" "mkdir .a a"
#parseAndDo "-1a" "mkdir .hiddendir{1..10} dir{1..10} && touch .hiddenfile{1..10} file{1..10}"
#echo
#
## *------------------------------------*\
##    Option r
## *------------------------------------*/
#TITLE="Option a"
#parseAndDo "-1r" "touch a b c AA BB CC"
#parseAndDo "-1r" "mkdir -p a b c AA BB CC"
#parseAndDo "-1r" "mkdir -p POP mok POPO liu && touch PIP mik PIPI lui"
#echo
#
## *------------------------------------*\
##    Option rR
## *------------------------------------*/
#TITLE="Option rR"
#parseAndDo "-1rR" "mkdir -p level1_{1..2}/level2_{1..2}"
#parseAndDo "-1rR" "mkdir -p level1_{1..2}/level2_{1..2}/level3_{1..2}"
#parseAndDo "-1rR" "mkdir -p level1_{1..3}/level2_{6..8}/level3_{11..13}"
#parseAndDo "-1rR" "mkdir -p .a .b .c && mkdir -p a b c "
#echo
#
## *------------------------------------*\
##    Option t
## *------------------------------------*/
## HFS Plus Dates  ** https://developer.apple.com/library/archive/technotes/tn/tn1150.html#HFSPlusDates
## HFS Plus stores dates in several data structures,
## including the volume header and catalog records.
## These dates are stored in unsigned 32-bit integers (UInt32) containing the number of seconds since midnight,
## January 1, 1904, GMT. This is slightly different from HFS, where the value represents local time.
## so, It's the sort it's up to you how class the same timestamp...
#TITLE="Option t"
#parseAndDo "-1t" "touch -t 201312101830.55 a ; touch -t 201312101831.55 b ; touch -t 201312101831 c ; touch -t 201312101820 d ; touch e ; touch -t 201212101830.55 e"
#parseAndDo "-1t" "touch -t 201312101830.55 a && touch -t 201212101830.55 b && touch -t 201412101830.55 c"
#parseAndDo "-1t" "touch -t 201312101830.55 a && touch -t 201212101830.55 b && touch -t 201412101830.55 c && touch -t 201411221830.55 d && touch -t 201405212033.55 e && touch -t 201409221830.55 f && touch -t 202007221830.55 g && touch -t 300012101830.55 h &&
#                  mkdir toto ; sleep 1;  mkdir tata; sleep 1; mkdir titi; sleep 1; touch ft_ls"
#parseAndDo "-1t" "touch -t 200012101830.55 a; touch -t 201412101830.55 b; ln b d;  sleep 1; ln -s c e; sleep 1; ln -s a f; touch -t 300012101830.55 c"
#parseAndDo "-1t" "touch -t 201312101830.55 B ; touch -t 201312101830.55 a"
#parseAndDo "-1tlT" "touch C ; touch -t 201212101830.55 c ; mkdir sbox ; sleep 1; mkdir sbox1; touch -t 201312101830.55 B; touch -t 201312101830.55 a; sleep 1; touch ft_ls"
#parseAndDo "-1tlT" "mkdir -p sbox/level1_{1..2}/level2_{1..2}/level3_{1..2} ; mkdir -p sbox1/level1_{1..2}/level2_{1..2}/level3_{1..2} ; mkdir -p sbox/level1_1 sbox/level1_1/level2_1 ; touch -t 201212101830.55 sbox/c_lvl1 ; touch -t 201212101830.55 sbox/level1_1/c_lvl2 ; touch -t 201212101830.55 sbox/level1_1/level2_1/c_lvl3; sleep 1; touch ft_ls"
#echo
#
## *------------------------------------*\
##    Option aRl / aR / l
## *------------------------------------*/
#parseAndDo "-lRa" "mkdir .hdir"
#parseAndDo "-1aR" ""
#parseAndDo "-1aR" "mkdir aRdir1 .aRhdir1 ; touch .aRhdir1/file1 .aRhdir1/.hfile1"
## *------------------------------------*\
##    option l
## *------------------------------------*/
#parseAndDo "-l" "touch a b c"
#parseAndDo "-l" "touch a b c && echo 'coucou' > a &&  echo 'hello world' > b"
#parseAndDo "-l" "touch a b c && echo 'coucou' > a &&  echo 'hello world' > b; mkdir 111 222 333 444 && touch 111/{a,b,c} && echo 'eat pizza' > 111/a"
#parseAndDo "-l" "touch .a ; dd bs=2 count=14450 if=/dev/random of=.a  >/dev/null 2>&1 ; ln -s .a b"
#parseAndDo "-la dir" "mkdir -p dir/.hdir ; touch dir/.hdir/file"
#parseAndDo "-la dir" "mkdir -p dir; touch dir/.file touch dir/visible  ; ln dir/.file sym0 ; ln dir/.file sym1 ; ln dir/.file sym2 ; ln dir/.file sym3 ; ln dir/.file sym4 ; ln dir/.file sym5 ; ln dir/.file sym6 ; ln dir/.file sym7 ; ln dir/.file sym8 ; ln dir/.file sym9 ; ln dir/.file sym10"
#parseAndDo "-lt" "touch -t 999912312459 future"
#parseAndDo "-l aaa" "touch aaa"
#
## *------------------------------------*\
##    permission
## *------------------------------------*/
#parseAndDo "-l" "touch a b c ; chmod 644 a ; chmod 755 b ; chmod 311 c"
#parseAndDo "-l" "mkdir a b c ; chmod 644 a ; chmod 755 b ; chmod 311 c"
#
## *------------------------------------*\
##    hyphen
## *------------------------------------*/
#parseAndDo "-1" "touch - file"
#parseAndDo "-1 -" "touch - file"
#parseAndDo "-1 --" "touch - file"
#parseAndDo "-1 -- -" "touch - file"
#parseAndDo "-1 -- --" "touch - -- ---"
#parseAndDo "-1 -- ---" "touch - -- ---"
#parseAndDo "-1 -- ." "touch - -- ---"
#parseAndDo "-1 -- -file" "mkdir -- -file --file ---file"
#parseAndDo "-1 -- -file" "mkdir -- -file --file ---file"
#parseAndDo "-1 -- --file" "mkdir -- -file --file ---file"
#parseAndDo "-1 -- ---file" "mkdir -- -file --file ---file"
#parseAndDo "-1" "mkdir -"
#parseAndDo "-1 -" "mkdir -"
#parseAndDo "-1 -- -" "mkdir -"
#parseAndDo "-1 -- --" "mkdir - -- ---"
#parseAndDo "-1 -- ---" "mkdir - -- ---"
#parseAndDo "-1 -- ." "mkdir - -- ---"
#parseAndDo "-1 -- -dir" "mkdir -- -dir --dir ---dir"
#parseAndDo "-1 -- --dir" "mkdir -- -dir --dir ---dir"
#parseAndDo "-1 -- ---dir" "mkdir -- -dir --dir ---dir"
#parseAndDo "-1 -- -- --" "touch -- - -- ---"
#parseAndDo "-1 - - -" "touch -- - -- ---"
#parseAndDo "-1 -- - -- ---" "touch -- - -- ---"
#parseAndDo "-1 - -- ---" "touch -- - -- ---"
#parseAndDo "-1 -- - ---" "touch -- - -- ---"
#parseAndDo "-1 -- -- --" "mkdir -- - -- ---"
#parseAndDo "-1 - - -" "mkdir -- - -- ---"
#parseAndDo "-1 -- - -- ---" "mkdir -- - -- ---"
#parseAndDo "-1 - -- ---" "mkdir -- - -- ---"
#parseAndDo "-1 -- - ---" "mkdir -- - -- ---"
#
## *------------------------------------*\
##    test username
## *------------------------------------*/
#parseAndDo "-l /usr/local/bin/node" ""
#parseAndDo "-l /usr/share/doc" ""
#
## *------------------------------------*\
##    test special bit
## *------------------------------------*/
#parseAndDo "-l" "mkdir  dir1 && chmod 0777 dir1"
#parseAndDo "-l" "mkdir  dir2 && chmod 1777 dir2"
#parseAndDo "-l" "mkdir  dir3 && chmod 2777 dir3"
#parseAndDo "-l" "mkdir  dir4 && chmod 3777 dir4"
#parseAndDo "-l" "mkdir  dir5 && chmod 4777 dir5"
#parseAndDo "-l" "mkdir  dir6 && chmod 5777 dir6"
#parseAndDo "-l" "mkdir  dir7 && chmod 6777 dir7"
#parseAndDo "-l" "mkdir  dir9 && chmod 0000 dir9"
#parseAndDo "-l" "mkdir  dir9 && chmod 0000 dir9"
#parseAndDo "-l" "mkdir  dir10 && chmod 1000 dir10"
#parseAndDo "-l" "mkdir  dir11 && chmod 2000 dir11"
#parseAndDo "-l" "mkdir  dir12 && chmod 3000 dir12"
#parseAndDo "-l" "mkdir  dir13 && chmod 4000 dir13"
#parseAndDo "-l" "mkdir  dir14 && chmod 5000 dir14"
#parseAndDo "-l" "mkdir  dir15 && chmod 6000 dir15"
#parseAndDo "-l" "mkdir  dir16 && chmod 7000 dir16"
#
## *------------------------------------*\
##    multiple files
## *------------------------------------*/
#parseAndDo "-1 . ." ""
#parseAndDo "-1 ./ ." "touch a b C D"
#parseAndDo "-1 z b a c d f e" "touch a c z ; mkdir b d ; ln -s a e && ln -s a f"
#parseAndDo "-lR ." "mkdir dir{1..5} .hdir{1..5} ; touch dir1/file{1..5} dir1/.hfile{1..5} ; touch .hdir1/file{1..5} .hdir1/.hfile{1..5} ; touch .hdir1/file{1..5} .hdir1/.hfile{1..5} ; touch a && ln -s a symlink"
#
## *------------------------------------*\
##    symlinc
## *------------------------------------*/
#parseAndDo "-1 symdir" "mkdir mydir && ln -s mydir symdir && touch mydir/file{1..5}"
#parseAndDo "-1 b" "touch a ; ln -s a b"
#parseAndDo "-1 b" "mkdir a ; ln -s a b ; rm -rf a"






# *------------------------------------*\
#    Bonus
# *------------------------------------*/
## option -u // last acces
#parseAndDo "-lu /usr"

## option c status change
#parseAndDo "-1tlc /usr/share"
#parseAndDo "-1tlr /usr/share"

## option n = les guid in number
#parseAndDo "-ln /usr"