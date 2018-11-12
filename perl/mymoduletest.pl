use warnings;
use strict;
use v5.12;

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/perl";
use MyModule;
use MyClass;
use MyModuleInherited;

my $argument = shift @ARGV;
print($argument, "\n");

MyModule::open_file("test.txt");
MyModule::print_file("test.txt");
my $num = 5;
MyModule::get_change_reference($num);
MyModule::get_change_dont_reference($num);
print($num, "\n");

my $my_class_instance_reference = MyClass->new({
    property1   =>  60,
    property2   =>  28
});

print $my_class_instance_reference->get_prop("property1"), "\n";
$my_class_instance_reference->set_prop("property1", 75);
print $my_class_instance_reference->get_prop("property1"), "\n";
$my_class_instance_reference->to_string();

my $mod_inherited = MyModuleInherited->new({
    property1 => 66,
    property2 => 32
});

$mod_inherited->to_string();