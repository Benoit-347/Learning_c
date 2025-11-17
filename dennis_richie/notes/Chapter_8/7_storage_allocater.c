// a storage is allocated in C with the help of the OS, which is what malloc does,
    // the free space in memory is in format of a linked memory, where blocks of memory exist, and each block has a element that points to the next block; whr the last block points to the 1st block.
    
// on requesting for storage, based on below 2 algo, the block is unlinked and provided to request.
                                // fist fit- first found, big enough block.
                                // best fit- the smallest, enough block.

 // if block is too big- it is split, unlinked and provided, if too small- requested to OS and provided
 // freeing- it also has an algorithm to find a spot to insert into the free list.
    // if the adjacent blocks of memory are free, they are merged to form a single block. (prevents too much fragmentation).

/*Contents of  a free block:
        A. Overhead-
            1. a ptr to next block in chain 'header i '
            2. a record of size of its block 'header ii'
        B. The free space
*/

// the control information at the beggining is called 'header'
    // alignment is a multiple of this header.  by creating a big data withing a union, with header in union


typedef long Align; // for alignment to the boundary of long; as 'long' has one of the largest size, with strict alignment requirements

// 2 members- 1. struct, 2. Align
union header { // the block
    struct {
        union header *ptr; // next block if on free list
        unsigned size;    // size of this block
    } s;
    Align x; // this forces alignment of block due to making them all sized to biggest element.
};

// sizeof(header) will be long/Align here
typedef union header Header;


// here the field x is never used, it only forces the header to be aligned on the worst case boundary.

// (nbytes + H - 1) / H     round-up if 1.9 => 2  if 1.1 => 2
    // (H-1)/H returns +empty if full number, even for the smallest addition (1), returns +1

// Calculate the total required number of units (including header): nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
                                                                                                                        // +1 at end to account overhead of header as well.
                                                                                                                            // note: the ptr returned by malloc points to free space, not to the header itself.
 
/*
 * The variable `base` is used to bootstrap the allocator.
 *
 * On the very first call to malloc(), `freep` is NULL.
 * When this happens, a degenerate free list is created:
 *     - It contains one block of size 0.
 *     - Its `next` pointer points back to itself.
 * This establishes a circular free list so later allocations can proceed normally.
 *
 * The free list is always searched starting from `freep` — the position
 * where the last allocation or deallocation occurred. This helps keep the
 * list more uniform and reduces fragmentation over time.
 *
 * During the search:
 *   - If a block of exactly the right size is found, it is removed from
 *     the free list and returned.
 *
 *   - If a block is larger than needed, it is split:
 *        * The tail end (the excess portion) is allocated to the user.
 *        * The original block's header is left in place, with its size
 *          reduced to reflect the remainder.
 *
 * The pointer returned to the user always refers to the usable memory
 * portion of the block — one unit past the header.
 * The header itself stores bookkeeping information (size and next pointer)
 * and precedes the block returned to the user.
 */

# include <stdio.h>
# include <unistd.h>

static Header base;         /* empty list to get started */
static Header *freep = NULL; /* start of free list */
// Header: s.ptr, s.s

// freep is basically pointing to a random position in the free block, atually placed at free block right behind most recent allocated block. (acts as parent ptr at start and end of code).
    // uses freep's parent property with looping on p (with memory of parent to prevp; freep nolonger parent mid loop)
            // to find if a whole circle was done, to indicate no match found over whole free list.
// we have 3 ptrs to Header now, p and prevp will be used in loop for new allocation and mem, and we need need 3rd for circle endpoint tracking.
static Header *morecore(unsigned);

/* malloc: general−purpose storage allocator */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;      // 2 ptrs to Header struct. 1 for returning allocation. 2. for keeping memory of past ptr (linking head of parent (cur is to be removed) with the header of next to cur.)   i.e head of parent to cur.ptr
    unsigned nunits;

    // Calculate the total required number of units (including header)
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        /* no free list yet */
        base.s.ptr = &base; // usually ptr points to another 'base' hence here, itself (self pointing to show null freep)
        base.s.size = 0;
        freep = &base;
        prevp = &base; // Ensure prevp starts at base if the list is new
    }

    // Loop through the free list to find a block.
        // always keeps freep at block next to newest allocation. (even on reaching end of block goes back to begginingblocks are a circular queue).
    // initialize p to point to free block nxt to prevp.
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) { // p hold nxt base, every loop, assign p to prevp, give p nxt base.
        if (p->s.size >= nunits) { /* big enough */
            // p will hold ptr to block of mem

            // exact size req met; link head of parent to tail of p. 
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            }
            //split,-only change size       header, tail not changed- as the block is not fully consumped hence header wont be lost, hence parent header not to be changed to block tail (which is ptr to nxt header)
                // tail side of block is given to request (head side is left as is)
            else {
                p->s.size -= nunits;    // remove new allocation size form block size
                p += p->s.size; // Shift to, start of new allocated block
                p->s.size = nunits;     // for new header, assign size as requested size.   (writes to mem at start, possible here in c as allocation is cast to 'Header' struct).
            }   // prevp not changed. as p is removed.

            // after getting p to point new allocation, change freep to accomodate new parent pos. (for less freagmentation- freep to point to pos behind last allocation)
            freep = prevp;
            return (void *)(p + 1); // Return pointer past the header
        }

        // reach here whn the particular block in loop is smaller than req
            // if below if false, loop until a circle is done
        if (p == freep) { /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL) {
                return NULL; /* none left */
            }
            // if reached here, then loop back to for loop since memory allocation suceeded
        }
    }
}

/*
note: when allocated space is provided to request, we add 1 and provide, this 1 (header) to not be used. Which may accumulate over time.
    So when the user frees the block, the original header is found easily with:
        free(ptr) → ptr - 1 = header
*/

// asking the system for memory is an expensive operation. So a large chunk 'NALLOC' units is requested by morecore when it needs memory for free list.
    // morecore spilts this huge chunk, steps up the size field and adds this to free list by calling free fn, adding additional memory to the arena.


// Unix sys call sbrk(n) returns a ptr to n bytes of memory. Returns -1 if there is no space. (even tho 0 would have been a better design).

// due to standard pointer comparision being only between pointers of an arr. This may not be portable. But works where general pointer comparision is meaningful, All UNIX systems.

# define NALLOC 1024
void free(void *ap);

static Header * morecore(unsigned nu){
    char * cp;
    // char *sbrk(int);
    Header * up;

    if (nu < NALLOC)
        nu = NALLOC;

    // not a direct (Header *) for cmp (char *) ptr with -1
    cp = sbrk(nu * sizeof(Header)); // return nu count of Headers of 1 byte unit chunks of memory.
    if (cp == (char *) -1)  //  casting to (char *) is imp as cp is a ptr. hence cast to char * required.
        return 0;
    up = (Header *) cp;
    up -> s.size = nu;
    free( (void *) (up + 1) );  // context: usually we free a block thats is deallocated from us, so it contains header. To clear header and add to free list, the free fn expects the arg ptr to be the free section of block. Therefore free adds section strating from ptr -1, to free list. Hence, +1 here to work with that agenda.
    return freep;
}


// free scans free list starting from freep.
    // if next to a free block, merge.

void free(void *ap){
    Header *bp, *p;

    bp = (Header *) ap -1;  // push header of ptr as well to free list

    // this loop checks if the new free allocation is near the eges of free list. (uses circular queue feature)
    // for loop: normal cond- increasing p and p->str, bp bw a free range; if cond- special pos of p and p->s.str, p->s.ptr has gone to left edge, and bp is between thisleft or right edge.
        // loop cond holds true as long as bp is not (after parent and before current) -> between 2 blocks of free mem (it does NOT hold true for unique pos whr p > p->s.ptr; as here bp>p but < p->s.ptr showing normal p and p->ptr, hence not edge case)
        for (p = freep; !( bp > p  && bp < p->s.ptr ); p = p->s.ptr)
            if (p >= p-> s.ptr && (bp > p || bp < p->s.ptr))    // p > p->s.ptr shows the unique pos of parent when, p is at right edge and p->s.ptr is at left edge
                                                                // the or cond chks right edge (bp > p ) or left edge (bp < p->s.ptr)
            break;  // freed block at start and end of arena
    
    // join to upper nbr
    if (bp + bp->s.size == p-> s.ptr){
        bp -> s.size += bp->s.size;
        p->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    // join to lower nbr
    if (p + p->s.size == bp){
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    
    freep = p;
}

int main(){
    char * ptr = malloc(100);
    for (int i = 0; i<100; i++){
        ptr[i] = i;
    }

    for (int i = 0; i<100; i++){
        printf("%d\n", ptr[i]);
    }

    return 0;
}