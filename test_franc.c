#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <google/cmockery.h>
#include "franc.h"


static void
test_multiply_franc_5x2() {
  Money *five = create_franc( 5 );
  Money *product = multiply_money( five, CHF, 2 );
  Money *ten = create_franc( 10 );

  assert_true( equal( product, CHF, ten, CHF ) );

  free( five );
  free( product );
  free( ten );
}


static void
test_multiply_franc_5x3() {
  Money *five = create_franc( 5 );
  Money *product = multiply_money( five, CHF, 3 );
  Money *fifteen = create_franc( 15 );

  assert_true( equal( product, CHF, fifteen, CHF ) );

  free( five );
  free( product );
  free( fifteen );
}


static void
test_equal() {
  Money *five1 = create_franc( 5 );
  Money *five2 = create_franc( 5 );
  Money *six = create_franc( 6 );

  assert_true( equal( five1, CHF, five2, CHF ) );
  assert_false( equal( five1, CHF, six, CHF ) );

  free( five1 );
  free( five2 );
  free( six );
}


int
main() {
  const UnitTest tests[] = {
    unit_test( test_multiply_franc_5x2 ),
    unit_test( test_multiply_franc_5x3 ),
    unit_test( test_equal ),
  };
  return run_tests( tests );
}
