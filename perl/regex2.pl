use warnings;
use strict;
use v5.12;
use Data::Dumper;

my @arr = qw/1 2 3/;
my @arr2 = qw/4 5 6/;
my %hsh = (
	"first"		=> \@arr,
	"second"	=> \@arr2
);
print(@{$hsh{"first"}});
print Dumper(\%hsh);

my $str = "this is sstring";
print("match", "\n") if ($str =~ /s{2}to?r[ijklmno]/);

my $str2 = q%::2/-99\\%; #% used as delimiter instead of " and \ escaped
print($str2, "\n");
my %match = ();
$match{$1} = $2 if ($str2 =~ /:{2}(\d)\/(-?\d+)/);
print Dumper(\%match);
$str =~ s/s{2}(tring|zing)/replaced/;
print("$str" . "\n");

for my $id (0 .. (@arr-1)) {
	print($arr[$id], "\n");
}

my $arr_ref = \@arr;
my $hsh_ref = \%hsh;
print("first element of arr is: ", $arr_ref->[0], "\n");
print("[first][0] element of hsh is: ", $hsh_ref->{"first"}->[0], "\n");

my $arr_ref_s = [1..5];
my $hsh_ref_s = {
	"first" 	=> $arr_ref_s,
	"second"	=> \@arr2
};
print Dumper($hsh_ref_s);

my $newhsh_ref->{"first"}->{"inner_first"} = [1,2,3];
$newhsh_ref->{"first"}->{"inner_second"} = [4,4];
$newhsh_ref->{"second"} = 5;
print Dumper($newhsh_ref);