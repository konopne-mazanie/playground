package Queue;

use warnings;
use strict;

sub new {
    my $class = shift;
    return bless ({
        'capacity'    =>  shift,
        'elements'    =>  []
    }, $class);
}

sub push {
    my ($self, $elem) = @_;
    return 0 if ((scalar @{$self->{'elements'}} + 1) > $self->{'capacity'});
    push @{$self->{'elements'}}, $elem;
    return 1;
}

sub pop {
    my $self = shift;
    return unless (scalar @{$self->{'elements'}});
    return shift @{$self->{'elements'}};
}

1;