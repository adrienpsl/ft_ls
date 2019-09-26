rm -rf render/*
mkdir -p render/includes;
mkdir -p render/src;

cp Makefile render
cp includes/* render/includes
find ./src -type f -name "*.h" -exec cp {} ./render/includes \; ;
find ./src -type f -name "*.c" -not -name "*test*" -exec cp {} ./render/src \; ;

cp -R ./libft/render render/libft

cd ./render
make;
#cd ./..;
#
#norminette ./render/src;
#norminette ./render/includes;
