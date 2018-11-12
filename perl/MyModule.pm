package MyModule;

use strict;
use warnings;
use v5.12;

sub open_file {
    my $file_name = shift;
    open(my $filehandle, ">>", $file_name) or die "cant open file";
    print($filehandle "testline1", "\n");
    close($filehandle);
}

sub print_file {
    my $file_name = shift;
    if (!(-e -r $file_name)) {
        print("Error, file not readable or does not exist\n");
        return;
    }
    open(my $filehandle, "<", $file_name) or die "cant open file";
    my $line_nr = 1;
    while (<$filehandle>) {
        print "Line: ${line_nr}: ", $_;
        $line_nr++;
    }
    close($filehandle);
}

sub get_change_reference {
    my $number_reference = \shift;
    $$number_reference++;
}

sub get_change_dont_reference {
    my $number = shift;
    $number++;
}

1;