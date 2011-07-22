#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <google/cmockery.h>
#include "bank.h"
#include "money.h"
#include "sum.h"


static void
test_plus_returns_sum() {
  Expression *five = ( Expression * ) dollar( 5 );
  Expression *addend_five = ( Expression * ) dollar( 5 );

  Expression *result = plus( five, addend_five );
  Sum *sum = ( Sum * ) result->value;
  assert_true( equal( five, sum->augend ) );
  assert_true( equal( addend_five, sum->addend ) );

  free( five );
  free( addend_five );
  free( result);
}


static void
test_reduce_sum() {
  Expression *three_usd = ( Expression * ) dollar( 3 );
  Expression *four_usd = ( Expression * ) dollar( 4 );
  Expression *seven_usd = ( Expression * ) dollar( 7 );

  Expression *exp = plus( three_usd, four_usd );
  Expression *result = ( Expression * ) reduce( exp , USD );
  assert_true( equal( result , seven_usd ) );

  free( three_usd );
  free( four_usd );
  free( seven_usd );
  free( exp );
  free( result );
}


static void
test_reduce_different_currency() {
  Money *two_franc = franc( 2 );
  Money *one_dollar = dollar( 1 );

  add_rate( CHF, USD, 2 );
  Expression *exp_two_franc = expression_from ( two_franc );
  Money *result = reduce( exp_two_franc, USD );
  assert_true( equal( result, one_dollar ) );

  free( two_franc );
  free( one_dollar );
  free( exp_two_franc );
  free( result );
}

static void
test_mixed_addition(){
  Expression *five_bucks = ( Expression * ) dollar( 5 );
  Expression *ten_francs = ( Expression * ) franc( 10 );
  Expression *ten_usd = ( Expression * ) dollar( 10 );

  add_rate( CHF, USD, 2 );
  Expression *result = ( Expression * ) reduce( plus( five_bucks, ten_francs ), USD );
  assert_true( equal( ten_usd, result ) );

  free( five_bucks );
  free( ten_francs );
  free( ten_usd );
  free( result );
}


int
main() {
  const UnitTest tests[] = {
    unit_test( test_plus_returns_sum ),
    unit_test( test_reduce_sum ),
    unit_test( test_reduce_different_currency ),
    unit_test( test_mixed_addition ), 
  };
  return run_tests( tests );
}
