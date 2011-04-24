#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <google/cmockery.h>
#include "dollar.h"
#include "franc.h"


static void
test_multiply_dollar_5x2() {
  Money *five = create_dollar( 5 );
  Money *product = multiply_money( five, USD, 2 );
  Money *ten = create_dollar( 10 );

  assert_true( equal( product, USD, ten, USD ) );

  free( five );
  free( product );
  free( ten );
}


static void
test_multiply_dollar_5x3() {
  Money *five = create_dollar( 5 );
  Money *product = multiply_money( five, USD, 3 );
  Money *fifteen = create_dollar( 15 );

  assert_true( equal( product, USD, fifteen, USD ) );

  free( five );
  free( product );
  free( fifteen );
}


static void
test_equal() {
  Money *five_dollar1 = create_dollar( 5 );
  Money *five_dollar2 = create_dollar( 5 );
  Money *six_dollar = create_dollar( 6 );
  Franc *five_franc = ( Franc * ) create_franc( 5 );

  assert_true( equal( five_dollar1, USD, five_dollar2, USD ) );
  assert_false( equal( five_dollar1, USD, six_dollar, USD ) );
  assert_false( equal( five_dollar1, USD, five_franc, CHF ) );

  free( five_dollar1 );
  free( five_dollar2 );
  free( six_dollar );
  free( five_franc );
}


int
main() {
  const UnitTest tests[] = {
    unit_test( test_multiply_dollar_5x2 ),
    unit_test( test_multiply_dollar_5x3 ),
    unit_test( test_equal ),
  };
  return run_tests( tests );
}
