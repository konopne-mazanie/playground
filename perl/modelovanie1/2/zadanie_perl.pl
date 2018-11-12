use strict;
use warnings;

use constant {
    ROAD_LENGHT         =>  200,
    ROAD_PART_SIZE      =>  10,
    CAR_COME_PROB       =>  [100, 10],
    MAX_CAR_SPEED       =>  20,
    SIM_STEPS_COUNT     =>  200,
};

my (@road, @road_delta);
my $last_id = 0;

sub get_random_number {
    my($min, $max) = @_;
    $min + int(rand($max - $min));
}

sub initialize_road {
    for my $i (0 .. (ROAD_LENGHT - 1)) {
        $road[$i] = 0;
        $road_delta[$i] = 0;
    }
}

sub show_road {
    print (("=" x 15) . "\n");
    print "| PART | DENS |\n";
    print (("=" x 15) . "\n");
    my ($part, $steps, $count, $average, $density) = (1, 0, 0, 0, 0);
    for (@road) {
        if ($steps == ROAD_PART_SIZE) {
            $density = (($count/$steps) * 100.0);
            $average+= $density;
            printf "| %4d | %3d%% |\n", $part, $density;
            print (("-" x 15) . "\n");
            $part++;
            ($steps, $count) = (0, 0);
        }
        $count++ if ($_);
        $steps++;
    }
    if ($steps) {
        printf ("| %4d | %3d%% |\n", $part, $density);
        print (("-" x 15) . "\n");
    }
    printf "|  AVG | %3d%% |\n", ($average/$part);
}

sub show_road_part {
    print "|";
    for my $i (shift() .. ROAD_PART_SIZE) {
        if ($road[$i]) {
            printf ("<=%4d=>", $road[$i]);
        } else {
            print ("_" x 8);
        }
    }
    print "|\n";
}

sub car_coming {
    return if ($road_delta[0]); # road start not empty
    return unless (get_random_number(0, CAR_COME_PROB->[0]) > CAR_COME_PROB->[1]);
    $road_delta[0] = ++$last_id;
}

sub car_distance {
    my $pos = shift() + 1;
    for my $i ($pos .. (ROAD_LENGHT-1)) {
        return $i if ($road[$i]);
    }
    return ROAD_LENGHT;
}

sub car_moving {
    my $pos = shift;
    my $next = car_distance($pos);
    return $next unless ($road[$pos]);
    if ($pos > (ROAD_LENGHT - 1)) {
        $road_delta[$pos] = 0;
        return (++$pos);
    }
    my $gt = $pos + get_random_number(1, MAX_CAR_SPEED);
    $gt = $next - 1 if ($gt >= $next);
    $road_delta[$gt] = $road[$pos];
    $road_delta[$pos] = 0;
    return $next;
}

sub timestep {
    my $i = -1;
    $road[++$i] = $_ for (@road_delta);
}

sub main {
    print "simulation starts\n";
    initialize_road;
    for (1 .. SIM_STEPS_COUNT) {
        car_coming;
        for (my $pos = 0; $pos < ROAD_LENGHT; $pos = car_moving($pos)) {}
        timestep;
        show_road_part(0);
    }
    show_road;
    print "simulation ends\n";
}

main;