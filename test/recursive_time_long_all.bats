#!/usr/bin/env ./test/libs/bats/bin/bats

# ------------------------------------------------------------------------------
#    load all the good stuff
# ------------------------------------------------------------------------------
load 'libs/utils'

function generate_one_dir() {
    mkdir "$1"

    sleep 1
    touch "$1"/file_1
    touch "$1"/file_2
    sleep 1

    touch "$1"/File_1
    sleep 1
    touch "$1"/File_2
    sleep 1

    touch "$1"/.File_1
    sleep 1
    touch "$1"/file_2
    sleep 1

    touch "$1"/.-File_1
    sleep 1
    touch "$1"/-a
    sleep 1
    touch "$1"/-.file_2
    sleep 1

    echo asohusaoehaoeuaoeuaoeuaoe > "$1"/file_1
    sleep 1
    echo asohusaoeh > "$1"/File_2
    sleep 1
    touch "$1"
}

function do_all_test() {
    command_equal -1R

    command_equal -Rl
    command_equal -1Ra
    command_equal -1Rt
    command_equal -1Rr

    command_equal -Rla
    command_equal -Rlt
    command_equal -Rlr

    command_equal -Rlta
    command_equal -Rltar
    command_equal -Rltr
    command_equal -R -l -t -r
}

function do_all_test_with_argv()  {
    command_equal -1R "$@"

    command_equal -Rl "$@"
    command_equal -1Ra "$@"
    command_equal -1Rt "$@"
    command_equal -1Rr "$@"

    command_equal -Rla "$@"
    command_equal -Rlt "$@"
    command_equal -Rlr "$@"

    command_equal -Rlta "$@"
    command_equal -Rltar "$@"
    command_equal -Rltr "$@"
    command_equal -R -l -t -r "$@"
}

#
#@test "Recursive test: one directory" {
#
#    generate_one_dir "dir"
#    do_all_test
#    do_all_test_with_argv "dir"
#}
#
#@test "No agrv : two directory" {
#
#    generate_one_dir "dir_1"
#    sleep 1
#    generate_one_dir "dir_2"
#
#    do_all_test
#    do_all_test_with_argv "dir_1" "dir_2"
#}

@test "No agrv : six directory" {

    generate_one_dir "dir_1"
    sleep 1
    generate_one_dir "dir_2"
    sleep 1
    generate_one_dir "Dir_3"
    sleep 1
    generate_one_dir ".dir_4"
    sleep 1
    generate_one_dir ".Dir_5"
    sleep 1
    generate_one_dir ".dir_6"

    do_all_test
    do_all_test_with_argv "dir_1" "dir_2" "Dir_3" ".dir_4" ".Dir_5" ".dir_6"
}

@test "recursive | no argv : one level : directories && files" {
    touch file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua
    mkdir dir_1 DIR_2 .hiden
    touch dir_1/file_a{1..50}
    touch DIR_2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch .hiden/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    command_equal -1R
}

@test "recursive | no argv : two level : directories && files" {
    touch fil_{0..2} asouh oseuh oaeu upm aoeue aoe .aeoua .aoa

    mkdir -p dir_1 DIR_2/-1 .hiden
    touch dir_1/file_a{1..50}
    touch DIR_2/file_{1..50}
    touch DIR_2/-1/file_{1..50}
    touch .hiden/file_{1..50}

    command_equal -1R
}

#function creation_dir() {
#    # file creation
#    touch -- --- - asouh oseuh oaeu upm aoeue aoe .aeoua -a -b -c .-- .tat
#    touch  -t 204201010101 file_1
#    touch  -t 204201010104 file_2
#    touch  -t 200001010104 Faa
#    touch  -t 203001010104 Fo
#    touch  -t 200101010104 Fi
#    touch  -t 200201010104 .Fi
#
#    # dir creation and filling
#    mkdir -p dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#    touch dir_1/file_a{1..5}
#    sleep 1
#    echo "auaoeuaoeuoeueau aoeuoaesuhaoeuhoaeuaoeuaoeuaoeu aoeuaoeu" > dir_1/file_a1
#    echo "auaoeuaoeuoooeueau aoeuoaesuhaoeuhoaeuaoeu" > dir_1/file_a3
#    echo "auaoeuaoeuo" > dir_1/file_a4
#    touch dir_1/file_b{1..5}
#    sleep 1
#    touch dir_1/.file_a{1..5}
#    sleep 1
#    touch DIR_2/file_{1..5}
#    sleep 3
#    echo auaoeuaoeuoeueau aoeuoaesuhaoeuhoaeuaoeu > DIR_2/file_1
#    echo auaoeuaoeuoeueau aoeuoaesuhaoeuhoaeuaoeu > DIR_2/file_2
#    sleep 1
#
#    touch DIR_1/-1/file_{1..5}
#    sleep 1
#    touch DIR_2/-1/file_{1..5}
#    sleep 1
#
#    touch DIR_1/-1/-2/file_{1..5}
#    sleep 1
#    touch DIR_2/-1/-2/file_{1..5}
#    sleep 1
#
#    touch DIR_1/-1/-2/-3/file_{1..5}
#    sleep 1
#    echo auaoeuaoeuoeueau aoeuoaesuhaoeuhoaeuaoeu > DIR_1/-1/-2/-3/file_1
#    echo auaoeuaoeuoeueau aoeuoaesuhaoeuhoaeua aoeu aoeuao aoeu aoeuaoe uaoeuaoeu oeu > DIR_1/-1/-2/-3/file_5
#    echo auaoeuao > DIR_1/-1/-2/-3/file_4
#    sleep 1
#    touch DIR_2/-1/-2/-3/file_{1..5}
#    sleep 1
#
#    touch .hiden/file_{1..5}
#    touch .hiden/file_R{1..5}
#    touch .hiden/.file_R{1..5}
#    touch .hiden/.aeouaoeusssfile_R{1..5}
#    sleep 1
#}
#
#@test "-R         : multi level : directories && files" {
#    creation_dir
#    command_equal -1R
#}
#
#@test "-Rl        : multi argv  : directories && files" {
#    creation_dir
#    command_equal -Rl file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#}
#
#@test "recursive, long format, reverse | argv : multi argv : directories && files" {
#    creation_dir
#    command_equal -lrR file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#}
#
#@test "recursive, long format, reverse, time | argv : multi argv : directories && files" {
#    creation_dir
#    command_equal -lrR file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#}
#
#@test "recursive, long format, reverse, time, all | argv : multi argv : directories && files" {
#    creation_dir
#    command_equal -lrRa file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#}
#
#@test "recursive, long format, reverse, time, all | argv : multi argv : directories && files" {
#    creation_dir
#    command_equal -l -r -R -a file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#}
#
#@test "recursive, long format, time, all | argv : multi argv : directories && files" {
#    creation_dir
#    command_equal -l  -R -a file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
#}
#
