#!/usr/bin/env ./test/libs/bats/bin/bats

# ------------------------------------------------------------------------------
#    load all the good stuff
# ------------------------------------------------------------------------------

load 'libs/utils'

@test "recursive | no argv : one level : one directory" {
    mkdir dir_1
    touch dir_1/file_a{1..50}

    command_equal -1R
}

@test "recursive | no argv : one level : one directory && files" {
    touch file_1 file_2
    mkdir dir_1
    touch dir_1/file_a{1..50}

    command_equal -1R
}

@test "recursive | no argv : one level : directories && files" {
    touch file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua
    mkdir dir_1 DIR_2 .hiden
    touch dir_1/file_a{1..50}
    touch DIR_2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch .hiden/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    command_equal -1R
}

@test "recursive | no argv : 2 level : directories && files" {
    touch file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua
    mkdir -p dir_1 DIR_2/-1 .hiden
    touch dir_1/file_a{1..50}
    touch DIR_2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch .hiden/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    command_equal -1R
}

@test "recursive | no argv : multi level : directories && files" {
    touch file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua
    mkdir -p dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
    touch dir_1/file_a{1..50}
    touch DIR_2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch DIR_1/-1/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch DIR_1/-1/-2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/-2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch DIR_1/-1/-2/-3/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/-2/-3/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch .hiden/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    command_equal -1R
}

@test "recursive | argv : multi argv : directories && files" {
    touch file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua
    mkdir -p dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
    touch dir_1/file_a{1..50}
    touch DIR_2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch DIR_1/-1/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch DIR_1/-1/-2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/-2/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch DIR_1/-1/-2/-3/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}
    touch DIR_2/-1/-2/-3/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    touch .hiden/file_aaseuhaoseuhasoeuhgaoesuhsaoaosuehaoseuasoeuhasouheaseuhsaoeheeeroeuhao{1..50}

    command_equal -1R file_1 file_2 asouh oseuh oaeu upm aoeue aoe .aeoua dir_1 DIR_2/-1/-2/-3 DIR_2/aoeoaeu DIR_1/aoeu  DIR_1/-1/-2/-3 .hiden
}