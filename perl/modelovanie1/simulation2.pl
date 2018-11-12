use strict;
use warnings;
use Switch;

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/modelovanie1";
use Queue;

use constant {
    MAXTIME             =>  1000,     # maximal simulation timesteps
    MAX_EVENT           =>  100,    # event calendar capacity

    QUEUE_CAPACITY_A    =>  100,
    QUEUE_CAPACITY_B    =>  100,
    QUEUE_CAPACITY_X    =>  100,
    QUEUE_CAPACITY_Y    =>  100,

    E1_DELAY            =>  10,
    E2_DELAY            =>  10,
    E3_DELAY            =>  10,
    E4_DELAY            =>  70,
    E5_DELAY            =>  50,
};

my $simtime = 0;    # current timestep
my @calendar = ();  # event calendar ({'time'=>int, 'event'=>int, 'event_sub'=>function()},...)

my $queueA = new Queue(QUEUE_CAPACITY_A);
my $queueB = new Queue(QUEUE_CAPACITY_B);
my $queueX = new Queue(QUEUE_CAPACITY_X);
my $queueY = new Queue(QUEUE_CAPACITY_Y);

my $item_dest = $queueB; # to where item goes from Q_A
my $item_in = 1; # item NR
my $done_cnt = 0;

sub calendar_print {
    print "==============================\n";
    for (my $i = 0; $i < scalar @calendar; $i++) {
       print "Calendar item: $i, time: " . $calendar[$i]->{'time'} . " event: " . $calendar[$i]->{'event'} . "\n";
    }
    print "==============================\n";
}

# add event to calendar
sub event_schedule {
    die "calendar overflow" unless (scalar @calendar <= MAX_EVENT);
    my ($delay, $event, $event_sub) = @_;
    push @calendar, {
        'time'      =>  $simtime + $delay,
        'event'     =>  $event,
        'event_sub' =>  $event_sub    
    };
    @calendar = sort {$a->{'time'} <=> $b->{'time'}} @calendar; #sort events by time
}

sub event_cause {
    my $first_elem = shift @calendar; # pop first event from calendar
    $simtime = $first_elem->{'time'}; # set current event simtime
    return ($first_elem->{'event'}, $first_elem->{'event_sub'});
}

sub event0 {
    event_schedule(1, 1, \&event1);
    event_schedule(1, 2, \&event2);
    event_schedule(1, 3, \&event3);
    event_schedule(1, 4, \&event4);
    event_schedule(1, 5, \&event5);
}

# transaction push Q_A
sub event1 {
    print "Transaction $item_in placed to Q_A\n";
    $queueA->push($item_in++);
    event_schedule(E1_DELAY, 1, \&event1);
}

# transaction move to Q_B/X/Y
sub event2 {
    my $item = $queueA->pop();
    return unless $item; # Q_A is empty
    if ($item_dest == $queueB) { # object address comparing
        unless ($queueB->push($item)) {
            print "Q_B overflow\n";
            $item = "NONE";
        }
        $item_dest = $queueX;
        print "Transaction $item moved to Q_B\n";
    } elsif ($item_dest == $queueX) {
        unless ($queueX->push($item)) {
            print "Q_X overflow\n";
            $item = "NONE";
        }
        $item_dest = $queueY;
        print "Transaction $item moved to Q_X\n";
    } else {
        unless ($queueY->push($item)) {
            print "Q_Y overflow\n";
            $item = "NONE";
        }
        $item_dest = $queueB;
        print "Transaction $item moved to Q_Y\n";
    }
    event_schedule(E2_DELAY, 2, \&event2);
}

# transaction left the system from Q_B
sub event3 {
    my $tr = $queueB->pop();
    $done_cnt++ if ($tr);
    print "Transaction " . ($tr or "NONE") . " left the system\n";
    event_schedule(E3_DELAY, 3, \&event3);
}

# transaction move from Q_X to Q_B
sub event4 {
    my $item = $queueX->pop();
    return unless $item;
    unless ($queueB->push($item)) {
        print "Q_B overflow\n";
        $item = "NONE";
    }
    print "Transaction $item moved to Q_B\n";
    event_schedule(E4_DELAY, 4, \&event4);
}

# transaction move from Q_Y to Q_X
sub event5 {
    my $item = $queueY->pop();
    return unless $item;
    unless ($queueX->push($item)) {
        print "Q_X overflow\n";
        $item = "NONE";
    }
    print "Transaction $item moved to Q_X\n";
    event_schedule(E5_DELAY, 5, \&event5);
}

sub main {
    print "simulation starts\n";
    # first events
    event0();
    calendar_print();
    # simulation loop
    while ($simtime < MAXTIME) {
        my ($event, $event_sub) = event_cause();
        print "time: $simtime, event: $event\n";
        &$event_sub if ($event); # execute event function
    }
    print "Done: $done_cnt\n";
    calendar_print();
    print "simulation finished\n";
}

main();
