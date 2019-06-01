# Les Fonctions autorisees

closedir ◦ stat ◦ lstat ◦ getpwuid ◦ getgrgid ◦ listxattr ◦ getxattr ◦ time ◦ ctime ◦ readlink ◦ malloc ◦ free ◦ perror ◦ strerror ◦ exit


### write
tente d'ecrire le nombre d'octer demander, les sortie d'err sont dans le man
```c 
ssize_t write(int fildes, const void *buf, size_t nbyte);
```
### opendir
retourn un ptr avec ptr sur un flux permettant d'interagir avec le dossier ouvert, marche aussi avec "."
null si malloc merde ou pas de file
```objectivec
// function ========================
DIR *topendir(const char *filename);

//  stucture : ======================
typedef struct
{
	int __dd_fd;    /* file descriptor associated with directory */
	long __dd_loc;    /* offset in current buffer */
	long __dd_size;    /* amount of data returned */
	char *__dd_buf;    /* data buffer */
	int __dd_len;    /* size of data buffer */
	long __dd_seek;    /* magic cookie returned */
	__unused long __padding; /* (__dd_rewind space left for bincompat) */
	int __dd_flags;    /* flags for readdir */
	__darwin_pthread_mutex_t __dd_lock; /* for thread locking */
	struct _telldir *__dd_td; /* telldir position recording */
} DIR; 
```

### readdir 
donne acces a tout les dir de la struct DIR donner en agument
le classement des directory n'est pas certain et depend des systemes
```objectivec
   // function ============
   struct dirent * readdir(DIR *dirp);

   // return ===============
   // il y a une protection en fonction du noyaux
   #define __DARWIN_STRUCT_DIRENTRY { \
   	__uint64_t  d_ino;      /* file number of entry */ \
   	__uint64_t  d_seekoff;  /* seek offset (optional, used by servers) */ \
   	__uint16_t  d_reclen;   /* length of this record */ \
   	__uint16_t  d_namlen;   /* length of string in d_name */ \
   	__uint8_t   d_type;     /* file type, see below */ \
   	char      d_name[__DARWIN_MAXPATHLEN]; /* entry name (up to MAXPATHLEN bytes) */ \
   }
   
   /*
    * File types
    */
   #define	DT_UNKNOWN	 0
   #define	DT_FIFO		 1
   #define	DT_CHR		 2
   #define	DT_DIR		 4
   #define	DT_BLK		 6
   #define	DT_REG		 8
   #define	DT_LNK		10
   #define	DT_SOCK		12
   #define	DT_WHT		14
```


### close DIR
 The closedir() function closes the named directory stream and frees the structure associated with the dirp pointer, returning 0 on success.  On failure, -1 is returned and the global
 variable errno is set to indicate the error.
 ```objectivec
  int closedir(DIR *dirp);
```

### stat 
```objectivec
   // function ==================
   int stat(const char *restrict path, struct stat *restrict buf);

//structure stat
struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
	
	// current protect of file
	mode_t   st_mode;   /* inode protection mode */   les droits du fichier
    
	// The inode for the file (note that this number is unique to all files and directories on a Linux System.
    ino_t    st_ino;    /* [XSI] File serial number */           
    
    // The device that the file currently resides on. // TODO : disque dur ?
    dev_t    st_dev;    /* device inode resides on */ // 
  
    uid_t    st_uid;    /* user-id of owner */
    
    gid_t    st_gid;    /* group-id of owner */
    
    nlink_t  st_nlink;  /* number of hard links to the file */
    
    dev_t    st_rdev;   /* device type, for special file inode */
    
    struct timespec st_atimespec;  /* time of last access */
    
    struct timespec st_mtimespec;  /* time of last data modification */
    
    // permission
    struct timespec st_ctimespec;  /* time of last file status change */
    
    off_t    st_size;   /* file size, in bytes */
    
    
    quad_t   st_blocks; /* blocks allocated for file */
    
    u_long   st_blksize;/* optimal file sys I/O ops blocksize */
    u_long   st_flags;  /* user defined flags for file */
    u_long   st_gen;    /* file generation number */
};
```

### lstat permet de faire la meme chose, sauf pour les liens symbolic ou :
The lstat() function is like stat() except in the case where the named
file is a symbolic link; lstat() returns information about the link,
while stat() returns information about the file the link references.  For
symbolic links, the st_mode member contains meaningful information when
used with the file type macros, and the st_size member contains the
length of the pathname contained in the symbolic link. File mode bits and
the contents of the remaining members of the stat structure are unspeci-
fied. The value returned in the st_size member is the length of the con-
tents of the symbolic link, and does not count any trailing null.





# getpwuid
La fonction getpwnam() renvoie un pointeur sur une  struc­
ture  contenant  les  divers champs de l'enregistrement de
/etc/passwd correspondant au nom d'utilisateur name. 
```objectivec
La structure passwd est définie dans <pwd.h> ainsi :

struct passwd {
    char   *pw_name;   /* Nom d'utilisateur             */
    char   *pw_passwd; /* Mot de passe                  */
    uid_t   pw_uid;    /* ID de l'utilisateur           */
    gid_t   pw_gid;    /* ID du groupe de l'utilisateur */
    char   *pw_gecos;  /* Nom réel de l'utilisateur     */
    char   *pw_dir;    /* Répertoire de connexion       */
    char   *pw_shell;  /* Programme Shell de connexion  */
};
```

# getgrgid
La fonction getgrnam() renvoie un pointeur  sur  structure
contenant  l'enregistrement  issus  de  /etc/group pour le
groupe correspondant au nom name.

La fonction getgrnid() renvoie un pointeur  sur  structure
contenant  l'enregistrement  issus  de  /etc/group pour le
groupe correspondant a l'ID gid.

```objectivec
La structure group est définie dans <grp.h> ainsi :

struct group {
    char   *gr_name;    /* Nom du groupe.          */
    char   *gr_passwd;  /* Mot de passe du groupe. */
    gid_t   gr_gid;     /* ID du groupe.           */
    char  **gr_mem;     /* Membres du groupe.      */
};
```



# les extended attributs : 
Use listxattr() to get a list of the names of all the extended attributes, 
and getxattr() to get the value of a particular attribute. 
If listxattr returns a non-zero result, you would display @ to indicate this.

code
http://man7.org/tlpi/code/online/diff/xattr/xattr_view.c.html






# les ACL access control list are display by : +

# le code pour en generer une avec le shell  
les acl sont des attribut specioux qui permette d'affiner plus finements les droits
voir le man de chmod pour les definir
commande a tester : 
--> refaire ces commande pour tester 
# ls -le
-rw-r--r--+ 1 juser  wheel  0 Apr 28 14:06 file1
# chmod +a "admin allow write" file1
# ls -le
-rw-r--r--+ 1 juser  wheel  0 Apr 28 14:06 file1
owner: juser
1: admin allow write
# chmod +a "guest deny read" file1
# ls -le
-rw-r--r--+ 1 juser  wheel  0 Apr 28 14:06 file1
owner: juser
1: guest deny read
2: admin allow write

## code pours les print
http://man7.org/linux/man-pages/man2/listxattr.2.html 

# readlink 
met dans le buffer fournis le chemin pour aller au symlink donner par le systeme
```objectivec
The following program allocates the buffer needed by readlink()
       dynamically from the information provided by lstat(2), falling back
       to a buffer of size PATH_MAX in cases where lstat(2) reports a size
       of zero.

       #include <sys/types.h>
       #include <sys/stat.h>
       #include <limits.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>

       int
       main(int argc, char *argv[])
       {
           struct stat sb;
           char *buf;
           ssize_t nbytes, bufsiz;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
           }

           /* Add one to the link size, so that we can determine whether
              the buffer returned by readlink() was truncated. */

           bufsiz = sb.st_size + 1;

           /* Some magic symlinks under (for example) /proc and /sys
              report 'st_size' as zero. In that case, take PATH_MAX as
              a "good enough" estimate. */

           if (sb.st_size == 0)
               bufsiz = PATH_MAX;

           buf = malloc(bufsiz);
           if (buf == NULL) {
               perror("malloc");
               exit(EXIT_FAILURE);
           }

           nbytes = readlink(argv[1], buf, bufsiz);
           if (nbytes == -1) {
               perror("readlink");
               exit(EXIT_FAILURE);
           }

           printf("'%s' points to '%.*s'\n", argv[1], (int) nbytes, buf);

           /* If the return value was equal to the buffer size, then the
              the link target was larger than expected (perhaps because the
              target was changed between the call to lstat() and the call to
              readlink()). Warn the user that the returned target may have
              been truncated. */

           if (nbytes == bufsiz)
               printf("(Returned buffer may have been truncated)\n");

           free(buf);
           exit(EXIT_SUCCESS);
       }
```





# getxattr
je sais pas 


# strerror 
affirche l'error contenu dans ernum faire un test ?
```objectivec
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main ()
{
  FILE * pFile;
  pFile = fopen ("unexist.ent","r");
  if (pFile == NULL)
    printf ("Error opening file unexist.ent: %s\n",strerror(errno));
  return 0;
}
```

# perror fais la meme chose je pense
```objectivec
#include <stdio.h>

int main () {
   FILE *fp;

   /* first rename if there is any file */
   rename("file.txt", "newfile.txt");

   /* now let's try to open same file */
   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      perror("Error: ");
      return(-1);
   }
   fclose(fp);
      
   return(0);
}
```

## exemple des deux 
```objectivec
int s;

s = socket(PF_INET, SOCK_STREAM, 0);

if (s == -1) { // some error has occurred
    // prints "socket error: " + the error message:
    perror("socket error");
}

// similarly:
if (listen(s, 10) == -1) {
    // this prints "an error: " + the error message from errno:
    printf("an error: %s\n", strerror(errno));
}
```


# option a implementer
ne pas print les fichier . c'est important man !


- tout trier en ordre ascii oui 

-1, met tout sur une colomne

-A, tt sauf . et .. 

-a -> les fichier .

-F Display a slash (`/') immediately after each pathname that is a directory, an asterisk (`*') after each that is executable, an at sign (`@') after each symbolic link, an equals sign (`=') after each
                socket, a percent sign (`%') after each whiteout, and a vertical bar (`|') after each that is a FIFO.
-G met les meme couleur que zsh

-r      Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size

-R      Recursively list subdirectories encountered.


























