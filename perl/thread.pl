use strict;
use warnings FATAL => 'all';
use threads;
use threads::shared;
use Thread::Queue qw( );
use v5.12;

my $cmd = system("ls -ah"); #cmd contains return code
print $cmd, "\n";
my @cmd2 = system(qw\ls -a -h\); #safer
my $cmd_out = `ls -ah`;
print $cmd_out, "\n";

my $th1 = threads->create(sub {
    for (my $i = 0; $i < 100; $i++) {
        print $i;
    }
});
for (my $i = 0; $i < 100; $i++) {
    print "a";
}
$th1->join();
print "\n";

my $th2 = threads->create({"context" => "list"}, sub {
    for (@_) {
        print $_;
    }
    @_;
}, 1, 2, 3); #passes 1,2,3 as params to sub
my @th_arr = $th2->join();
print @th_arr;



my $NUM_WORKERS = 5;
sub worker {
    my ($job) = @_;
    print $job;
}

my $q = Thread::Queue->new();
my @workers;
for (1..$NUM_WORKERS) {
    push @workers, async {
        while (defined(my $job = $q->dequeue())) {
            worker($job);
        }
    };
}
my @jobs = qw\j k l\;
$q->enqueue($_) for @jobs;        # Send work
$q->end();                        # Tell workers they're done.
$_->join() for @workers;          # Wait for the workers to finish.