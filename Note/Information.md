# Les Fonctions autorisees

closedir ◦ stat ◦ lstat ◦ getpwuid ◦ getgrgid ◦ listxattr ◦ getxattr ◦ time ◦ ctime ◦ readlink ◦ malloc ◦ free ◦ perror ◦ strerror ◦ exit


### write
tente d'ecrire le nombre d'octer demander, les sortie d'err sont dans le man
```c 
ssize_t write(int fildes, const void *buf, size_t nbyte);
```
### opendir
retourn un ptr avec ptr sur un flux permettant d'interagir avec le dossier ouvert
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
	mode_t   st_mode;   /* inode protection mode */   
    
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

