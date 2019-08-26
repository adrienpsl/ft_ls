#!/usr/bin/env ./test/libs/bats/bin/bats

# the first one is mine
# ------------------------------------------------------------------------------
#    load all the good stuff
# ------------------------------------------------------------------------------

load 'libs/utils'

# ------------------------------------------------------------------------------
#    with no argv ( only -l )
# ------------------------------------------------------------------------------

@test "long format | no argv : one file" {
    touch a
    command_equal -l
}

@test "long format | no argv : two file" {
    touch a b
    command_equal -l
}

@test "long format | no argv : three file" {
    touch a b c
    command_equal -l
}

@test "long format | no argv : right : 777" {
    touch file
    chmod 777 file
    command_equal -l
}

@test "long format | no argv : right : 000" {
    touch file
    chmod 000 file
    command_equal -l
}

@test "long format | no argv : right : mixed" {
    touch file_064 file_474 file_640 file_123 file_420
    chmod 064 file_640
    chmod 474 file_474
    chmod 640 file_640
    chmod 123 file_123
    chmod 420 file_420

    mkdir dir_064 dir_474 dir_640 dir_123 dir_420
    chmod 064 dir_640
    chmod 474 dir_474
    chmod 640 dir_640
    chmod 123 dir_123
    chmod 420 dir_420

    command_equal -l
}

@test "long format | no argv : special bits : file :  mixed" {
    touch file1 && chmod 0777 file1
    touch file2 && chmod 1777 file2
    touch file3 && chmod 2777 file3
    touch file4 && chmod 3777 file4
    touch file5 && chmod 4777 file5
    touch file6 && chmod 5777 file6
    touch file7 && chmod 6777 file7
    touch file8 && chmod 7777 file8
    touch file9 && chmod 0000 file9
    touch file10 && chmod 1000 file10
    touch file11 && chmod 2000 file11
    touch file12 && chmod 3000 file12
    touch file13 && chmod 4000 file13
    touch file14 && chmod 5000 file14
    touch file15 && chmod 6000 file15
    touch file16 && chmod 7000 file16

    command_equal -l
}

@test "long format | no argv : special bits : directory : mixed" {
    mkdir  dir1 && chmod 0777 dir1
    mkdir  dir2 && chmod 1777 dir2
    mkdir  dir3 && chmod 2777 dir3
    mkdir  dir4 && chmod 3777 dir4
    mkdir  dir5 && chmod 4777 dir5
    mkdir  dir6 && chmod 5777 dir6
    mkdir  dir7 && chmod 6777 dir7
    mkdir  dir9 && chmod 0000 dir9
    mkdir  dir9 && chmod 0000 dir9
    mkdir  dir10 && chmod 1000 dir10
    mkdir  dir11 && chmod 2000 dir11
    mkdir  dir12 && chmod 3000 dir12
    mkdir  dir13 && chmod 4000 dir13
    mkdir  dir14 && chmod 5000 dir14
    mkdir  dir15 && chmod 6000 dir15
    mkdir  dir16 && chmod 7000 dir16

    command_equal -l
}

@test "long format | no argv : date" {
    touch -t 204201010101 futur
    touch -t 199812312459 past
    touch                 current

    command_equal -l
}

@test "long format | no argv : symlik" {
  mkdir directory
  touch directory/file

  ln -s directory      dir_symlik
  ln -s directory/file file_symlik

  ln -s dir_symlik     sym_symlik_0
  ln -s sym_symlik_0   sym_symlik_1
  ln -s sym_symlik_1   sym_symlik_2

  command_equal -l
}

@test "long format | no argv : mixed test" {
  touch a b c && echo 'coucou' > a &&  echo 'hello world' > b
  mkdir 111 222 333 444 && touch 111/{a,b,c} && echo 'eat pizza' > 111/a

  command_equal -l
}

# ------------------------------------------------------------------------------
#    with argv
# ------------------------------------------------------------------------------

@test "long format | argv : file : one" {
    touch a b c
    command_equal -l b
}

@test "long format | argv : file : two" {
    touch a b c
    command_equal -l a c
}

@test "long format | argv : file : three" {
    touch a b c
    command_equal -l a b c
}

@test "long format | argv : directory : one" {
    mkdir directory
    touch directory/file_{1..20}
    command_equal -l directory
}

@test "long format | argv : directory : two" {
    mkdir directory_1 directory_2
    touch directory_1/file_{1..20} directory_2/file_{1..20}
    command_equal -l directory_1 directory_2
}


@test "long format | argv : directory and file : mixed" {
    mkdir directory_1 DIR_2 _directory_3
    touch DIR_2/file_{1..20} _directory_3/file_{1..20} .hidden

    ln -s directory_1 sym_dir_1
    ln -s DIR_2 sym_DIR_2

    touch file_1 file_2 .hidde
    ln -s file_1 sym_file_1

    command_equal -l file_1 file_2 directory_1 DIR_2 sym_dir_1 _directory_3 sym_DIR_2 .hidden
}

#
# if you got in error with the time section, I doesn't mean
# that your ls is wrong, like that line I delete by  sed
# ls may trigger something and change its time.
@test "long format | argv : socket test" {
    ../../ft_ls -l /var/run > a
    ls -l /var/run > b

    sed -i '' '/utmpx/d' a
    sed -i '' '/utmpx/d' b

    run diff a b
    assert_output ""
}

#
# same comment that's previous one
@test "long format | argv : block and char " {
    ../../ft_ls -l /dev > a
    ls -l /dev > b

    files=("afsc_type5" "auditsessions" "autofs_homedirmounter" "autofs_notrigger" "autofs_nowait" "bpf1" "bpf3" "console" "disk0s1" "dtrace" "io8log" "io8logmt" "io8logtemp" "klog" "null" "random" "rdisk0s1" "tty" "urandom")

    for i in "${files[@]}"
    do :
        sed -i '' "/$i/d" a
        sed -i '' "/$i/d" b
    done

    run diff a b
    assert_output ""
}