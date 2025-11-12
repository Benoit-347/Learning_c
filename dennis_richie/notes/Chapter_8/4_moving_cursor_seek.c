// reading and writing happens sequentially, with respect to the cursor. However, you can also move around arbitarily without reading/writing by using a sys call lseek().
    // long lseek(int fd, long offseet, int origin);    the origin shows the position to which the offset is added, and then sets postion of cursor.
        // origin can show the beggining of the file as 0, or current position as 1,5,10, and the offset is calculated from this position (depending on origin, offset on beggining or current position).

// when we want to append onto a file, we can use >>, or a 'a' mode in fopen(); which seeks to the end of the file when opening.
    // going back to beggining of a file: lseek(fd, 0L, 0);

//  a fn is shown below, that reads n bytes from any arbitary location of the file.

# include <unistd.h>

int get(int fd, long pos, char * buf, int n){
    if (lseek(fd, pos, 0) >= 0)
        return read(fd, buf, n);    // returns the new position of file, after reading.
    else
        return -1;
}