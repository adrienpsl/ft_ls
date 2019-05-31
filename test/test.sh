#!/usr/bin/env bash

# clean working depot
#rm -rf test_ls
mkdir test_ls
cd test_ls

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
chmod 0 42----------

ln -s 42---------- linked

mkdir directory

cd dir
touch toto
chmod 000 dir
mknod: MYFIFO: File exists


sudo mknod ./lp0 c 6 0
sudo mknod MYFIFO b 0 9
     mkfifo a=rw MYFIFO

