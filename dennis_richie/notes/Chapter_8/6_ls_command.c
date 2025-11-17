// a cmd to print all the file names in a directory in UNIX is done by ls. We want to do that is a relatively platform independent way in C.
// brief notes on UNIX file system: 
/*                  A directory contains a list of filenames and info and location of directory (inode_number).
                                                                                                        struct dirent {
                                                                                                            ino_t    d_ino;        // inode number
                                                                                                            char     d_name[];     // file name
                                                                                                        };
                        This inode is part of a table called- "inode list" (so a segment). (jargon- what about a table that stores perms rights and a sys service handles read and wrting from this table to cross check access to file-segment relationship)
                            A typical inode stores all information about the file except the file_name (since inode is a directory attribute)
                            eg- -> file type (regular, dir, symlink…)
                                -> permissions (rwx)
                                -> size
                                -> timestamps (atime, mtime, ctime)
                                -> owner UID/GID
                                -> reference count (link count)
                                -> pointers to data blocks:
                                    direct blocks
                                    indirect block
                                    double indirect block
                                    triple indirect block
                        */

// our program:
// the data contents of a directory is different for system of different versions.
    // so we will have 2 parts of the program to face this:
                                                    // 1. a portable part
                                                    // 2. a platform dependent part

#define _GNU_SOURCE // to make GNU specific variable words available like O_DIRECTORY
# include <sys/stat.h>

#define NAME_MAX 14  // longest filename component, system−dependent 
typedef struct {    // portable directory entry
    long ino;   // inode number
    char name[NAME_MAX+1];  // name + \0
} My_Dirent;

// each direcory of name and inode has a descriptor.
typedef struct {    // minimal members (no buffering)
    int fd;     // file descriptor for the directory
    My_Dirent d;   // directory entry.
} My_DIR;

/* Declarations used by the rest of your code (match usage in dirwalk) */
My_DIR *opendir(char *dirname);
My_Dirent *readdir(My_DIR *dfd);
void closedir(My_DIR *dfd);

/* 'stat' system call takes a filename and returns all of the information in the inode for that file, or −1 if there is an error. That is, fills the structure stbuf with the inode information for the file name. */
char *name;
struct stat stbuf;
// stat(name, &stbuf);

/* inode information returned by stat in <sys/stat.h> 
struct stat
{
    dev_t   st_dev;      // device of inode 
    ino_t   st_ino;      // inode number  
    short   st_mode;     // mode bits  
    short   st_nlink;    // number of links to file  
    short   st_uid;      // owners user id  
    short   st_gid;      // owners group id  
    dev_t   st_rdev;     // for special files  
    off_t   st_size;     // file size in characters  
    time_t  st_atime;    // time last accessed  
    time_t  st_mtime;    // time last modified  
    time_t  st_ctime;     // time originally created  
};
*/

// The st_mode entry contains a set of flags describing the file. The flag definitions are also included in <sys/types.h>; we need only the part that deals with file type:
#define S_IFMT    0160000  /* type of file: */
#define S_IFDIR   0040000  /* directory */
#define S_IFCHR   0020000  /* character special */
#define S_IFBLK   0060000  /* block special */
#define S_IFREG   0100000  /* regular file */

/* If the mode obtained from stat indicates that a file is not a directory, then the size is at hand and can be printed directly.
   If the name is a directory, however, then we have to process that directory one file at a time;
                                            it may in turn contain sub−directories, so the process is recursive.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> // flags for read and write 
#include <sys/types.h> //typedefs
#include <sys/stat.h>   // structure returned by stat
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>

/* Forward declarations for functions implemented below */
void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

/* print file name */
int main(int argc, char **argv)
{
    if (argc == 1) /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

// The function fsize prints the size of the file.
    // If the file is a directory, however, fsize first calls dirwalk to handle all the files in it.
    // flag names S_IFMT and S_IFDIR are used to decide if the file is a directory.

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)    // the recur call like binary tree, go to sub list until file, then all files in sub and Upwards.
        dirwalk(name, fsize);
    
    printf("%8ld %s\n", (long)stbuf.st_size, name);   // end case of recur (dir walk also ends from here).
}

// dirwalk is a fn tht calls fsize(). Since inside every fsize(), there may be a dir, the two functions call each other recursively.
#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))    // 2nd arg is a fn ptr
{
    char name[MAX_PATH];
    My_Dirent *dp;
    My_DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 ||
            strcmp(dp->name, "..") == 0)
            continue; /* skip self and parent */
        
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        else {      // the actual body of dirwalk
            sprintf(name, "%s/%s", dir, dp->name);      // done for all files (from while loop)
            (*fcn)(name);      // for each element in read, call fsize of it, if it is dir it will go through another fwalk.
        }
    }
    closedir(dfd);
}

/* ============================
   Start Platform-dependent part
   ============================
   Implement opendir / readdir / closedir that work the way K&R expects:
   - opendir opens directory as a file and returns a My_DIR *
   - readdir reads low-level directory records and returns My_Dirent *
   - closedir closes descriptor and frees state
*/

/* We'll use the Linux getdents64 syscall if available; define struct linux_dirent64
   roughly matching kernel layout. This replicates the old fixed-record dir format
   style used in K&R's code (not the POSIX readdir). */

#if defined(__linux__)
/* linux_dirent64 for getdents64 parsed from kernel ABI (user-space view).
   Note: d_name is a flexible array member; do NOT use sizeof(d->d_name). */
struct linux_dirent64 {
    ino_t          d_ino;       // user-space inode type
    off_t          d_off;       // offset to next dirent
    unsigned short d_reclen;    // length of this dirent record
    unsigned char  d_type;      // file type (not used here)
    char           d_name[];    // flexible array member
};
#endif

/* We will implement a simple buffered readdir using the getdents64 syscall.
   The implementation below keeps one buffer per directory stream; it's not thread-safe
   but matches the simple K&R behavior. */

#define D_BUF_SIZE 8192

struct dir_handle {
    int fd;
    char buf[D_BUF_SIZE];
    int nread;
    int bpos;
};

My_DIR *opendir(char *dirname)
{
    int fd = open(dirname, O_RDONLY | O_DIRECTORY);
    if (fd == -1)
        return NULL;

    /* allocate a combined block containing My_DIR then dir_handle */
    size_t wrap_sz = sizeof(My_DIR) + sizeof(struct dir_handle);
    void *wrap = malloc(wrap_sz);
    if (wrap == NULL) {
        close(fd);
        return NULL;
    }

    My_DIR *wrap_dp = (My_DIR *) wrap;
    struct dir_handle *wrap_h = (struct dir_handle *) ((char *)wrap + sizeof(My_DIR));

    /* initialize My_DIR part */
    wrap_dp->fd = fd;
    wrap_dp->d.ino = 0;
    wrap_dp->d.name[0] = '\0';

    /* initialize handle */
    wrap_h->fd = fd;
    wrap_h->nread = 0;
    wrap_h->bpos = 0;
    memset(wrap_h->buf, 0, D_BUF_SIZE);

    return wrap_dp;
}

/* Internal helper to get the handle pointer from My_DIR* */
static struct dir_handle *get_handle(My_DIR *dp)
{
    if (dp == NULL) return NULL;
    struct dir_handle *h = (struct dir_handle *) ((char *)dp + sizeof(My_DIR));
    return h;
}

/* readdir: read next entry and copy to dp->d (return pointer to dp->d or NULL) */
My_Dirent *readdir(My_DIR *dp)
{
    if (dp == NULL) return NULL;
    struct dir_handle *h = get_handle(dp);
    if (h == NULL) return NULL;

#if defined(__linux__)
    for (;;) {
        if (h->bpos >= h->nread) {
            /* refill buffer using getdents64 syscall */
            int n = syscall(SYS_getdents64, h->fd, h->buf, D_BUF_SIZE);
            if (n <= 0) {
                return NULL;
            }
            h->nread = n;
            h->bpos = 0;
        }

        /* parse one linux_dirent64 at buffer position */
        struct linux_dirent64 *d = (struct linux_dirent64 *)(h->buf + h->bpos);

        /* guard: ensure we have a plausible reclen */
        if (d->d_reclen == 0 || h->bpos + d->d_reclen > h->nread) {
            /* corrupt entry or truncated — bail out */
            return NULL;
        }

        if (d->d_ino == 0) {
            h->bpos += d->d_reclen;
            continue;
        }

        /* copy name, truncated to NAME_MAX -- don't use sizeof(d->d_name) */
        size_t namelen = strnlen(d->d_name, NAME_MAX);
        if (namelen > NAME_MAX) namelen = NAME_MAX;
        memcpy(dp->d.name, d->d_name, namelen);
        dp->d.name[namelen] = '\0';
        dp->d.ino = (long) d->d_ino;

        h->bpos += d->d_reclen;
        return &dp->d;
    }
#else
    /* Non-linux fallback: indicate unsupported platform */
    (void) h;
    errno = ENOSYS;
    return NULL;
#endif
}

void closedir(My_DIR *dp)
{
    if (dp == NULL) return;
    struct dir_handle *h = get_handle(dp);
    if (h) {
        close(h->fd);
    }
    /* free the combined allocation */
    free(dp);
}

/* ============================
   End platform-dependent part
   ============================ */

/* End of program */
