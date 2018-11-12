use warnings;
use strict;
use v5.12;

sub function1 {
    print("sub", " $_[0]", "\n");
    print("input params count: ", scalar @_, "\n");
    "returned string"; #return not neccessary here
}

my $fn_ref = \&function1;
&$fn_ref("a") if (defined $fn_ref);

sub passByValue{
    my ($a, $b) = @_;
    $a = 2; #changed only internal value
}

passByValue(2, 3);