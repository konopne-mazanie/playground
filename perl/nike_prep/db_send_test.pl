#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

$|++;
use Net::RabbitFoot;
use JSON::PP qw(encode_json decode_json);

my $conn = Net::RabbitFoot->new()->load_xml_spec()->connect(
    host => 'localhost',
    port => 5672,
    user => 'guest',
    pass => 'guest',
    vhost => '/',
);


my $chan = $conn->open_channel();

my $json = {
    stavka  =>  "ruzovy konik",
    kurz    =>  "99"
};

my $encoded_json = encode_json $json;

$chan->publish(
    exchange => '',
    routing_key => 'stavky',
    body => $encoded_json,
);

print " [x] Sent json\n";

$conn->close();