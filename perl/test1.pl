use warnings;
use strict;
use v5.12;

use constant MY_CONSTANT => 69;

print("Hello World\n");
my $x = 10;
my $y = 20;
my $s = "Perl string";
my $c = $x + $y;
print($c, "\n");
#comment
print(length($s),"\n");
print("This is" . " concatenation operator" . "\n");
my $a = "this" eq "this"; #for comparing strings, not ==
print($a, "\n");

my $b;
chomp($b = <STDIN>);
print ($b, "\n");
my @arr = qw\1 2 3\;
my %this_is_hash = ( elemname => "val", #only string as key
                    elem2 => @arr);
print(%this_is_hash, "\n");
print("arr elem [0] is ", $arr[0], "\n"); #mind & as you getting scalar
print("from hash key elemname value is: ", $this_is_hash{"elemname"}, "\n");
$this_is_hash{"newelem"} = "newval"; #modify the same
delete $this_is_hash{"newelem"};
for(keys %this_is_hash){
 print("Val of $_ is $this_is_hash{$_}\n");
}

for(values %this_is_hash){
 print("Val $_\n");
}

print("if is true", "\n") if ($x == 10);

if (("this" eq "not_this") && (($x == 10))) {
    print("true", "\n");
} elsif ($y == 25) {
    print("y = 25", "\n");
} else {
    print("false", "\n");
}

my $given_ex;
given ($x) {
    when (10) { $given_ex = 77;}
    default {$given_ex = 22;}
}
print("given result: $given_ex\n");

for my $i (@arr) {
	$i = 2*$i;
}
print(@arr, "\n");

for (my $i = 0; $i < 3; $i++) {
	print($arr[$i]);
}


# my @numbers = ();
# while(my $input = <>) {
#   print(">");
#   push(@numbers, int(chomp($input)));    
# }
 
# print "You entered: @numbers\n";

my $sum_even = 0;
#my $num = 0;
do {{
 # get the next array element
 my $num = shift(@arr); #also removes the element from array
 # skip if the  element is odd number
 next if $num % 2 == 1;
 # calculate total of even numbers
 $sum_even += $num;
}}until(!scalar @arr > 0);
print($sum_even, "\n");

my $con_str = "abc";
$con_str .= "def";
print $con_str, "\n";
