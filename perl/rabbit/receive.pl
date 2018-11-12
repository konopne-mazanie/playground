#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

$|++;
use AnyEvent;
use Net::RabbitFoot;
use JSON::PP qw(encode_json decode_json);
use Data::Dumper;

my $conn = Net::RabbitFoot->new()->load_xml_spec()->connect(
    host => 'localhost',
    port => 5672,
    user => 'guest',
    pass => 'guest',
    vhost => '/',
);

my $ch = $conn->open_channel();

$ch->declare_queue(queue => 'json');

print " [*] Waiting for messages. To exit press CTRL-C\n";

sub callback {
    my $var = shift;
    my $body = $var->{body}->{payload};
    print " [x] Received:\n";
    my $decoded_json = decode_json $body;
    print Dumper($decoded_json);
}

$ch->consume(
    on_consume => \&callback,
    no_ack => 1,
);

# Wait forever
AnyEvent->condvar->recv;
