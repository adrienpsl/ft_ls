# ------------------------------------------------------------------------------
#    load all the good stuff
# ------------------------------------------------------------------------------
load 'libs/utils'

#@test "option_u" {
#    generate_one_dir "."
#
#    command_equal -1u
#    command_equal -lu
#    command_equal -lru
#}
#
#@test "option_S" {
#    generate_one_dir "."
#
#    command_equal -1S
#    command_equal -lS
#    command_equal -lrS
#}
#
#@test "option_c" {
#    mkdir dir
#    sleep 1
#    touch dir/toto dir/titi
#    echo 212121 > dir/titi
#
#    command_equal -1c
#    command_equal -lc
#    command_equal -lrc
#}

@test "option_n" {
    generate_one_dir "."

    command_equal -1n
    command_equal -ln
    command_equal -lr
}

@test "option_T" {
    generate_one_dir "."

    command_equal -1T
    command_equal -llT
    command_equal -lrT
}

@test "option_o" {
    generate_one_dir "."

    command_equal -o
    command_equal -lo
}