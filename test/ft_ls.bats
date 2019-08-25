#!/usr/bin/env ./test/libs/bats/bin/bats
load 'libs/bats-support/load'
load 'libs/bats-assert/load'


ls=;
ft_ls=;

function setup() {
  cp        "../cmake-build-debug/ft_ls" "."
  mkdir -p  "test_container/test_dir"
  cd        "test_container/test_dir"
}

function teardown() {
  cd            "../.."
  chmod -R  777 "test_container/test_dir"
  rm    -rf     "test_container/test_dir"
}

function command_equal() {
    ls=$(ls "$@")
    ft_ls=$(../../ft_ls "$@")
    assert_equal "$ls" "$ft_ls"
}

function command_output() {
    ls=$(ls "$@")
    run ../../ft_ls "$@"
}


@test "test hyphen one hyphen" {
    # setup
    touch file -

    # tests
    command_equal -1
    command_equal -1 -
    command_equal -1 --
    command_equal -1 -- -
}

@test "test plurial hyphen" {
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

@test "test hyphen in dir name" {
###  setup *********************************************************************
    mkdir -- -dir --dir ---dir
###  tests *********************************************************************
    command_equal -1 -- -dir
    command_equal -1 -- --dir
    command_equal -1 -- ---dir
}

#@test "test hyphen and option" {
#    # setup
#    mkdir file_1 file_2
#
#    # tests
#    command_equal -- -1 -- file_1
#    assert_output  "$ls"
#    echo $ls > ../toto
#}
