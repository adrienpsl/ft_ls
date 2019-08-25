#!./libs/bats/bin/bats

a=2;

setup()
{
  a=2
}

load 'libs/bats-support/load'
load 'libs/bats-assert/load'

@test "Should add numbers together" {
    assert_equal $(echo 1+1| bc) "$a"
}