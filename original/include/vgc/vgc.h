/* http://nullprogram.com/blog/2015/02/17/ */
/* https://github.com/skeeto/skeeto.github.com/blob/master/_posts/2015-02-17-Generic-C-Reference-Counting.markdown */
#pragma once

#if defined( __STDC__ )
# define CSTD 1990
# if defined( __STDC_VERSION__ )
#  define CSTD 1990
#  if ( __STDC_VERSION__ >= 199409L )
#   define CSTD 1990
#  endif
#  if ( __STDC_VERSION__ >= 199901L )
#   define CSTD 1999
#  endif
#  if ( __STDC_VERSION__ >= 201112L )
#   define CSTD 2011
#   include <stdatomic.h>
#  endif
# endif
#endif

#if CSTD == 1990
# define RC_INC( x ) ( ( x )++ )
# define RC_DEC( x ) ( --( x ) )
#endif
#if CSTD == 1999
# define RC_INC( x ) ( __sync_add_and_fetch( ( int* )( &( x ) ), 1 ) )
# define RC_DEC( x ) ( __sync_sub_and_fetch( ( int* )( &( x ) ), 1 ) )
#endif
#if CSTD == 2011
# define RC_INC( x ) ( atomic_fetch_add( ( int* )&( x ), 1 ) )
# define RC_DEC( x ) ( atomic_fetch_sub( ( int* )&( x ), 1 ) - 1 )
#endif

struct ref {
/*    void (*free)(const struct ref *);*/
    void (*free)( struct ref* );
    int count;
};

/*static inline void*/
void
/*ref_inc(const struct ref *ref)*/
ref_inc(struct ref *ref)
{
/*    ((struct ref *)ref)->count++;*/
   RC_INC( ref->count );
}

/*static inline void*/
void
/*ref_dec(const struct ref *ref)*/
ref_dec(struct ref *ref)
{
/*    if (--((struct ref *)ref)->count == 0)*/
    if( RC_DEC( ref->count ) == 0 ) { ref->free( ref ); }
}
