#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc, free */
#include <stddef.h>  /* offsetof */
#include <stdarg.h>  /* va_list */
#include <errno.h>
#include <vgc/vgc.h> /* refcount, ref_inc, ref_dec */

#ifndef container_of
#define container_of(ptr, type, member)     \
           ( ( type * )                     \
             ( ( char* )( ptr ) -           \
               offsetof( type, member ) ) )
#endif

#ifndef snprintf
int
snprintf( char *buffer, size_t n, const char *format, ... )
{
   va_list ap;
   int r;

   va_start( ap, format );
   if( ( r = sprintf( buffer, format, ap ) ) > n )
   {
      errno = EFBIG;
      r = -1;
   }
   va_end( ap );

   return( r );
}
#endif

struct node
{
   char id[ 64 ];
   float value;
   struct node *next;
   struct ref refcount;
};

/*static void*/
void
/*node_free(const struct ref *ref)*/
node_free( struct ref *ref )
{
   struct node *node = container_of( ref, struct node, refcount );
   struct node *child = node->next;
   free( node );
   if( child ) ref_dec( &child->refcount );
}

struct node *
node_create( char *id, float value )
{
   struct node *node = malloc( sizeof( *node ) );
   snprintf( node->id, sizeof( node->id ), "%s", id );
   node->value = value;
   node->next = NULL;
/*    node->refcount = (struct ref){node_free, 1};*/
   node->refcount.free = node_free;
   node->refcount.count = 1;
   return node;
}

void
node_push( struct node** nodes, char *id, float value )
{
   struct node *node = node_create( id, value );
   node->next = *nodes;
   *nodes = node;
}

struct node*
node_pop( struct node** nodes )
{
   struct node* node = *nodes;
   *nodes = ( *nodes )->next;
   if( *nodes ) ref_inc( &( *nodes )->refcount );
   return node;
}

void
node_print( struct node* node )
{
   for( ; node; node = node->next )
      printf( "%s = %f\n",
              node->id,
              node->value );
}

int
main( int argc, char** argv )
{
   struct node *nodes = NULL;
   char id[ 64 ];
   float value;
   while( scanf( " %63s %f", id, &value ) == 2 )
      node_push( &nodes, id, value );
   if( nodes != NULL )
   {
      node_print( nodes );
      struct node *old = node_pop( &nodes );
      node_push( &nodes, "foobar", 0.0f );
      node_print( nodes );
      ref_dec( &old->refcount );
      ref_dec( &nodes->refcount );
   }
   return 0;
}

