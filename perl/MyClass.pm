package MyClass;

use warnings;
use strict;
use v5.12;

sub new {
    my ($class,$args) = @_; #@_ contains classname and constructor arguments, creates binding list = @_
    my $self = bless { #use hash reference - {} to pass constructor params, you can use array reference [] or whatever ref
        property1   =>  $args->{property1},
        property2   =>  $args->{property2}
    }, $class;
}

sub set_prop {
    my ($self, $prop, $val) = @_;
    $self->{$prop} = $val;
}

sub get_prop {
    my ($self, $prop) = @_;
    $self->{$prop};
}

sub to_string {
    my $self = shift;
    print "Class props:\n";
    for (keys %$self) {
        print $self->{$_}, "\n";
    }
}

1;