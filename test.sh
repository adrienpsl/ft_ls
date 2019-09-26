
#echo "norminette : --------------------------------------------------------"
#norminette . | grep "Error"

#echo "nm : ----------------------------------------------------------------"
#nm ft_ls | grep "U"

#echo "init test dir no arguments : ----------------------------------------"

## create a dir and watch inside
mkdir -p test_dir_1/test_dir_1_1/test_dir_1_2
touch test_dir_1/file{1..3}
touch file{1..3}
touch test_dir_1/test_dir_1_1/file{1..3}
touch test_dir_1/test_dir_1_1/test_dir_1_2/file{1..3}
ln -s  test_dir_1 s_dir
ln -s  file2 s_file

function t_() {
  echo "$@" "           ========================================================="
  ls -1 "$@"        > ls_result
  ./ft_ls -1 "$@"   > ft_result
  diff ls_result ft_result
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