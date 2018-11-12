#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

use Net::Prometheus;
use Plack::Builder;
use threads;

my $client = Net::Prometheus->new;

my $counter = $client->new_counter(
    name => "requests",
    help => "Number of received requests",
);

sub handle_request
{
    $counter->inc;
}

builder {
    mount "/metrics" => $client->psgi_app;
};

while (1) {
    sleep(10);
}