load 'libs/utils'

# test file and path to big
@test "error : file no acces" {
    # setup
    mkdir dir_no_r;
    touch dir_no_r/toto;
    chmod 000 dir_no_r;

    # test
    test_print dir_no_r
}



# test memory with valgrind, how ?

