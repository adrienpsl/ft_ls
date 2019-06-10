data flow 
    - recoit en input lse data : 
        *   __main__ 
            parcours argv et le long contenant les arguments
            _ si str[i] == '-'
                *   __parse_argv__ 
                    print usage and return -1 if error
                    put option in the long option
            - launch ft_ls_main
            _
                *  



pas mal de chose ne vont pas car je n'ai pas 
gerer tout ls cas au debut.


utiliser l'option sans sort pour voir si je vais aller vite


fix le truc des - marche pour lire des file

fix si je donne un symlink, ls va le chercher, le parse et 
le set comme un symlink

quand il y a plusieur argv je dois mettre file_1path: file_2path: ...

pb je ne clean pas les symlync 

voir comment implementer l'option -d, print les d comme des file

-A pas le . et le ..
-aA pas le .

-p permet de mettre les / tout ca tout ca a la fin des file

si je peux pas l'ouvrir un file, je le print quand meme 
// mais je mets sur la sortie d'err qui il est. 

./b:
ls: b: permission denied

return same usage than ls

pb padding avec le -l et un file




                    
                    
                  
libft                                 
libft_ls_lib.a                        
src                   
                  













