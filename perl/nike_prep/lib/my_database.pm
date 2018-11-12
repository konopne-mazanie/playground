package my_database;

use strict;
use warnings;

use DBI;

### Static (class) methods
sub connect {
	my ($class, $db, $host, $port) = @_;
	DBI->connect("DBI:mysql:database=$db;host=$host;port=$port","root","mysql") or die "Unable to connect";
}

sub new {
    my ($class, $database, $table) = @_;
    my $self = bless {
        database   =>  $database,
        table	   =>  $table
    }, $class;
}

### Methods

sub get_data {
	my $self = shift;
    my $database = $self->{database};
	my $table = $self->{table};
    my $command = <<EOF;
        SELECT *
        FROM $table
EOF

    my $query = run_query($database, $command);
	my @lines;

    while (1) {
		my @line = $query->fetchrow();
        last unless scalar(@line) > 0;
		push @lines, \@line;
    }
    $query->finish();
	@lines;
}

sub insert_data {
    my ($self, $stavka, $kurz) = @_;
    my $database = $self->{database};
	my $table = $self->{table};

    my $command = <<EOF;
        INSERT INTO $table(stavka, kurz)
        VALUES(?, ?)
EOF
    my $query = run_query($database, $command, [$stavka, $kurz]);
    $query->finish();
}

### private

sub run_query {
    my $database = shift;
    my $query = shift;
    my $params = shift;

    my $prep = $database->prepare($query) or die "bad statement";
    if (defined $params) {
        $prep->execute(@$params) or die "unable to execute query";
    } else {
        $prep->execute() or die "unable to execute query";
    }
    $prep;
}

sub DESTROY {
	my $self = shift;
	my $database = $self->{database};
	$database->disconnect();
}

1;
