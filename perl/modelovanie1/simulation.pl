use strict;
use warnings;

use constant {
    MAXTIME             =>  20,     # maximal simulation timesteps
    MAX_EVENT           =>  100,    # event calendar capacity

    MAX_LIFT_1_PERSONS  =>  3,
    MAX_LIFT_2_PERSONS  =>  3,
    PEOPLE_COME_INT     =>  [1, 2],
    PEOPLE_COME_CNT     =>  [1, 3],
    LIFT_1_COME_INT     =>  [2, 5],
    LIFT_2_COME_INT     =>  [2, 5],
};

my $simtime = 0;    # current timestep
my @calendar = ();  # event calendar ({'time'=>int, 'event'=>int, 'event_sub'=>function()},...)
my $persons_h1 = 0;    # persons in hall 1
my $persons_h2 = 0;    # persons in hall 2

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
    my $persons_in = get_random_number(PEOPLE_COME_CNT->[0], PEOPLE_COME_CNT->[1]);
    print "$persons_in persons came\n";
    $persons_h1 += $persons_in;
    event_schedule(get_random_number(PEOPLE_COME_INT->[0], PEOPLE_COME_INT->[1]), 1, \&event1); # somebody else will come after PEOPLE_COME_INT timesteps
}

# represents lift 1 leaving hall
sub event2 {
    my $persons_lift = ($persons_h1 < MAX_LIFT_1_PERSONS) ? $persons_h1 : MAX_LIFT_1_PERSONS;
    $persons_h2 += $persons_lift;
    $persons_h1 -= $persons_lift;
    print "lift 1 has left floor, waiting persons (hall 1): $persons_h1\n";
    event_schedule(get_random_number(LIFT_1_COME_INT->[0], LIFT_1_COME_INT->[1]), 2, \&event2); # lift returns after 2 - 5 timesteps
}

# represents lift 2 leaving hall
sub event3 {
    $persons_h2 -= ($persons_h2 < MAX_LIFT_2_PERSONS) ? $persons_h2 : MAX_LIFT_2_PERSONS;
    print "lift 2 has left floor, waiting persons (hall 2): $persons_h2\n";
    event_schedule(get_random_number(LIFT_2_COME_INT->[0], LIFT_2_COME_INT->[1]), 3, \&event3); # lift returns after 2 - 5 timesteps
}

sub main {
    print "simulation starts\n";
    # first events
    event_schedule(1, 1, \&event1);
    event_schedule(1, 2, \&event2);
    event_schedule(1, 3, \&event3);
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
