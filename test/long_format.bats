#!/usr/bin/env ./test/libs/bats/bin/bats

# the first one is mine

load 'libs/utils'

@test "long format : file : one - no argv" {
    touch a
    command_equal -l
}

@test "long format : file : two - no argv" {
    touch a b
    command_equal -l
}

@test "long format : file : three - no argv" {
    touch a b c
    command_equal -l
}

@test "long format : file : one - argv" {
    touch a b c
    command_equal -l b
}

@test "long format : file : two - argv" {
    touch a b c
    command_equal -l a c
}

@test "long format : file : three - argv" {
    touch a b c
    command_equal -l a b c
}

@test "long format : right : 777" {
    touch file
    chmod 777 file
    command_equal -l file
}

@test "long format : right : 000" {
    touch file
    chmod 000 file
    command_equal -l
}

@test "long format : right : mixed" {
    touch file_064 file_474 file_640 file_123 file_420
    chmod 064 file_640
    chmod 474 file_474
    chmod 640 file_640
    chmod 123 file_123
    chmod 420 file_420

    mkdir dir_064 dir_474 dir_640 dir_123 dir_420
    chmod 064 dir_640
    chmod 474 dir_474
    chmod 640 dir_640
    chmod 123 dir_123
    chmod 420 dir_420

    command_equal -l
}

@test "long format : special bits : file :  mixed" {
    touch file1 && chmod 0777 file1
    touch file2 && chmod 1777 file2
    touch file3 && chmod 2777 file3
    touch file4 && chmod 3777 file4
    touch file5 && chmod 4777 file5
    touch file6 && chmod 5777 file6
    touch file7 && chmod 6777 file7
    touch file8 && chmod 7777 file8
    touch file9 && chmod 0000 file9
    touch file10 && chmod 1000 file10
    touch file11 && chmod 2000 file11
    touch file12 && chmod 3000 file12
    touch file13 && chmod 4000 file13
    touch file14 && chmod 5000 file14
    touch file15 && chmod 6000 file15
    touch file16 && chmod 7000 file16

    command_equal -l
}

@test "long format : special bits : directory : mixed" {
    mkdir  dir1 && chmod 0777 dir1
    mkdir  dir2 && chmod 1777 dir2
    mkdir  dir3 && chmod 2777 dir3
    mkdir  dir4 && chmod 3777 dir4
    mkdir  dir5 && chmod 4777 dir5
    mkdir  dir6 && chmod 5777 dir6
    mkdir  dir7 && chmod 6777 dir7
    mkdir  dir9 && chmod 0000 dir9
    mkdir  dir9 && chmod 0000 dir9
    mkdir  dir10 && chmod 1000 dir10
    mkdir  dir11 && chmod 2000 dir11
    mkdir  dir12 && chmod 3000 dir12
    mkdir  dir13 && chmod 4000 dir13
    mkdir  dir14 && chmod 5000 dir14
    mkdir  dir15 && chmod 6000 dir15
    mkdir  dir16 && chmod 7000 dir16

    command_equal -l
}

