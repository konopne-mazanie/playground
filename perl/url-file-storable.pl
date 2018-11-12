use strict;
use warnings;
use v5.12;

use LWP::UserAgent;
use File::Basename;
use File::Temp;
use Data::Dumper;
use Time::HiRes;
use Storable;

my $user_agent = LWP::UserAgent->new;
my $response = $user_agent -> request(HTTP::Request->new(GET=>'http://google.com'));

printf "code, message: %d %s\n", $response->code, $response->message;
printf "status line:   %s\n"   , $response->status_line;
printf "filename:      %s\n"   , $response->filename;
printf "base:          %s\n"   , $response->base;

#print Dumper($response);

if ($response->is_success) {
    print Dumper($response->decoded_content);
} else {
    print "Error: ", $response->status_line, "\n";
}

my($filename, $dirs, $suffix) = fileparse("/home/peter/file.txt", qr/\.[^.]*/);
printf "filename: %s\ndirs: %s\nsuffix: %s\n", $filename, $dirs, $suffix;

my $tmp = File::Temp->new();
print $tmp "first output to temple file";

Time::HiRes::sleep(2.5);
my $clock0 = Time::HiRes::clock();
for (1..1000) {
    print $_;
}
print "\n";
my $clock1 = Time::HiRes::clock();
my $clockd = $clock1 - $clock0;
print $clockd, "\n";

my $arr_to_store = [1, 2, 3];
Storable::store($arr_to_store, "storage_file.dat") or die "Unable to store data";
my $arr_retrieved_ref = Storable::retrieve("storage_file.dat");
print @$arr_retrieved_ref if $arr_retrieved_ref;