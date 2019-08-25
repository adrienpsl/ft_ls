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

@test "test double hyphen stop catching option" {
    # setup
    touch file

    # tests
    run ../../ft_ls -1 -- -a file
    out=$(printf "ls: -a: No such file or directory\nfile")
    assert_output "$out"
}

@test "long format test" {
    touch a b c
    command_equal -l

}
