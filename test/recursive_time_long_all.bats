#!/usr/bin/env ./test/libs/bats/bin/bats

# ------------------------------------------------------------------------------
#    load all the good stuff
# ------------------------------------------------------------------------------
load 'libs/utils'
#
#@test "Recursive test: one level : one directory" {
#    generate_one_dir "dir"
#    do_all_test
#    do_all_test_with_argv "dir"
#}
#
#@test "Recursive test: one level : two directory" {
#    generate_one_dir "dir_1"
#    sleep 1
#    generate_one_dir "dir_2"
#
#    do_all_test
#    do_all_test_with_argv "dir_1" "dir_2"
#}
#
#@test "Recursive test: one level : six directory" {
#    generate_one_dir "dir_1"
#    sleep 1
#    generate_one_dir "dir_2"
#    sleep 1
#    generate_one_dir "Dir_3"
#    sleep 1
#    generate_one_dir ".dir_4"
#    sleep 1
#    generate_one_dir ".Dir_5"
#    sleep 1
#    generate_one_dir ".dir_6"
#
#    do_all_test
#    do_all_test_with_argv "dir_1" "dir_2" "Dir_3" ".dir_4" ".Dir_5" ".dir_6"
#}

#@test "Recursive test: one level : directories && files" {
#
#    generate_one_dir "."
#    generate_one_dir "dir_1"
#
#    do_all_test
#}

#@test "recursive | no argv : two level : directories && files" {
#
#    generate_one_dir "."
#    sleep 1
#
#    generate_one_dir "dir_1/dir_1_1"
#    sleep 1
#    generate_one_dir "dir_1/dir_1_2"
#    sleep 1
#    generate_one_dir "dir_1/dir_1_3"
#    sleep 1
#    touch "dir_1"
#
#    generate_one_dir "dir_2/dir_2_1"
#    sleep 1
#    generate_one_dir "dir_2/dir_2_2"
#    sleep 1
#    generate_one_dir "dir_2/dir_2_3"
#    sleep 1
#    touch "dir_2"
#
#    sleep 1
#    touch ".."
#
#    sleep 1
#    touch "."
#
#    do_all_test
#}

@test "recursive | argv : multi level : directories && files" {

    generate_one_dir "."
    sleep 1

    generate_one_dir "dir_1/dir_1_1"
    sleep 1
    generate_one_dir "dir_1/dir_1_2"
    sleep 1
    generate_one_dir "dir_1/dir_1_3"
    sleep 1
    touch "dir_1"

    generate_one_dir "dir_2/dir_2_1"
    sleep 1
    generate_one_dir "dir_2/dir_2_2"
    sleep 1
    generate_one_dir "dir_2/dir_2_3"
    sleep 1
    generate_one_dir "dir_2/dir_2_3/dir_2_3_1"
    sleep 1
    generate_one_dir "dir_2/dir_2_3/dir_2_3_1/dir_2_3_1_4"
    sleep 1
    touch "dir_2/dir_2_3/dir_2_3_1"
    sleep 1
    generate_one_dir ".Dir_5"
    sleep 1
    generate_one_dir "ir_5"
    sleep 1
    generate_one_dir "1ir_5"

    sleep 1
    ln -s dir_2/dir_2_3 link_dir
    sleep 1
    ln -s .Dir_5/File_1 link_file

    sleep 1
    touch "dir_2"

    sleep 1
    touch ".."

    sleep 1
    touch "."

    do_all_test_with_argv -- -.file_2 File_1 File_2 .File_1 file_1 "dir_1/dir_1_1" "dir_2/dir_2_1" "." "dir_2/dir_2_3/dir_2_3_1" ".Dir_5"
}


