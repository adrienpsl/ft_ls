#!/usr/bin/env ./test/libs/bats-core/bin/bats

load 'libs/utils'

@test "hyphen : one -" {
    # setup
    touch file -

    # tests
    command_equal -1
    command_equal -1 -
    command_equal -1 --
    command_equal -1 -- -
}

@test "hyphen : a lot of -" {
###  setup *********************************************************************
    touch - -- ---
###  tests *********************************************************************
    command_equal -1 -- --
    command_equal -1 -- ---
    command_equal -1 -- .
    command_equal -1 -- -- --
    command_equal -1 - - -
    command_equal -1 -- - --
    command_equal -1 -- --- --
}

@test "hyphen : - in file name" {
###  setup *********************************************************************
    mkdir -- -dir --dir ---dir
###  tests *********************************************************************
    command_equal -1 -- -dir
    command_equal -1 -- --dir
    command_equal -1 -- ---dir
}

@test "hyphen : -- stop catching option" {
    # setup
    touch file

    # tests
    run ../../ft_ls -1 -- -a file
    out=$(printf "ls: -a: No such file or directory\nfile")
    assert_output "$out"
}
