
#echo "norminette : --------------------------------------------------------"
norminette . | grep "Error"

#echo "nm : ----------------------------------------------------------------"
nm ft_ls | grep "U"

#echo "init test dir no arguments : ----------------------------------------"

## create a dir and watch inside
mkdir -p test_dir_1/test_dir_1_1/test_dir_1_2
mkdir -p test_dir_2/test_dir_2_1/test_dir_2_2
touch test_dir_1/file{1..3}
touch file{1..3}
touch test_dir_1/test_dir_1_1/file{1..3}
touch test_dir_2/test_dir_2_1/file{1..3}
touch test_dir_1/test_dir_1_1/test_dir_1_2/file{1..3}
touch test_dir_2/test_dir_2_1/test_dir_2_2/file{1..3}

mkdir -p test_dir_2/test_dir_2_1/test_no
chmod 000 test_dir_2/test_dir_2_1/test_no

ln -s  test_dir_1 s_dir
ln -s  file2 s_file

function t_() {
  echo "$@" "           ========================================================="
  ls -1 "$@"        > ls_result 2>&1
  ./ft_ls -1 "$@"   > ft_result 2>&1
  diff ls_result ft_result
}

function v_() {
    valgrind --log-fd=1 ./ft_ls  "$@" | grep "definitely lost:"
}

echo
echo  "test simple no arguments"
t_
t_ -a
t_ -l

echo
echo "test with file"
t_ file1
t_ -a file1
t_ -l file1

echo "test with simlink"
t_ s_file
t_ s_dir
t_ -a s_file
t_ -a s_dir
t_ -l s_file
t_ -l s_dir


echo
echo "test with directory"
t_ /
t_ -a /
t_ -l /

t_  /var/run/
t_ -l /var/run/
t_ -r /var/run/
t_ -t /var/run/
t_ -rlt /var/run/

#t_ -Rl /Users/adpusel

#t_ -Rrl1  a /Users/adpusel
t_ -Rlt
t_ -Rrlt

t_ -Rrlt . . file1 . file2 . s_dir s_file

# test not allowed
mkdir -p not_allowed_file
chmod 000 not_allowed_file
t_ not_allowed_file

t_ -Z_this_option_does_not_exist
t_ -la--t

#touch a b
#t_ a '' b

t_ -lZWYX243
#t_ r h

mkdir adir zdir
touch afile zfile
ln -s adir asymdir
ln -s adir zsymdir
ln -s afile asymfile
ln -s afile zsymfile

t_ -1 adir zdir aNotExist zNotExistB afile zfile asymdir zsymdir asymfile zsymfile


#echo
#echo test memory
v_ ""
v_ /
#v_ -R /Users/adpusel
v_ aa hh
v_ -Z_this_option_does_not_exist
v_ -Rrlt /Users/adpusel
#v_ not_allowed_file