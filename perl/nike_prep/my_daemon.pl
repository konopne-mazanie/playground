#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

use Proc::Daemon;
use AnyEvent;
use Net::RabbitFoot;
use JSON::PP qw(encode_json decode_json);

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/nike_prep/lib";

use my_database;

## initialize daemon
#Proc::Daemon::Init; #TODO uncomment this

## initialize database
my $database = my_database->new(my_database->connect("stavky", "localhost", "3306"), "stavky") or die "database connection failed";

## initialize rabbit
my $conn = Net::RabbitFoot->new()->load_xml_spec()->connect(
    host => 'localhost',
    port => 5672,
    user => 'guest',
    pass => 'guest',
    vhost => '/',
) or die "Connection to rabbit failed";
my $ch = $conn->open_channel() or die "Connection to rabbit failed (unable to opem channel)";
$ch->declare_queue(queue => 'stavky');

sub rabbit_callback {
    my $var = shift;
    my $body = $var->{body}->{payload};
    my $decoded_json = decode_json $body;

    $database->insert_data($decoded_json->{stavka}, $decoded_json->{kurz});
}

$ch->consume(
    on_consume => \&rabbit_callback,
    no_ack => 1,
);

my $continue = 1;
$SIG{TERM} = sub { $continue = 0 };

while ($continue) {
    ## receive forever
    AnyEvent->condvar->recv;
}

# TODO all done and tested except settings loading (subtasks 5,6 remain),,install rabbitmq & mysql in office, configure database from this file