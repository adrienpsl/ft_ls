
load 'libs/bats-support/load'
load 'libs/bats-assert/load'

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

    assert_equal "$ft_ls" "$ls"
}
