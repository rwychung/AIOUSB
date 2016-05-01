#include "AIOProductTypes.h"
#include <stdarg.h>
#include <string.h>


#ifdef __cplusplus
namespace AIOUSB {
#endif


AIOProductRange *NewAIOProductRange( unsigned long start, unsigned long end)
{
    AIOProductRange *tmp = (AIOProductRange*)malloc(sizeof(AIOProductRange));
    if (!tmp) return NULL;
    tmp->_start = start;
    tmp->_end   = end;
    return tmp;
}

AIORET_TYPE DeleteAIOProductRange( AIOProductRange *pr )
{
    AIO_ASSERT( pr );
    free(pr);
    return AIOUSB_SUCCESS;
}

AIORET_TYPE AIOProductRangeStart( const AIOProductRange *pr )
{
    AIO_ASSERT(pr);
    return pr->_start;
}

AIORET_TYPE AIOProductRangeEnd( const AIOProductRange *pr )
{
    AIO_ASSERT(pr);
    return pr->_end;
}

/* This is a hack to allow
 * me to not force users to use -std=gnu++11
 */
#ifdef __cplusplus
AIOProductGroup::AIOProductGroup( size_t numbergroups, ... ) : _num_groups(numbergroups), _groups(NULL)
{
    va_list arguments;
    this->_groups = new AIOProductRange*[numbergroups];
    va_start( arguments, numbergroups );
    for ( int i = 0; i < (int)numbergroups ; i ++ ) {
        AIOProductRange *tmp = va_arg( arguments, AIOProductRange*);
        this->_groups[i] = tmp;
    }
    va_end(arguments);
}

AIOProductGroup::~AIOProductGroup(){
    for ( int i = 0; i < (int)this->_num_groups; i ++ ) { 
        delete this->_groups[i];
    }
    delete [] this->_groups;
}
#endif

AIOProductGroup *NewAIOProductGroup(size_t numbergroups, ... )
{
    va_list arguments;
    int i;
    AIOProductGroup *ng = (AIOProductGroup*)malloc(sizeof(AIOProductGroup));
    if ( !ng ) return NULL;
    ng->_groups = (AIOProductRange**)malloc(sizeof(AIOProductRange*)*numbergroups );
    if (!ng->_groups ) goto cleanup;
    ng->_num_groups = numbergroups;

    va_start( arguments, numbergroups );
    for ( i = 0; i < (int)numbergroups ; i ++ ) {
        AIOProductRange *tmp = va_arg( arguments, AIOProductRange*);
        if ( !tmp ) goto err;
        ng->_groups[i] = tmp;
    }

    va_end(arguments);
    return ng;

 err:
    for (i = i-1 ;i >= 0; i -- ) {
        free(ng->_groups[i]);
    }
    free(ng->_groups);
 cleanup:
    free( ng );

    return NULL;
}

AIORET_TYPE DeleteAIOProductGroup( AIOProductGroup *pg )
{
    AIO_ASSERT( pg );
    int i;
    for ( i = 0; i < (int)pg->_num_groups; i ++ ) {
        free( pg->_groups[i] );
    }
    free(pg->_groups);
    free(pg);
    return AIOUSB_SUCCESS;
}

AIORET_TYPE AIOProductGroupContains( const AIOProductGroup *g, unsigned long val )
{
    AIO_ASSERT( g );
    int i;
    for ( i = 0 ; i < (int)g->_num_groups; i ++ ) {
        if ( val >= g->_groups[i]->_start && val <= g->_groups[i]->_end )
            return AIOUSB_SUCCESS;

    }
    return -AIOUSB_ERROR_INVALID_DATA;
}



#ifdef __cplusplus
}
#endif


#ifdef SELF_TEST

#include "AIOUSBDevice.h"
#include "gtest/gtest.h"

#include <iostream>
using namespace AIOUSB;

#include <unistd.h>
#include <stdio.h>

TEST(AIOProductRange,NewProductRange ) 
{
    AIOProductRange *tmp = NewAIOProductRange(100,1100);
    ASSERT_TRUE( tmp );

    ASSERT_EQ( 1100, AIOProductRangeEnd(tmp));
    ASSERT_EQ( 100 , AIOProductRangeStart(tmp));
    
    DeleteAIOProductRange( tmp );
}

TEST(AIOProductGroup,NewGroup )
{
    AIOProductRange *first = NewAIOProductRange(100,1100);
    AIOProductRange *second = NewAIOProductRange(1105,1200);
    AIOProductGroup *pg = NewAIOProductGroup( 2, first, second );
    
    ASSERT_TRUE( pg );


    DeleteAIOProductGroup( pg );
}

TEST(AIOProductGroup,NullGroups )
{
    AIOProductRange *first = NewAIOProductRange(100,1100);
    AIOProductRange *second = NewAIOProductRange(1105,1200);
    AIOProductRange *nullval = NULL;

    AIOProductGroup *pg = NewAIOProductGroup( 3, first, second, nullval);
    
    ASSERT_FALSE( pg );

}
#undef AIO_RANGE
#undef AIO_PRODUCT_GROUP

#ifdef __cplusplus
#define AIO_RANGE(start,stop) new AIOProductRange(start,stop)
#define AIO_PRODUCT_GROUP(NAME, N , ... ) const AIOProductGroup NAME( N, __VA_ARGS__ )
#define AIO_PRODUCT_CONSTANT(NAME, NAMEPTR, N, ... )   const AIOProductGroup NAME( N, __VA_ARGS__ ); \
                                                       const AIOProductGroup *NAMEPTR = &NAME;
#else
#define AIO_RANGE(start,stop) (&(AIOProductRange *){ ._start=start, ._end =stop })
#define AIO_PRODUCT_GROUP(NAME, N , ... ) const AIOProductGroup NAME( N, __VA_ARGS__ )


#endif 

TEST(AIOProductGroup, Defaults )
{
    AIOProductRange newbie(10,20);
    AIOProductRange *second = new AIOProductRange(10,34);
    AIOProductGroup other( 3, AIO_RANGE(3,4),AIO_RANGE(3,4),AIO_RANGE(3,4) );
    AIO_PRODUCT_CONSTANT( mygroup, mygroupp, 2 , AIO_RANGE(3,4), AIO_RANGE(10,34) );
    AIORET_TYPE retval = AIOProductGroupContains( &mygroup, 3 );
    ASSERT_GE( retval, AIOUSB_SUCCESS );
    ASSERT_GE( AIOProductGroupContains( &mygroup, 10 ), AIOUSB_SUCCESS );
    ASSERT_GE( AIOProductGroupContains( &mygroup, 4 ), AIOUSB_SUCCESS );
    ASSERT_LT( AIOProductGroupContains( &mygroup, 5 ), AIOUSB_SUCCESS );
    ASSERT_GE( AIOProductGroupContains( &mygroup, 11 ), AIOUSB_SUCCESS );
    ASSERT_GE( AIOProductGroupContains( &mygroup, 34 ), AIOUSB_SUCCESS );
    ASSERT_LT( AIOProductGroupContains( &mygroup, 2 ), AIOUSB_SUCCESS );
    
    delete second;

}

int main(int argc, char *argv[] )
{
  
  AIORET_TYPE retval;

  testing::InitGoogleTest(&argc, argv);
  testing::TestEventListeners & listeners = testing::UnitTest::GetInstance()->listeners();

  return RUN_ALL_TESTS();  

}

#endif