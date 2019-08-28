load 'libs/bats-support/load'
load 'libs/bats-assert/load'

function setup() {
  cp "../cmake-build-debug/ft_ls" "."
  mkdir -p "test_container/test_dir"
  cd "test_container/test_dir"
}

function teardown() {
  cd "../.."
  chmod -R 777 "test_container/test_dir"
  rm -rf "test_container/test_dir"
}

function command_equal() {

  ls=$(ls "$@")
  ft_ls=$(../../ft_ls "$@")

  assert_equal "$ft_ls" "$ls"
}

function test_print() {

  ls=$(ls "$@")

  assert_equal "" "$ls"
}

function generate_one_dir() {
  mkdir -p "$1"

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

  echo asohusaoehaoeuaoeuaoeuaoe >"$1"/file_1
  sleep 1
  echo asohusaoeh >"$1"/File_2
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

function do_all_test_with_argv() {
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
