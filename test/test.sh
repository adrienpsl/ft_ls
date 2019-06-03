#!/usr/bin/env bash

# clean working depot
rm -rf test_ls

mkdir test_ls
cd test_ls
mkdir toto
cd toto

touch 42-rwxrwxrwx
chmod 777 42-rwxrwxrwx

touch 42-w--w--w--
chmod 222 42-w--w--w--

touch 42----rwxrwx
chmod 077 42----rwxrwx

touch 42------x--x
chmod 011 42------x--x

touch 42-r-xr-xr-x
chmod 555 42-r-xr-xr-x

touch 42-----wxrwx
chmod 037 42----------

touch 42----------
chmod 000 42----------

ln -s 42---------- linked

mkdir directory

mkdir dir
chmod 000 dir

mkfifo fifofile


# test for sort data
rmd -rf toto
mkdir toto
cd toto

touch origin
touch modify
touch change

sleep 2
echo aoehuaonseuhasoeuhaoeuhaoseuhaoseuhaoseuhsaoe > modify

sleep 2
chmod 777 change

cd ..




