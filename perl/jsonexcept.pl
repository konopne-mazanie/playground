#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';
use JSON::PP qw(encode_json decode_json);
use Data::Dumper;

my $student = {
    name => 'Foo Bar',
    email => 'foo@bar.com',
    gender => undef,
    classes => [
        'Chemistry',
        'Math',
        'Litreture',
    ],
    address => {
        city => 'Fooville',
        planet => 'Earth',
    },
};

my $student_json = encode_json $student;
print $student_json, "\n";

my $student_struct = decode_json $student_json;
print Dumper($student_struct);
eval {
    my $json_struct2 = decode_json "{\\\\}";
} or do {
    print "Exception: ", $@, "\n" if $@;
};