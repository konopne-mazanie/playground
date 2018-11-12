use warnings;
use strict;
use v5.12;
use Data::Dumper;

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/perl";
use MyModule;
use MyClass;
use MyModuleInherited;

my $my_class1 = MyClass->new({
    property1   =>  70,
    property2   =>  28
});

my $my_class2 = MyClass->new({
    property1   =>  65,
    property2   =>  28
});

my $list = [$my_class1, $my_class2];
my @list_sorted = sort {$a->get_prop("property1") <=> $b->get_prop("property1")} @$list;
my $list_sorted_r = \@list_sorted;

print Dumper($list_sorted_r);

my $fn = sub {"world"};
sub print_hello_word {
    my $fn_internal = shift;
    my $str = "hello " . &$fn_internal;
    print $str, "\n";
}
print_hello_word($fn);