use strict;
use warnings;
use v5.12;

use Test::Most tests => 4; #run witdh: prove -l t/MathLibTest.t

use MathLib qw(add);

subtest add1 => sub {
    plan tests => 1;
 
    is(add(2,2), 4, "MathLib Add Test");
};

subtest add2 => sub {
    plan tests => 1;
 
    is(add(2,2), 48, "MathLib Add Test (Should Fail)");
};

subtest has_methods => sub {
    plan tests => 2;
 
    can_ok("MathLib", ("add"));
    can_ok("MathLib", ("sub"));
};

subtest should_throw => sub {
    plan tests => 2;
 
    throws_ok { add("a", 70) } qr/wrong param/, "excp should be thrown";
    throws_ok { add(70, "b") } qr/wrong param/, "excp should be thrown";
};

