#!./libs/bats/bin/bats
load 'libs/bats-support/load'
load 'libs/bats-assert/load'


ls=""
ft_ls=""

cp ../cmake-build-debug/ft_ls_test .

function setup()
{
 echo tata
}

function teardown()
{
  echo
}

function do_command() {
    ls=$(ls "$@")
    ft_ls=$(./ft_ls_test "$@")
}


@test "test hyphen hard" {
    touch file -
    do_command -1
    assert_equal "$ls" "$ft_ls"
    echo "$ls" "$ft_ls"
}