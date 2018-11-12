use strict;
use warnings;

use constant {
    MAXTIME     =>  20,     # maximal simulation timesteps
    MAX_EVENT   =>  100     # event calendar capacity
};

my $simtime = 0;    # current timestep
my @calendar = ();  # event calendar ({'time'=>int, 'event'=>int, 'event_sub'=>function()},...)
my $persons = 0;    # persons in hall

sub get_random_number {
    my($min, $max) = @_;
    $min + int(rand($max - $min));
}

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

# represents people coming to the hall 
sub event1 {
    my $persons_in = get_random_number(1, 3);
    print "$persons_in persons came\n";
    $persons += $persons_in;
    event_schedule(get_random_number(1, 2), 1, \&event1); # somebody else will come after 1 - 2 timesteps
}

# represents lift leaving hall
sub event2 {
    $persons = ($persons < 3) ? 0 : $persons - 3;
    print "lift has left floor, waiting persons: $persons\n";
    event_schedule(get_random_number(2, 5), 2, \&event2); # lift returns after 2 - 5 timesteps
}

sub main {
    print "simulation starts\n";
    # first events
    event_schedule(1, 1, \&event1);
    event_schedule(1, 2, \&event2);
    calendar_print();
    # simulation loop
    while ($simtime < MAXTIME) {
        my ($event, $event_sub) = event_cause();
        print "time: $simtime, event: $event\n";
        &$event_sub if ($event); # execute event function
    }
    calendar_print();
    print "simulation finished\n";
}

main();
