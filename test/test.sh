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

#
### test guid / sticky bit / uid
#

# S udi
touch uids_big
chmod u+s uids_big

# s uid
touch uids_little
chmod 700 uids_little
chmod u+s uids_little

# S gdi
touch gids_big
chmod 707 gids_big
sudo chmod g+s gids_big

# s gid
touch gids_little
chmod 770 gids_little
sudo chmod g+s gids_little

# sticky T
touch sticky_big
chmod +t sticky_big

# sticky t
touch sticky_little
chmod 707 sticky_little
chmod +t sticky_little



#
### test date
#
touch -m -t 3003020303 future
touch -m -t 199009022233 past


#
### see file type
#

# block special
/dev/disk0

# regular file
/Users/adpusel/.zshrc

# directory
/Users/adpusel/Applications

# symbolic link
/dev/stderr

# char special
/dev/ttyv0

# fifo / socket
mkfifo fifofile

# socket
/var/run/pppconfd



