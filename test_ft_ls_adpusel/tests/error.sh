echo "test error handling"

function command_equal() {
    ls "$@" > diff_ls 2>&1
  ../ft_ls "$@" > diff_ft 2>&1
  diff diff_ls diff_ft
}

command_equal not_exist