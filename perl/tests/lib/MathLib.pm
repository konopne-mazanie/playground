package MathLib;

use strict;
use warnings;
use v5.12;

use base 'Exporter';
our @EXPORT_OK = qw(add);

sub add {
    my ($a, $b) = @_;
    die "wrong param" unless (($a =~ (/^-?\d+$/)) && ($b =~ (/^-?\d+$/)));
    $a + $b;
}

1;